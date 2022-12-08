# Flags de compilação
CC = gcc
CFLAGS = -Wall -std=c99

# Arquivos objeto:
OBJ = jewels.o

jewels: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o lattes
	
jewels.o: jewels.c
	$(CC) $(CFLAGS) -c jewels.c

# Limpa os arquivos objeto gerados
clean:
	rm *.o
	
# Limpa os arquivos objeto e o executável
purge: clean
	rm -f lattes
