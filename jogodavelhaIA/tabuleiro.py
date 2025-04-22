class Tabuleiro:
    """
    Representa o estado do tabuleiro (3x3):
    VAZIO = 0, X = 1, O = 2
    """
    VAZIO = 0
    X = 1
    O = 2

    def __init__(self):
        # Cria matriz 3x3 vazia
        self.matriz = [[Tabuleiro.VAZIO]*3 for _ in range(3)]

    def esta_livre(self, linha, coluna):
        # Retorna True se posição estiver vazia
        return self.matriz[linha][coluna] == Tabuleiro.VAZIO

    def marcar(self, linha, coluna, simbolo):
        # Marca X ou O se estiver livre
        if self.esta_livre(linha, coluna):
            self.matriz[linha][coluna] = simbolo
            return True
        return False

    def cheia(self):
        # Retorna True se não houver espaço vazio
        return all(self.matriz[i][j] != Tabuleiro.VAZIO
                   for i in range(3) for j in range(3))

    def verificar_vitoria(self, simbolo):
        m = self.matriz
        # Linhas e colunas
        for i in range(3):
            if all(m[i][j] == simbolo for j in range(3)):
                return True
            if all(m[j][i] == simbolo for j in range(3)):
                return True
        # Diagonais
        if m[0][0] == simbolo == m[1][1] == m[2][2]:
            return True
        if m[0][2] == simbolo == m[1][1] == m[2][0]:
            return True
        return False
