#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <omp.h>
#include <errno.h>

int **alloc_matrix(int XDIM, int YDIM);

void get_dimensions(int* dims);

void fill_matrix(int**matrix, int XDIM, int YDIM,char* file);

void apply_convolution(int**matrix, int** result, int* dims, int threads);

void save_matrix_as_binary(int** matrix, int* dims, char* filename);


int main(int argc, char *argv[]){

    
    if(argc < 2){

        printf("Use ./filter <n> with 'n' the number of threads to use in paralel section\n");

        exit(EXIT_FAILURE);

    }

    int threads = atoi(argv[1]);

    int dims[2];
    
    get_dimensions(dims);

    int** imagen_r = alloc_matrix(dims[0],dims[1]); 
    
    int** imagen_g = alloc_matrix(dims[0],dims[1]); 

    int** imagen_b = alloc_matrix(dims[0],dims[1]); 

    int** result_r = alloc_matrix(dims[0],dims[1]);

    int** result_g = alloc_matrix(dims[0],dims[1]);

    int** result_b = alloc_matrix(dims[0],dims[1]);

    
    fill_matrix(imagen_r,dims[0],dims[1],"canal_r.txt");

    fill_matrix(imagen_g,dims[0],dims[1],"canal_g.txt");

    fill_matrix(imagen_b,dims[0],dims[1],"canal_b.txt");

    
    apply_convolution(imagen_r, result_r, dims, threads);
    
    apply_convolution(imagen_g, result_g, dims, threads);

    apply_convolution(imagen_b, result_b, dims, threads);

    
    save_matrix_as_binary(result_r,dims,"filtered_r.bin");

    save_matrix_as_binary(result_g,dims,"filtered_g.bin");

    save_matrix_as_binary(result_b,dims,"filtered_b.bin");
    

    free(imagen_r);

    free(result_r);

    free(imagen_g);

    free(result_g);

    free(imagen_b);

    free(result_b);

    exit(EXIT_SUCCESS);

}

void get_dimensions(int* dims){
    
    FILE * file = fopen("dimensiones.txt","r");

    if(file == NULL){

        perror("Error trying to obtain dimention of image from txt file");

        exit(EXIT_FAILURE);
        
    }
    
    char buffer[100];
    
    if(fgets(buffer, 100, file) == NULL){ 
        
        exit(EXIT_FAILURE);
    
    }
    
    char* token = strtok(buffer," ");
    
    int i = 0;
    
    while(token != NULL){
    
        dims[i] = atoi(token);
    
        i++;
    
        token=strtok(NULL," "); 
    
    }
    
    fclose(file);
}

int **alloc_matrix(int XDIM, int YDIM){

    int **array;
    
    array = malloc(sizeof(int*) * (size_t)YDIM);
    
    for(int i = 0 ; i < YDIM ; i++)
    
        array[i] = malloc( sizeof(int) *(size_t)XDIM);
    
    return array;

}

void fill_matrix(int**matrix, int XDIM, int YDIM,char* file){
    
    FILE* img = fopen(file, "r");

    if( img == NULL){

        perror("Error opening file for fill matrix");

        exit(EXIT_FAILURE);

    }
    
    char *line = NULL;
    
    size_t len = 0;

    int i,j;

    for(i = 0; i < YDIM; i++){
    
        if( getline(&line, &len, img) == -1){

            exit(EXIT_FAILURE);

        } 
    
        char* token = strtok(line," ");
    
        for(j = 0; j < XDIM; j++){
    
            matrix[i][j] = atoi(token);
    
            token = strtok(NULL, " "); 
    
        } 
    
    }

}

void apply_convolution(int**matrix, int** result, int* dims, int threads){
    
    int i, j, k, l;
    int accumulator;

    double start_time, end_time;
    double execution_time;

    int kernel[3][3] = {
    {-1, -1, -1},
    {-1,  8, -1},
    {-1, -1, -1}
    };
    
    start_time = omp_get_wtime();

    #pragma omp parallel for private(i,j,k,l,accumulator) num_threads(threads) schedule(static)

    for (i = 0; i < dims[0]; i++) {
        for (j = 0; j < dims[1]; j++) {
            accumulator = 0;
            
            for (k = 0; k < 3; k++) {
                for (l = 0; l < 3; l++) {
                    if (i + k - 1 >= 0 && i + k - 1 < dims[0] && j + l - 1 >= 0 && j + l - 1 < dims[1]) {
                        accumulator += matrix[i + k - 1][j + l - 1] * kernel[k][l];
                    }
                }
            }
            
            if(accumulator < 0){
                
                accumulator = 0;

            }else if(accumulator > 255){

                accumulator = 255;

            }
            
            result[i][j] = accumulator;
        }
    }

    end_time = omp_get_wtime();

    execution_time = end_time - start_time;

    printf("Tiempo de ejecución utilizando %d threads: %f segundos\n", threads, execution_time);

}

void save_matrix_as_binary(int** matrix, int* dims, char* filename) {
    
    int i;

    FILE* file = fopen(filename, "wb");

    if (file == NULL) {

        perror("Error trying to create binary file from save image.\n");

        exit(EXIT_FAILURE);

    }

    // Escribir las dimensiones de la matriz en el archivo
    if(fwrite(dims, sizeof(int), 2, file) == 0){

        perror("Error trying to write image dimention in binary file");

        exit(EXIT_FAILURE);

    }

    // Escribir la matriz en el archivo
    for (i = 0; i < dims[1]; i++) {
        
        if(fwrite(matrix[i], sizeof(int), (size_t)dims[0], file) == 0){
            
            perror("Error trying to write image in binary file");

            exit(EXIT_FAILURE);

        }
        
    }

    fclose(file);
}

