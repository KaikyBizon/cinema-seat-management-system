#include <stdio.h>

#define LIN 10
#define COL 8
#define TOTAL (LIN * COL)

int main() {
  // int seats[LIN][COL] = {
  //     {0, 0, 0, 0, 0, 0, 0, 0},
  //     {0, 0, 0, 0, 0, 0, 0, 0},
  //     {1, 1, 1, 1, 1, 1, 0, 0},
  //     {0, 0, 0, 0, 0, 0, 0, 0},
  //     {0, 0, 1, 1, 1, 1, 1, 1},
  //     {0, 0, 0, 0, 0, 0, 0, 0},
  //     {1, 1, 1, 0, 0, 0, 0, 0},
  //     {0, 0, 0, 0, 1, 1, 1, 0},
  //     {0, 0, 1, 1, 0, 0, 0, 0},
  //     {0, 0, 0, 0, 0, 0, 0, 0},
  // };
  // int seats[LIN][COL] = {
  //     {1, 0, 1, 0, 1, 0, 1, 0},
  //     {1, 0, 1, 0, 1, 0, 1, 0},
  //     {1, 0, 1, 0, 1, 0, 1, 0},
  //     {1, 0, 1, 0, 1, 0, 1, 0},
  //     {1, 0, 1, 0, 1, 0, 1, 0},
  //     {1, 0, 1, 0, 1, 0, 1, 0},
  //     {1, 0, 1, 0, 1, 0, 1, 0},
  //     {1, 0, 1, 0, 1, 0, 1, 0},
  //     {1, 0, 1, 0, 1, 0, 1, 0},
  //     {1, 0, 1, 0, 1, 0, 1, 0},
  // };
  int seats[LIN][COL] = {
      {0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0},
      {1, 1, 1, 1, 1, 1, 1, 1},
      {0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0},
  };

  int num_res, recom[TOTAL][2], recom_idx = 0, tmp_lin_idx, tmp_col_idx;

  // Variáveis para estatísticas
  int fil_crit[LIN], fil_liv[LIN],
      total_liv = 0, total_oc = 0,
      total_fil_liv = 0, total_fil_crit = 0,
      oc_fil, fil_max[2] = {0, 0}, fil_min[2] = {0, COL};

  // for (int i = 0; i < LIN; i++) {
  //   for (int j = 0; j < COL; j++) {
  //     seats[i][j] = 0;
  //   }
  // }

  for (int i = 0; i < LIN; i++) {
    for (int j = 0; j < COL; j++) {
      printf("%d ", seats[i][j]);
    }
    printf("\n");
  }

  for (int i = 0; i < LIN; i++) {
    oc_fil = 0;

    // Contar assentos ocupados
    for (int j = 0; j < COL; j++) {
      oc_fil += seats[i][j];
    }

    // Encontrar maior e menor
    if (oc_fil > fil_max[1]) {
      fil_max[0] = i;
      fil_max[1] = oc_fil;
    } else if (oc_fil < fil_min[1]) {
      fil_min[0] = i;
      fil_min[1] = oc_fil;
    }

    // Total de assentos ocupados e livres
    total_oc += oc_fil;
    total_liv += COL - oc_fil;

    // Fileiras livres e fileiras críticas
    if (oc_fil == 0) {
      fil_liv[total_fil_liv] = i;
      total_fil_liv++;
    } else if (oc_fil >= (3 * COL) / 4) {
      fil_crit[total_fil_crit] = i;
      total_fil_crit++;
    }
  }

  // Impressão de estatísticas
  printf("Total livre: %d\n", total_liv);
  printf("Total ocupado: %d\n", total_oc);
  printf("Percentual de ocupação: %.2f%%\n", (float)(total_oc * 100) / TOTAL);
  printf("Livre: ");
  for (int i = 0; i < total_fil_liv; i++) {
    printf("%d ", fil_liv[i]);
  }
  printf("\n");

  printf("Crítico: ");
  if (total_fil_crit == 0) {
    printf("Nenhuma");
  }
  else {
    for (int i = 0; i < total_fil_crit; i++) {
      printf("%d ", fil_crit[i]);
    }
  }
  printf("\n");

  printf("Fileira mais ocupada: %d\n", fil_max[0]);
  printf("Fileira menos ocupada: %d\n", fil_min[0]);

  // for (int j = 0; j < LIN; j++) {
  //   for (int k = 0; k < COL; k++) {
  //     if (recom_idx == num_res) {
  //       break;
  //     }
  //     tmp_lin_idx = (j + LIN/2 - 1 + LIN) % LIN;
  //     tmp_col_idx = (k + COL/2 - num_res/2 + COL) % COL;
  //     if (seats[tmp_lin_idx][tmp_col_idx] == 0) {
  //       recom[recom_idx][0] = tmp_lin_idx;
  //       recom[recom_idx][1] = tmp_col_idx;
  //       recom_idx++;
  //     }
  //   }
  // }

  // scanf("%d", &num_res);
  num_res = 9;

  // 1 - 8 assentos -> procurar 10 fileiras
  // 9 - 16 assentos -> procurar 9 fileiras
  // 17 - 24 assentos -> procurar 8 fileiras
  // for (int i = 0, x; i < LIN - ((num_res - 1) / COL); i++) {
  for (int i = 0, x; i < LIN; i++) {
    // 0 1 2 3 4 5 6 7 8 9 -> fileira
    // 9 7 5 3 1 0 2 4 6 8 -> prioridade de busca
    if (i % 2 == 0) {
      x = (LIN + i) / 2;
    } else {
      x = (LIN - 1 - i) / 2;
    }

    // X fileiras inteiras + 0 assentos -> procurar 0 colunas
    // X fileiras inteiras + 1 assentos -> procurar 8 colunas
    // X fileiras inteiras + 2 assentos -> procurar 7 colunas
    // for (int j = 0, y; j < (COL + 1 - (num_res % COL)) % (COL + 1); j++) {
    for (int j = 0, y; j < COL; j++) {
      if (recom_idx == num_res) {
        break;
      }
      // 0 1 2 3 4 5 6 7 -> assento
      // 7 5 3 1 0 2 4 6 -> prioridade de busca
      if (j % 2 == 0) {
        y = (j / 2) + (COL / 2);
      } else {
        y = (COL - 1 - j) / 2;
      }
      
      if (seats[x][y] == 0) {
        recom[recom_idx][0] = x;
        recom[recom_idx][1] = y;
        recom_idx++;
      }
    }
  }

  for (int i = 0; i < num_res; i++) {
    printf("%d %d\n", recom[i][0], recom[i][1]);
  }

  return 0;
}
