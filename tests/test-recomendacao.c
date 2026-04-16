#include <stdio.h>

#define LIN 10
#define COL 8
#define SEQ ((COL + 1) / 2)
// #define TOTAL (LIN * COL)

int main()
{
  int seats[LIN][COL] = {
      {1, 0, 1, 0, 1, 0, 1, 0},
      {0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0},
      {1, 1, 1, 1, 1, 1, 1, 1},
      {0, 0, 0, 1, 1, 1, 1, 1},
      {0, 0, 0, 1, 1, 1, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0},
  };
  int res_qtd, res_fil, res_resto, res_lim;
  int lvl_liv[LIN][2] = {0}, liv_fil[LIN][COL], tmp;
  int seq[LIN][SEQ][2] = {0}, seq_idx, skip;

  // Teste
  // Quantos assentos reservados?
  res_qtd = 5;

  // Procurar quantas fileiras?
  res_fil = ((res_qtd - 1) / COL) + 1;
  // Procurar quantos assentos na última busca?
  res_resto = res_qtd % COL;
  // Assentos por fileira
  if (res_qtd < COL) {
    res_lim = res_qtd;
  } else {
    res_lim = COL;
  }

  // Registrar número de assentos livres em cada fileira
  // do centro para fora
  // Imprimir os assentos
  for (int i = 0, x; i < LIN; i++) {
    // Ordem de prioridade das fileiras
    if (i % 2 == 0) {
      x = (LIN + i) / 2;
    } else {
      x = (LIN - 1 - i) / 2;
    }
    // Índice da fileira
    lvl_liv[i][0] = x;
    // Número de assentos livres na fileira
    lvl_liv[i][1] = COL;

    skip = 0;
    seq_idx = 0;

    for (int j = 0, y; j < COL; j++) {
      // Analisar assentos do centro para fora
      if (j % 2 == 0) {
        y = (COL + j) / 2;
      } else {
        y = (COL - 1 - j) / 2;
      }

      // Contar número de assentos livres
      lvl_liv[i][1] -= seats[x][j];

      if (seats[i][j] == 0) {
        if (skip == 0) {
          seq[i][seq_idx][0] = j;
          seq[i][seq_idx][1] = COL;
          skip = 1;
        }
      }
      else if (skip == 1) {
        seq[i][seq_idx][1] = j;
        seq_idx++;
        skip = 0;
      }

      // Se o assento analisado estiver livre, incluir o índice à matriz
      liv_fil[i][j] = -1;
      if (seats[i][y] == 0) {
        liv_fil[i][j] = y;
      }

      printf("%d ", seats[i][j]);
    }
    printf("\n");
  }

  // Organizar fileiras em ordem decrescente de assentos livres
  // Se houver assentos livres suficientes na fileira, ignorar
  // (a fileira ainda é elegível)
  for (int i = 0; i < LIN - 1; i++) {
    for (int j = i + 1; j < LIN; j++) {
      if (lvl_liv[i][1] < lvl_liv[j][1] && lvl_liv[i][1] < res_lim) {
        for (int k = 0; k < 2; k++) {
          tmp = lvl_liv[i][k];
          lvl_liv[i][k] = lvl_liv[j][k];
          lvl_liv[j][k] = tmp;
        }
      }
    }
  }

  // Teste
  for (int i = 0; i < LIN; i++) {
    printf("Fileira %d: %d livres - ", lvl_liv[i][0], lvl_liv[i][1]);
    for (int j = 0; j < COL; j++) {
      if (liv_fil[lvl_liv[i][0]][j] != -1) {
        printf("%d ", liv_fil[lvl_liv[i][0]][j]);
      }
    }
    printf("\n");

    tmp = 0;
    do {
      printf("[%d, %d[ ", seq[lvl_liv[i][0]][tmp][0], seq[lvl_liv[i][0]][tmp][1]);
      tmp++;
    } while (tmp < SEQ && seq[lvl_liv[i][0]][tmp][1] != 0);

    printf("\n\n");
  }

  return 0;
}
