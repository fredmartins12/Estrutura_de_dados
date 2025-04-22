import pygame

# Define cores usadas no jogo\NOME_CORES = {
    'preto': (0, 0, 0),
    'branco': (255, 255, 255),
    'azul': (0, 0, 255),
    'cinza': (192, 192, 192),
    'dourado': (255, 215, 0)
}

class Botao(pygame.sprite.Sprite):
    def __init__(self, linha, coluna, tamanho):
        super().__init__()
        # Guarda posição lógica do botão
        self.linha = linha
        self.coluna = coluna
        self.tamanho = tamanho

        # Cria superfície do botão
        self.image = pygame.Surface((tamanho, tamanho))
        # Define cores padrão (texto e fundo)
        self.cor_texto = NOME_CORES['preto']
        self.cor_fundo = NOME_CORES['branco']
        # Preenche fundo
        self.image.fill(self.cor_fundo)
        # Define retângulo para colisão e posicionamento
        self.rect = self.image.get_rect()
        self.rect.topleft = (coluna * tamanho, linha * tamanho)

        # Fonte para desenhar X ou O
        self.fonte = pygame.font.SysFont('Arial', tamanho // 2)
        self.simbolo = ''  # '', 'X' ou 'O'

    def set_simbolo(self, simbolo):
        # Só define se ainda não houver símbolo
        if self.simbolo:
            return False
        self.simbolo = simbolo
        # Atualiza visual
        self.image.fill(self.cor_fundo)
        if simbolo:
            texto = self.fonte.render(simbolo, True, self.cor_texto)
            # Centraliza o texto no botão
            pos = texto.get_rect(center=(self.tamanho // 2, self.tamanho // 2))
            self.image.blit(texto, pos)
        return Tru
