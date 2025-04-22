from tabuleiro import Tabuleiro
from jogador_humano import JogadorHumano
from jogador_ia import JogadorIA

class JogoDaVelha:
    """
    Controla o fluxo do jogo: turnos, vitória e empate.
    """
    def __init__(self):
        self.tabuleiro = Tabuleiro()
        self.turno = Tabuleiro.X  # X inicia
        self.jogador_x = JogadorHumano(Tabuleiro.X)
        self.jogador_o = JogadorIA(Tabuleiro.O)
        self.running = True
        self.ultimo_simbolo = ''

    def fazer_jogada(self, linha, coluna):
        """
        Executa a jogada do jogador atual.
        Retorna True se a jogada foi válida.
        """
        jogador = self.jogador_x if self.turno == Tabuleiro.X else self.jogador_o
        if jogador.jogar(self, linha, coluna):
            # Armazena símbolo para atualizar a interface
            self.ultimo_simbolo = 'X' if self.turno == Tabuleiro.X else 'O'
            # Verifica vitória ou empate
            if self.tabuleiro.verificar_vitoria(self.turno):
                print(f"{self.ultimo_simbolo} venceu!")
                self.running = False
            elif self.tabuleiro.cheia():
                print("Empate!")
                self.running = False
            else:
                # Alterna turno
                self.turno = Tabuleiro.O if self.turno == Tabuleiro.X else Tabuleiro.X
            return True
        return False
