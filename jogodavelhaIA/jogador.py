class Jogador:
    """
    Classe base para jogadores (Humanos ou IA).
    """
    def __init__(self, simbolo):
        self.simbolo = simbolo  # Armazena 'X' ou 'O'

    def jogar(self, tabuleiro):
        """
        Método a ser implementado pelas subclasses para fazer a jogada.
        """
        raise NotImplementedError("Método jogar deve ser implementado pelas subclasses")
