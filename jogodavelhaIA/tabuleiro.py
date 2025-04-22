class Tabuleiro:
    DESCONHECIDO = 0
    JOGADOR_0 = 1
    JOGADOR_X = 4
    OUTRO_TIPO = 2

    def __init__(self):
        self.matriz = [ [Tabuleiro.DESCONHECIDO, Tabuleiro.DESCONHECIDO, Tabuleiro.DESCONHECIDO], 
                        [Tabuleiro.DESCONHECIDO, Tabuleiro.DESCONHECIDO, Tabuleiro.DESCONHECIDO],
                        [Tabuleiro.DESCONHECIDO, Tabuleiro.DESCONHECIDO, Tabuleiro.DESCONHECIDO]]
#Aqui, uma lista de listas implementa uma matriz 3×3, permitindo acesso direto e constante a cada célula via matriz[linha][coluna]
#Por que é importante:
#Indexação O(1): pegar ou alterar o valor de qualquer posição é feito em tempo constante graças à implementação interna como array 
#Iteração simples: loops aninhados permitem percorrer linhas e colunas de forma clara, essencial para verificar condições de vitória.

    def tem_campeao(self):
        # Verificar linhas
        for i in range(3):
            if self.matriz[i][0] == self.matriz[i][1] == self.matriz[i][2] != Tabuleiro.DESCONHECIDO:
                return self.matriz[i][0]
        
        # Verificar colunas
        for i in range(3):
            if self.matriz[0][i] == self.matriz[1][i] == self.matriz[2][i] != Tabuleiro.DESCONHECIDO:
                return self.matriz[0][i]
        
        # Verificar diagonais
        if self.matriz[0][0] == self.matriz[1][1] == self.matriz[2][2] != Tabuleiro.DESCONHECIDO:
            return self.matriz[0][0]
        if self.matriz[0][2] == self.matriz[1][1] == self.matriz[2][0] != Tabuleiro.DESCONHECIDO:
            return self.matriz[0][2]
        
        # Verifica se há empate
        for i in range(3):
            for j in range(3):
                if self.matriz[i][j] == Tabuleiro.DESCONHECIDO:
                    return Tabuleiro.DESCONHECIDO
        
        # Empate
        return Tabuleiro.OUTRO_TIPO
