# Nome do executável
EXEC = lista_sequencial

# Compilador
CC = gcc

# Opções de compilação
CFLAGS = -Wall -Wextra -std=c11

# Arquivos fonte
SRC = lista.c

# Regra padrão para compilar o executável
all: $(EXEC)

$(EXEC): $(SRC)
	$(CC) $(CFLAGS) -o $(EXEC) $(SRC)

# Regra para limpar arquivos gerados
clean:
	rm -f $(EXEC)

# Regra para executar o programa
run: $(EXEC)
	./$(EXEC)

.PHONY: all clean run
