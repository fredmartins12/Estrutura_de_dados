# -*- coding: utf-8 -*-

import pygame  # Biblioteca para captura de eventos e interações do usuário
from jogador import Jogador
from tabuleiro import Tabuleiro

class JogadorHumano(Jogador):
    """
    Representa um jogador humano que faz jogadas através de cliques do mouse.
    """
    def __init__(self, tabuleiro: Tabuleiro, botoes: list, tipo: int):
        # Chama o construtor da classe base Jogador, passando o tabuleiro e o tipo (X ou O)
        super().__init__(tabuleiro, tipo)
        # Armazena a grade de botões usada pela interface gráfica
        self.buttons = botoes

    def get_jogada(self) -> (int, int):
        """
        Aguarda até que o usuário clique em um dos botões do tabuleiro.
        Retorna uma tupla (linha, coluna) indicando onde o usuário clicou.
        """
        while True:
            # Processa todos os eventos que ocorreram (teclado, mouse, etc.)
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    # Se o usuário fechar a janela, encerra o Pygame
                    pygame.quit()
                # Verifica se houve clique do mouse
                if event.type == pygame.MOUSEBUTTONDOWN:
                    # Captura a posição x,y do clique na janela
                    pos_mouse = pygame.mouse.get_pos()
                    # Percorre cada linha e coluna da grade de botões 3x3
                    for l in range(3):
                        for c in range(3):
                            b = self.buttons[l][c]  # Botão na posição [l][c]
                            # Se o clique ocorreu dentro da área desse botão
                            if b.rect.collidepoint(pos_mouse):
                                # Retorna a linha e a coluna correspondentes ao botão clicado
                                return (l, c)
                            
    
