#include <stdio.h>

// definindo constantes para alguns valores
#define TAM_TABULEIRO 10
#define TAM_NAVIO 3
#define TAM_OCTAEDRO 3
#define TAM_CRUZ 5
#define TAM_LCONE 3
#define TAM_CCONE 5

// definindo funções para facilitar a chamada das habilidades

void gerarCone(int habCone[TAM_LCONE][TAM_CCONE], int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    for (int i = 0; i < 3; i++) {

        for(int j = 0; j < 5; j++) {
            if (tabuleiro[i + 7][j] == 3 && habCone[i][j] == 1){
                tabuleiro[i + 7][j] = 5;
            } else if (tabuleiro[i + 7][j] == 3 && habCone[i][j] == 0) {
                tabuleiro[i + 7][j] = 3;
            } else {
                tabuleiro[i + 7][j] = habCone[i][j];
            }
        }
    }
}

void gerarCruz(int habCruz[TAM_CRUZ][TAM_CRUZ], int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    for (int i = 0; i < 5; i++) {

        for(int j = 0; j < 5; j++) {
            if (tabuleiro[i + 3][j + 3] == 3 && habCruz[i][j] == 1){
                tabuleiro[i + 3][j + 3] = 5;
            } else if (tabuleiro[i + 3][j + 3] == 3 && habCruz[i][j] == 0) {
                tabuleiro[i + 3][j + 3] = 3;
            } else {
                tabuleiro[i + 3][j + 3] = habCruz[i][j];
            }
        }
    }
}

void gerarOctaedro(int habOctaedro[TAM_OCTAEDRO][TAM_OCTAEDRO], int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    for (int i = 0; i < 3; i++) {

        for(int j = 0; j < 3; j++) {
            if (tabuleiro[i + 1][j + 1] == 3 && habOctaedro[i][j] == 1){
                tabuleiro[i + 1][j + 1] = 5;
            } else if (tabuleiro[i + 1][j + 1] == 3 && habOctaedro[i][j] == 0) {
                tabuleiro[i + 1][j + 1] = 3;
            } else {
                tabuleiro[i + 1][j + 1] = habOctaedro[i][j];
            }
        }
    }
}

void mostrarTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    for (int i = 0; i < TAM_TABULEIRO; i++) {

        for(int j = 0; j < TAM_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]); 
        }
        printf("\n");
    }
}

int main () {

    // criando o tabuleiro 10x10

    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];

    for (int i = 0; i < TAM_TABULEIRO; i++) {

        for(int j = 0; j < TAM_TABULEIRO; j++) {
            tabuleiro[i][j] = 0; 
        }
    }

    //navio horizontal
    int horizontalLinha = 2, horizontalColuna = 4;
    //navio vertical
    int verticalLinha = 5, verticalColuna = 7;
    //navio diagonal
    int linhaDiag = 1, colunaDiag = 1;
    //navio diagonal invertida
    int linhaDiagInversa = 5, colunaDiagInversa = 4;
    //flag para controlar se pode ou não posicionar os navios
    int podeExecutar = 1;

    //matriz feita mão de cada habilidade

    int habCruz[TAM_CRUZ][TAM_CRUZ] = {
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {1, 1, 1, 1, 1},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0}
    };

    int habCone[TAM_LCONE][TAM_CCONE] = {
        {0, 0, 1, 0, 0},
        {0, 1, 1, 1, 0},
        {1, 1, 1, 1, 1}
    };

    int habOctaedro[TAM_OCTAEDRO][TAM_OCTAEDRO] = {
        {0, 1, 0},
        {1, 1, 1},
        {0, 1, 0}
    };

    //condicional para saber se o navio esta dentro dos limites
    if ((horizontalColuna + TAM_NAVIO > TAM_TABULEIRO) || 
    (verticalColuna + TAM_NAVIO > TAM_TABULEIRO) || 
    (linhaDiag + TAM_NAVIO > TAM_TABULEIRO && colunaDiag + TAM_NAVIO > TAM_TABULEIRO) || 
    (linhaDiagInversa + TAM_NAVIO > TAM_TABULEIRO) || 
    (-colunaDiagInversa + -TAM_NAVIO < -TAM_TABULEIRO)) {
        printf("Navio fora dos limites.");
        podeExecutar = 0;
    } 

    //para saber os navios se sobrepoem
    if (podeExecutar) {
        for (int i = 0; i < TAM_NAVIO; i++) {
            if (tabuleiro[horizontalLinha][horizontalColuna + i] != 0 ||
                tabuleiro[verticalLinha + i][verticalColuna] != 0 ||
                tabuleiro[linhaDiag + i][colunaDiag + i] != 0 ||
                tabuleiro[linhaDiagInversa + i][colunaDiagInversa - i] != 0) {
                printf("Erro: sobreposição entre navios.\n");
                podeExecutar = 0;
                break;

            }
        }
    }

    //posicionando os navios
    if (podeExecutar) {
        for (int i = 0; i < TAM_NAVIO; i++){
            tabuleiro[horizontalLinha][horizontalColuna + i] = 3;
            tabuleiro[verticalLinha + i][verticalColuna] = 3;
            tabuleiro[linhaDiag + i][colunaDiag + i] = 3;
            tabuleiro[linhaDiagInversa + i][colunaDiagInversa - i] = 3;
        }
    }

    //chamando as habilidades
    gerarCone(habCone, tabuleiro);
    gerarCruz(habCruz, tabuleiro);
    gerarOctaedro(habOctaedro, tabuleiro);

    //chamando tabuleiro
    printf("Tabuleiro:\n");
    mostrarTabuleiro(tabuleiro);

    return 0;
}  