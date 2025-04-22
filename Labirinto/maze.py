import pygame
import numpy as np
import csv
import random
import threading
from collections import deque  # Estrutura de dados: deque permite inserção/remoção rápida em ambas as extremidades, ideal para pilha ou fila

class Maze:

    # Constantes usadas para representar diferentes elementos no labirinto
    WALL = 0     # Parede
    HALL = 1     # Corredor
    PLAYER = 2   # Jogador
    PRIZE = 3    # Prêmio

    def __init__(self):
        # Inicializa a matriz M como None. Ela será uma matriz NumPy representando o labirinto
        self.M = None  # Estrutura de dados: matriz é essencial para representar mapas e tabuleiros
        pygame.init()  # Inicializa os módulos do Pygame

    def load_from_csv(self, file_path: str):
        # Carrega o labirinto de um arquivo CSV
        with open(file_path, newline='') as csvfile:
            reader = csv.reader(csvfile)  # Lê cada linha do CSV como uma lista de strings
            # Converte cada valor para inteiro e cria uma matriz NumPy
            self.M = np.array([list(map(int, row)) for row in reader])  # NumPy array: mais eficiente que listas para acessar e modificar grandes matrizes

    def init_player(self):
        # Define posições aleatórias para o jogador e o prêmio

        # Encontra posição válida aleatória para o jogador
        while True:
            posx = random.randint(2, 39)
            posy = random.randint(2, 39)
            if self.M[posx, posy] == Maze.HALL:
                self.init_pos_player = (posx, posy)  # Tupla: estrutura leve e imutável para representar coordenadas
                break

        # Encontra posição válida aleatória para o prêmio
        while True:
            posx = random.randint(2, 39)
            posy = random.randint(2, 39)
            if self.M[posx, posy] == Maze.HALL:
                self.M[posx, posy] = Maze.PRIZE
                break

    def find_prize(self, pos: (int, int)) -> bool:
        # Verifica se a posição especificada contém o prêmio
        if self.M[pos[0], pos[1]] == Maze.PRIZE:
            return True
        else:
            return False

    def is_free(self, pos: (int, int)) -> bool:
        # Verifica se a posição está livre (corredor ou prêmio)
        if self.M[pos[0], pos[1]] in [Maze.HALL, Maze.PRIZE]:
            return True
        else:
            return False

    def mov_player(self, pos: (int, int)) -> None:
        # Move o jogador para a nova posição, se for válida (corredor)
        if self.M[pos[0], pos[1]] == Maze.HALL:
            self.M[pos[0], pos[1]] = Maze.PLAYER

    def get_init_pos_player(self) -> (int, int):
        # Retorna a posição inicial do jogador (tupla com coordenadas x, y)
        return self.init_pos_player

    def solve_maze(self) -> bool:
        # Algoritmo de busca para encontrar o prêmio

        stack = deque()  # deque como pilha: permite operações rápidas para DFS (Busca em profundidade)
        visited = set()  # set: estrutura eficiente para verificar se uma posição já foi visitada, com busca O(1)
        start_pos = self.get_init_pos_player()  # Posição inicial do jogador
        stack.append(start_pos)  # Adiciona posição inicial na pilha

        while stack:
            current_pos = stack.pop()  # Remove o topo da pilha (último a entrar)

            if self.find_prize(current_pos):  # Verifica se o prêmio está na posição atual
                print("Caminho encontrado!")
                return True

            if current_pos in visited:  # Ignora posições já visitadas
                continue

            visited.add(current_pos)  # Marca a posição atual como visitada
            self.mov_player(current_pos)  # Move o jogador

            x, y = current_pos  # Desempacota as coordenadas

            # Verifica as posições adjacentes (cima, baixo, esquerda, direita)
            for dx, dy in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
                next_pos = (x + dx, y + dy)  # Calcula nova posição (tupla)
                if next_pos not in visited and self.is_free(next_pos):
                    stack.append(next_pos)  # Adiciona nova posição na pilha

        print("Nenhum caminho encontrado.")
        return False

    def run(self):
        # Inicia uma nova thread para exibir o labirinto
        th = threading.Thread(target=self._display)  # thread: permite que a interface gráfica funcione em paralelo à lógica principal
        th.start()

    def _display(self, cell_size=15):
        # Exibe graficamente o labirinto com Pygame

        rows, cols = self.M.shape  # A matriz NumPy fornece número de linhas e colunas
        width, height = cols * cell_size, rows * cell_size
        screen = pygame.display.set_mode((width, height))
        pygame.display.set_caption("Labirinto")

        # Cores dos elementos
        BLACK = (0, 0, 0)
        GRAY = (192, 192, 192)
        BLUE = (0, 0, 255)
        GOLD = (255, 215, 0)

        running = True
        while running:
            if not pygame.display.get_init():
                break

            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    running = False
                    pygame.quit()

            screen.fill(BLACK)

            # Percorre a matriz e desenha cada célula com a cor apropriada
            for y in range(rows):
                for x in range(cols):
                    if self.M[y, x] == Maze.WALL:
                        color = BLACK
                    elif self.M[y, x] == Maze.HALL:
                        color = GRAY
                    elif self.M[y, x] == Maze.PLAYER:
                        color = BLUE
                    elif self.M[y, x] == Maze.PRIZE:
                        color = GOLD

                    pygame.draw.rect(screen, color, (x * cell_size, y * cell_size, cell_size, cell_size))

            pygame.display.flip()
