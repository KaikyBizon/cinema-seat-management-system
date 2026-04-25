#include <stdio.h>

#define LIN 10
#define COL 8
#define TOTAL (LIN * COL)

int main() {
  int seats[LIN][COL] = {
      {0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0},
      {1, 1, 1, 1, 1, 1, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0},
      {0, 1, 1, 1, 1, 1, 1, 1},
      {0, 0, 0, 0, 0, 0, 0, 0},
      {1, 1, 1, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 1, 1, 1, 0},
      {0, 0, 1, 1, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0},
  };
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
  // int seats[LIN][COL] = {
  //     {0, 0, 0, 0, 0, 0, 0, 0},
  //     {0, 0, 0, 0, 0, 0, 0, 0},
  //     {0, 0, 0, 0, 0, 0, 0, 0},
  //     {0, 0, 0, 0, 0, 0, 0, 0},
  //     {0, 0, 0, 0, 0, 0, 0, 0},
  //     {1, 1, 1, 1, 1, 1, 1, 1},
  //     {0, 0, 0, 0, 0, 0, 0, 0},
  //     {0, 0, 0, 0, 0, 0, 0, 0},
  //     {0, 0, 0, 0, 0, 0, 0, 0},
  //     {0, 0, 0, 0, 0, 0, 0, 0},
  // };

  // Variáveis para estatísticas
  int fil_crit[LIN], fil_liv[LIN],
      total_liv = 0, total_oc = 0,
      total_fil_liv = 0, total_fil_crit = 0,
      oc_fil, fil_max[2] = {0, 0}, fil_min[2] = {0, COL},
      rest_liv_crit[LIN];

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
      rest_liv_crit[i] = COL - oc_fil;
    }
  }

  // Impressão de estatísticas
  printf("Total livre: %d\n", total_liv);
  printf("Total ocupado: %d\n", total_oc);
  printf("Percentual de ocupacao: %.2f%%\n", (float)(total_oc * 100) / TOTAL);
  printf("Fileiras livres: ");
  for (int i = 0; i < total_fil_liv; i++) {
    printf("%d ", fil_liv[i]);
  }
  printf("\n\n");

  printf("Fileiras criticas: ");
  if (total_fil_crit == 0) {
    printf("Nenhuma");
  }
  else {
    for (int i = 0; i < total_fil_crit; i++) {
      printf("%d ", fil_crit[i]);
    }
  }
  printf("\n");

  for (int i; i < total_fil_crit; i++) {
    printf("Fileira %d: ", fil_crit[i]);
    printf("%d livres\n", rest_liv_crit[fil_crit[i]]);
  }

  printf("\n");

  printf("Fileira mais ocupada: %d\n", fil_max[0]);
  printf("Fileira menos ocupada: %d\n", fil_min[0]);

  return 0;
}
