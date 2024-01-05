### Ingeniería en Computación - FCEFyN - UNC
# Memoria compartida

# Desarrollo y explicación del proyecto

Para la resolución de este trabajo práctico se optó primero por una organización del proyecto para determinar cómo se iba a llevar a cabo el mismo.

En primer lugar, se optó por dividir el proyecto en 3 (tres) programas que realizan distintas funciones. A continuación; se detalla brevemente qué hace cada programa 

1) Un programa en Python "separe_img.py": Este programa abre una imagen .png la cual es la imagen "GeoTif" proporcionada en GitHub, solo que se optó cambiarle el formato para
poder trabajar con ella en Python con librerías conocidas. Lo que hace el programa con esta imagen es dividirla en sus tres canales RGB monocromáticos. Cada canal está representado por una matriz de NxM cuyos valores representan la intensidad monocromática en R, G y B para la imagen. Se deja expresado a cada canal como un archivo .txt que contiene dichos valores.

2) El programa principal "main.c": Respetando la consigna, se decidió crear un programa principal que tome los tres canales R, G y B como entrada y su output sean tres salidas que corresponden al edge filter aplicado a cada canal input. Dicho programa lo que hace es levantar cada archivo .txt proporcionado por el programa nro 1) y crear las matrices cuando el programa se ejecuta. Una vez creadas las matrices se procede a aplicarle el edge-filter. En dicho cálculo es donde entra en juego la paralelización utilizando OpenMP; siendo posible pasar por parámetro la cantidad de threads a utilizar al programa principal. Se utilizan mediciones de tiempo proporcionadas por la librería OpenMP en donde se ve como incrementa la velocidad del cálculo a medida que se incrementan la cantidad de threads a utilizar hasta llegar a un "tope" proporcionado por las características del hardware en donde se ejecute el programa. Los tres canales output dados por este programa son las imágenes filtradas en formato binario .bin

3) El último programa en Python "show_img.py": Dicho programa hace posible la visualización de la imagen. Toma como input los tres archivos binarios proporcionados por el programa nro 2) y muestra la imagen filtrada como una suma de dichos canales.


# Ejecución del programa

Para la ejecución y análisis del proyecto se puede ejecutar el script "exec.sh" proporcionado en el repositorio el cual ejecuta paso por paso los programas mencionados anteriormente. 

Primero se compila el programa principal utilizando las flags de compilación correspondentes y se crea un ejecutable llamado filter

Luego se compila y ejecuta el primer programa en Python, que da como resultado las matrices R, G y B en formato .txt

Después se ingresa por consola la cantidad de threads a utilizar en la sección paralela del programa principal filter

Por último, se muestra por consola el tiempo que tarda cada aplicación del filtro a los canales y se muestra la imagen filtrada, en donde se puede variar el número de threads a utilizar y apreciar como se obtienen mejoras si se utiliza el número óptimo para cada caso.

El proyecto se desarrolló en una pc de 6 cores y 12 threads, por lo que el número óptimo de threads a utilizar es 12.

A continuación se muestran capturas de ejecuciones del programa sin utilizar paralelizacion y luego utilizando paralelización con 1, 2, 4, 8 y 12 threads. El orden en el que se filtran las imágenes es:

    1) La imagen r
    2) La imagen g
    3) La imagen b
![image](https://github.com/ICOMP-UNC/2023---soii---laboratorio-iv-teomerino1/assets/66422394/2b9976c8-d642-4a10-b159-df2a4a23c9b5)
    
![image](https://github.com/ICOMP-UNC/2023---soii---laboratorio-iv-teomerino1/assets/66422394/743ee990-b14a-47df-8091-f5906e0ca839)

![image](https://github.com/ICOMP-UNC/2023---soii---laboratorio-iv-teomerino1/assets/66422394/33671956-20fe-4685-af2e-7d9630368799)

![image](https://github.com/ICOMP-UNC/2023---soii---laboratorio-iv-teomerino1/assets/66422394/2423cbe9-cf50-4268-b35b-c462c33443b1)

![image](https://github.com/ICOMP-UNC/2023---soii---laboratorio-iv-teomerino1/assets/66422394/f77eef3a-87b8-41ae-b933-fc44e65bb945)

![image](https://github.com/ICOMP-UNC/2023---soii---laboratorio-iv-teomerino1/assets/66422394/c2e3d47d-4005-453c-9366-30a339c15cb6)

Se puede observar como los tiempos de ejecución obtienen mejoras hasta llegar al número óptimo de threads a utilizar, en este caso, 12.

Por último, se muestra una captura de una ejecución del programa con 50 threads para corroborar que aumentar la cantidad de threads más allá del óptimo trae resultados indeseados, y se ve como el tiempo de ejecución aumentó levemente a diferencia de la ejecución con el número óptimo para este caso. 

![image](https://github.com/ICOMP-UNC/2023---soii---laboratorio-iv-teomerino1/assets/66422394/34a7facc-a723-46fa-a0be-848247825a1a)






    
