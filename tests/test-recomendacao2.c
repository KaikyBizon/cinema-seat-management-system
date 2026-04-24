#include <stdio.h>

#define LIN 10
#define COL 8
#define TOTAL (LIN * COL)
#define SEQ ((COL + 1) / 2)

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

  int res_qtd, res_lim;
  // Cada fileira tem certo número de sequências contínuas de assentos
  // Cada sequência é definida por seu ponto inicial (inclusivo)
  // e seu ponto final (exclusivo)
  int seq[LIN][SEQ][2], skip;
  int seq_score[LIN][SEQ], seq_qtd[LIN];
  int seq_coord[2];
  int recom[TOTAL], recom_qtd, recom_idx;

  res_qtd = 5;
  recom_idx = 0;

  for (int i = 0; i < LIN; i++) {
    for (int j = 0; j < COL; j++) {
      printf("%d ", seats[i][j]);
    }
    printf("\n");
  }

  // while (res_qtd > 0) {
  //
  // }

  recom_qtd = 0;

  if (res_qtd <= COL) {
    res_lim = res_qtd;
  } else {
    res_lim = COL;
  }

  seq_coord[0] = (LIN + 1) / 2;
  seq_coord[1] = 0;

  for (int i = 0, x; i < LIN; i++) {
    // Ordem do centro para fora
    if (i % 2 == 0) {
      x = (LIN + i) / 2;
    } else {
      x = (LIN - i - 1) / 2;
    }

    skip = 0;
    seq_qtd[x] = 0;

    for (int j = 0; j < COL; j++) {
      // Registro das sequências contínuas da fileira
      if (seats[x][j] == 0) {
        if (skip == 0) {
          seq[x][seq_qtd[x]][0] = j;
          seq[x][seq_qtd[x]][1] = COL;
          skip = 1;
        }

        // Se o último assento da fileira estiver vazio
        // adicionar mais 1 para o tamanho da sequência
        if (j == COL - 1) {
          seq_qtd[x]++;
        }
      }
      // Se encontrar um assento ocupado
      // após uma sequência de assentos vazios,
      // encerrar a sequência e começar uma nova
      else if (skip == 1) {
        seq[x][seq_qtd[x]][1] = j;
        seq_qtd[x]++;
        skip = 0;
      }
      // printf("%d ", seats[i][j]);
    }

    // Atribuir pontuação com base em quão no centro
    // a sequência está
    // Limitar a sequência analisada ao número de
    // assentos reservados
    for (int j = 0; j < seq_qtd[x]; j++) {
      seq_score[x][j] = 0;
      for (int k = 0, y, cap = 0; k < COL; k++) {
        if (cap == res_lim) {
          break;
        }

        if (k % 2 == 0) {
          y = (COL + k) / 2;
        } else {
          y = (COL - k - 1) / 2;
        }

        if (seq[x][j][0] <= y && y < seq[x][j][1]) {
          seq_score[x][j] += (COL - y) * (y + 1);
          cap++;
        }
      }
      
      if (seq_score[x][j] > seq_score[seq_coord[0]][seq_coord[1]]) {
        seq_coord[0] = x;
        seq_coord[1] = j;
      }
    }
    // printf("\n");
  }

  // Descobrir qual a maior pontuação
  // Registrar os assentos da sequência
  for (int i = 0, x; i < res_lim; i++) {
    if (i % 2 == 0) {
      x = (COL + i) / 2;
    } else {
      x = (COL - i - 1) / 2;
    }
    
    if (seq[seq_coord[0]][seq_coord[1]][0] < x && x < seq[seq_coord[0]][seq_coord[1]][1]) {
      recom[i] = x;
      recom_qtd++;
    }
  }

  res_qtd -= recom_qtd;

  // TESTE
  // Impressão dos dados
  printf("\n");

  for (int i = 0; i < LIN; i++) {
    for (int j = 0; j < seq_qtd[i]; j++) {
      printf("[%d,%d[ ", seq[i][j][0], seq[i][j][1]);
    }
    printf("\n");
    for (int j = 0; j < seq_qtd[i]; j++) {
      printf("%d ", seq_score[i][j]);
    }
    printf("\n\n");
  }

  printf("(%d, %d)\n", seq_coord[0], seq_coord[1]);
  printf("%d assentos encontrados:\n", recom_qtd);
  for (int i = 0; i < res_lim; i++) {
    printf("(%d, %d) ", seq_coord[0], recom[i]);
  }
  printf("\n");

  return 0;
}
