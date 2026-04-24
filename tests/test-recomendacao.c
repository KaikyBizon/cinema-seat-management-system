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
      {1, 1, 1, 0, 0, 0, 0, 0},
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
  int score[LIN] = {0}, ord_idx;

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

    for (int j = 0, y, idx = 0; j < COL; j++) {
      // Analisar assentos do centro para fora
      if (j % 2 == 0) {
        y = (COL + j) / 2;
      } else {
        y = (COL - 1 - j) / 2;
      }

      // Contar número de assentos livres
      lvl_liv[i][1] -= seats[x][j];

      // Sequência de assentos livres
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
      // liv_fil[i][j] = -1;
      if (seats[i][y] == 0) {
        liv_fil[i][idx] = y;
        idx++;
      }

      printf("%d ", seats[i][j]);
    }
    printf("\n");
  }

  // Organizar fileiras em ordem decrescente de assentos livres
  // Priorizar fileiras com sequência contínua de assentos livres
  // maior ou igual ao número de assentos reservados
  for (int i = 0; i < LIN - 1; i++) {
    for (int j = i + 1; j < LIN; j++) {
      if (lvl_liv[i][1] < res_lim) {
        if (lvl_liv[i][1] < lvl_liv[j][1]) {
          for (int k = 0; k < 2; k++) {
            tmp = lvl_liv[i][k];
            lvl_liv[i][k] = lvl_liv[j][k];
            lvl_liv[j][k] = tmp;
          }
        }
      } else {
        for (int k = 0; k < SEQ; k++) {
          if (seq[lvl_liv[i][0]][k][1] == 0) {
            break;
          }
          if (seq[lvl_liv[i][0]][k][1] - seq[lvl_liv[i][0]][k][0] < res_lim) {
            for (int l = 0; l < 2; l++) {
              tmp = lvl_liv[i][l];
              lvl_liv[i][l] = lvl_liv[j][l];
              lvl_liv[j][l] = tmp;
            }
          }
        }
      }
    }
  }

  ord_idx = lvl_liv[0][0];
  for (int i = 0; i < LIN; i++) {
    score[lvl_liv[i][0]] = 0;
    for (int j = 0; j < lvl_liv[i][1]; j++) {
      if (j == res_lim) {
        break;
      }
      score[lvl_liv[i][0]] += (COL - liv_fil[lvl_liv[i][0]][j]) * (liv_fil[lvl_liv[i][0]][j] + 1);
    }
    if (score[lvl_liv[i][0]] > score[ord_idx]) {
      ord_idx = lvl_liv[i][0];
    }
  }

  // Teste
  for (int i = 0; i < LIN; i++) {
    printf("Fileira %d: %d livres - ", lvl_liv[i][0], lvl_liv[i][1]);
    for (int j = 0; j < lvl_liv[i][1]; j++) {
      printf("%d ", liv_fil[lvl_liv[i][0]][j]);
    }
    printf("\n");

    for (int j = 0; j < SEQ; j++) {
      if (seq[lvl_liv[i][0]][j][1] == 0) {
        break;
      }
      printf("[%d, %d[ ", seq[lvl_liv[i][0]][tmp][0], seq[lvl_liv[i][0]][tmp][1]);
    }

    printf("\n\n");
  }

  // for (int i = 0; i < LIN; i++) {
  //   printf("%d ", score[i]);
  // }
  // printf("\n");
  
  for (int i = 0; i < res_lim; i++) {
    printf("(%d, %d) ", ord_idx, liv_fil[ord_idx][i]);
  }
  printf("\n");


  return 0;
}
