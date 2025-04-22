import pygame
from buttons import Botao, NOME_CORES
from pygame.locals import QUIT, MOUSEBUTTONDOWN

class TelaTabuleiro:
    """
    Interface gráfica que mostra o tabuleiro e gerencia eventos.
    """
    def __init__(self, tela, jogo):
        self.tela = tela
        self.jogo = jogo
        # Cada célula ocupa 1/3 da largura da janela
        self.tamanho = tela.get_width() // 3
        # Grupo de sprites contendo todos os botões
        self.sprites = pygame.sprite.Group()
        for i in range(3):
            for j in range(3):
                btn = Botao(i, j, self.tamanho)
                self.sprites.add(btn)

    def loop(self):
        """
        Loop principal: captura eventos e atualiza a tela.
        """
        while True:
            for ev in pygame.event.get():
                if ev.type == QUIT:
                    pygame.quit()
                    return
                if ev.type == MOUSEBUTTONDOWN and self.jogo.running:
                    x, y = ev.pos
                    for btn in self.sprites:
                        if btn.rect.collidepoint(x, y):
                            # Tenta executar a jogada e atualiza o botão se válido
                            if self.jogo.fazer_jogada(btn.linha, btn.coluna):
                                btn.set_simbolo(self.jogo.ultimo_simbolo)
                            break

            # Desenha o fundo e todos os botões
            self.tela.fill(NOME_CORES['preto'])
            self.sprites.draw(self.tela)
            pygame.display.flip()
