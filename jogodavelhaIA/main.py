# Arquivo: main.py
# -*- coding: utf-8 -*-
import pygame
from jogo_velha import JogoDaVelha
from tabuleiro_screen import TelaTabuleiro

# Inicialização do Pygame
pygame.init()
# Cria janela 600x600 pixels
tela = pygame.display.set_mode((600, 600))
pygame.display.set_caption("Jogo da Velha IA")

# Cria instâncias do jogo e da tela
jogo = JogoDaVelha()
tela_jogo = TelaTabuleiro(tela, jogo)
# Inicia o loop de eventos e desenho da interface
tela_jogo.loop()

