#include <stdio.h>

#define LIN 10
#define COL 8
#define TOTAL_ASSENTOS (LIN * COL)
#define MAX_GRUPOS (TOTAL_ASSENTOS / 2) // limite de duplas caso a sala toda seja alugada

int main()
{
    // matriz da sala de cinema (1 = ocupado, 0 = livre)
    int matriz_cinema[LIN][COL] = {
        {1, 0, 1, 0, 1, 0, 1, 0},
        {0, 0, 0, 1, 1, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 1, 0},
        {1, 1, 1, 0, 0, 1, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 1, 1, 1, 1, 1},
        {0, 0, 1, 1, 1, 1, 0, 0},
        {0, 1, 1, 0, 1, 0, 0, 0},
        {0, 1, 1, 1, 0, 1, 0, 0},
        {0, 0, 1, 0, 1, 0, 0, 0},
    };

    int tamanhos[MAX_GRUPOS]; // guarda quantas pessoas ficam em cada subgrupo
    int filas[MAX_GRUPOS];    // guarda em qual linha cada subgrupo vai sentar
    int cols[MAX_GRUPOS];     // guarda em qual coluna cada subgrupo comeca

    int ingressos; // quantidade total de ingressos que o usuario vai digitar
    int max_r;     // numero maximo de divisoes permitidas (total de ingressos / 2)

    int r;         // em quantas partes o grupo esta sendo dividido
    int i;         // contador linhas
    int j;         // contador colunas
    int k;         // contador pra checar os assentos um do lado do outro
    int g;         // contador que indica qual subgrupo esta sendo testado
    int f1;        // fileira onde o primeiro grupo vai tentar sentar
    int c1;        // coluna onde o primeiro grupo vai tentar sentar
    int dir;       // direcao da busca (1 pra olhar a fileira de tras, -1 pra olhar a da frente)
    int offset;    // deslocamento pro switch (0 = meio, 1 = direita, 2 = esquerda)
    int f_teste;   // fileira que o codigo testa pros amigos que sobraram
    int c_teste;   // coluna que o codigo testa pros amigos que sobraram
    int sucesso = 0; // avisa o programa se achou lugar pra todo mundo (1) ou nao (0)
    int u, v;      // iteradores auxiliares para checar fileiras vizinhas
    int alocados;  // contador de quantos subgrupos ja acharam lugar

    // imprime o mapa
    printf("mapa atual da sala:\n     |    tela     |\n     ---------------\n");
    for (i = 0; i < LIN; i++) {
        printf("%2d | ", i);
        for (j = 0; j < COL; j++) printf("%d ", matriz_cinema[i][j]);
        printf("\n");
    }
    printf("     ---------------\n      0 1 2 3 4 5 6 7\n\n");

    // pega a quantidade de ingressos
    printf("sistema de sugestao:\n");
    printf("digite a quantidade de ingressos desejados: ");
    scanf("%d", &ingressos);
    printf("\nbuscando lugares...\n\n");

    // previne que o usuario peca mais lugares do que a sala tem ou valores negativos
    if (ingressos <= 0 || ingressos > TOTAL_ASSENTOS) {
        printf("erro: quantidade invalida. a sala tem %d assentos.\n", TOTAL_ASSENTOS);
        return 0; // encerra caso de erro
    }

    // calcula o limite de grupos (ex: 7 ingressos / 2 = maximo de 3 grupos)
    max_r = ingressos / 2;
    if (max_r == 0) {
        max_r = 1; // se comprar 1 ingresso, tem que tentar pelo menos 1 grupo
    }

    // tenta nao dividir (r=1), se falhar divide em 2 (r=2), etc.
    for (r = 1; r <= max_r; r++) {

        int base = ingressos / r; // quantas pessoas vao ficar em cada grupo por padrao
        int resto = ingressos % r; // quem sobrou da divisao e precisa de um assento extra

        // (pula pra proxima tentativa se a base for menor que 2)
        if (r > 1 && base < 2) continue;

        // distribui as pessoas nos subgrupos
        for (i = 0; i < r; i++) {
            if (i < resto) tamanhos[i] = base + 1; // os primeiros grupos ganham a sobra
            else tamanhos[i] = base;               // o resto fica com a quantidade base
        }

        // procura lugar pro grupo1 alternando do centro pros cantos
        for (i = 0; i < LIN; i++) {

            if (i % 2 == 0) f1 = (LIN + i) / 2;
            else f1 = (LIN - 1 - i) / 2;

            // desliza pela fileira testando as colunas
            for (c1 = 0; c1 <= COL - tamanhos[0]; c1++) {
                int livres = 0; // conta quantos zeros achou em sequencia

                // verifica os assentos lado a lado pro tamanho do grupo 1
                for (k = 0; k < tamanhos[0]; k++) {
                    if (matriz_cinema[f1][c1 + k] == 0) livres++;
                }

                // se a quantidade de zeros for igual ao tamanho do grupo 1, achou lugar
                if (livres == tamanhos[0]) {
                    filas[0] = f1; // guarda a linha do grupo 1
                    cols[0] = c1;  // guarda a coluna do grupo 1
                    alocados = 1;  // marca que ja guardamos lugar pra 1 subgrupo

                    // tenta encaixar o resto do pessoal estritamente colado aos que ja sentaram
                    for (g = 1; g < r; g++) {
                        int achou_g = 0; // avisa se achou lugar pra esse subgrupo (g) especifico

                        // varre as fileiras que ja fazem parte do grupo
                        for (u = 0; u < alocados; u++) {

                            // tenta colar na fileira de tras (+1) ou da frente (-1) dos amigos
                            for (dir = 1; dir >= -1; dir -= 2) {
                                f_teste = filas[u] + dir; // calcula a fileira vizinha exata

                                // verifica se a fileira vizinha existe (nao saiu da matriz)
                                if (f_teste >= 0 && f_teste < LIN) {

                                    // checa se essa fileira ja nao esta sendo usada pelo proprio grupo
                                    int usada = 0;
                                    for (v = 0; v < alocados; v++) {
                                        if (filas[v] == f_teste) usada = 1;
                                    }

                                    // se a fileira esta livre pra gente expandir o bloco
                                    if (usada == 0) {

                                        // tenta alinhar a coluna (mesma coluna, puxa pra direita, puxa pra esquerda)
                                        for (offset = 0; offset < 3; offset++) {
                                            switch (offset) {
                                                case 0: c_teste = c1;     break; // fica embaixo ou em cima
                                                case 1: c_teste = c1 + 1; break; // puxa um pro lado
                                                case 2: c_teste = c1 - 1; break; // puxa um pro outro
                                            }

                                            // garante que a coluna de teste nao estoure a parede da sala
                                            if (c_teste >= 0 && c_teste <= COL - tamanhos[g]) {
                                                int livres_vizinho = 0; // conta os zeros da vizinhanca

                                                for (k = 0; k < tamanhos[g]; k++) {
                                                    if (matriz_cinema[f_teste][c_teste + k] == 0) livres_vizinho++;
                                                }

                                                // se os lugares baterem com o tamanho desse subgrupo
                                                if (livres_vizinho == tamanhos[g]) {
                                                    filas[g] = f_teste; // salva a fileira vizinha pra ele
                                                    cols[g] = c_teste;  // salva a coluna dele
                                                    alocados++;         // registra que mais um grupo cresceu o bloco
                                                    achou_g = 1;        // marca que deu certo pra ele
                                                    break;              // sai do switch
                                                }
                                            }
                                        }
                                    }
                                }
                                if (achou_g == 1) break; // sai do laco de direcao se ja achou
                            }
                            if (achou_g == 1) break; // sai do laco de blocos vizinhos se ja achou
                        }
                        if (achou_g == 0) break; // se nao achou lugar colado pra esse subgrupo, a divisao toda falha
                    }

                    // se a quantidade de grupos colados for a mesma necessária
                    if (alocados == r) {
                        sucesso = 1; // deu tudo certo
                        break; // para de tentar outras colunas
                    }
                }
            }
            if (sucesso == 1) break; // para de testar outras linhas pro grupo principal
        }
        if (sucesso == 1) break; // para de tentar novas divisoes se a atual ja formou o bloco
    }

    // mostra o resultado final
    if (sucesso == 1) {
        printf("sucesso! lugares reservados em %d fileira(s) colada(s).\n\n", r);
        for (g = 0; g < r; g++) {
            printf("-> grupo %d (%d pessoas): fila %d, assentos %d a %d\n",
                   g + 1, tamanhos[g], filas[g], cols[g], cols[g] + tamanhos[g] - 1);
        }
    } else {
        printf("nao foi possivel juntar esse grupo sem separar alguem ou pular fileiras.\n");
    }

    return 0;
}
