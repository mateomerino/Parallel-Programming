
CFLAGS = -Wall -pedantic -Werror -Wextra -Wconversion -std=gnu11


filter: main.o
	gcc $(CFLAGS) -fopenmp -o filter main.o

main.o: main.c 
	gcc $(CFLAGS) -fopenmp -c main.c 


clean:
	rm *.bin *.txt *.o filter