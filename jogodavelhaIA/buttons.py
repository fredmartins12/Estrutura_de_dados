# Arquivo: buttons.py
# -*- coding: utf-8 -*-
import pygame  # Biblioteca para interface gráfica
from tabuleiro import Tabuleiro  # Importa a definição do tabuleiro

# Grupo de sprites para armazenar todos os botões do tabuleiro
botoes_sprite = pygame.sprite.Group()

class Botao(pygame.sprite.Sprite):
    def __init__(self, tela, posicao, dimensoes):
        super().__init__()  # Inicializa a classe base Sprite
        # Cores de texto e fundo no formato "texto on fundo"
        self.cores = "preto on branco"
        # Separa as cores de texto (fg) e fundo (bg)
        self.cor_texto, self.cor_fundo = self.cores.split(" on ")
        # Define posição x, y do botão
        self.x, self.y = posicao
        # Define largura (w) e altura (h)
        self.largura, self.altura = dimensoes
        # Retângulo que define área clicável e de desenho
        self.rect = pygame.Rect(self.x, self.y, self.largura, self.altura)
        self.tela = tela  # Referência à superfície onde o botão será desenhado
        self.jogador = Tabuleiro.DESCONHECIDO  # Estado inicial sem X ou O
        # Desenha o texto inicial vazio
        self.mudar_texto(Tabuleiro.DESCONHECIDO)
        # Desenha o botão
        self.atualizar()
        # Adiciona este sprite ao grupo global
        botoes_sprite.add(self)

    def mudar_texto(self, jogador):
        # Se já existe X ou O, não muda (impede sobrescrever)
        if self.jogador != Tabuleiro.DESCONHECIDO:
            return False
        self.jogador = jogador  # Atribui X ou O
        # Define fonte Arial no tamanho 150
        self.fonte = pygame.font.SysFont("Arial", 150)
        # Escolhe o caractere a renderizar (X, O ou espaço)
        if jogador == Tabuleiro.JOGADOR_X:
            self.texto_render = self.fonte.render("X", True, self.cor_texto)
        elif jogador == Tabuleiro.JOGADOR_0:
            self.texto_render = self.fonte.render("O", True, self.cor_texto)
        else:
            self.texto_render = self.fonte.render(" ", True, self.cor_texto)
        # Desenha o texto na posição do botão
        self.tela.blit(self.texto_render, (self.x, self.y))
        return True  # Indica que o texto foi alterado com sucesso

    def atualizar(self):
        # Atualiza cores (permitiria trocar tema)
        self.cor_texto, self.cor_fundo = self.cores.split(" on ")
        # Desenha o retângulo de fundo
        pygame.draw.rect(self.tela, self.cor_fundo, (self.x, self.y, self.largura, self.altura))
        # Atualiza a imagem usada pelo sprite (necessário para clique e desenho)
        self.image = self.texto_render
