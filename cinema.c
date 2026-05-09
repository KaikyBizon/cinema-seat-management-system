#include <stdio.h>
#include <stdlib.h>

#define LIN 10
#define COL 8
#define TOTAL (LIN * COL)
#define MAX_GRUPOS ((TOTAL + 1) / 2)

void limparBuffer();

int main() {
  int matriz_cinema[LIN][COL] = {0};
  int acao[TOTAL][2];
  int opt;
  int i, j, k, l;
  int aux;
  int flag;
  int alt_print;
  int erro;
  int sucesso;
  int final;

  int usrs[TOTAL] = {0};
  int pwds[TOTAL];
  int usr_seats[TOTAL] = {0};
  int usr_idx;
  int login;
  int pwd;

  int fil_max[2];
  int fil_min[2];
  int fil_liv[LIN];
  int fil_crit[LIN];
  int rest_liv_crit[LIN];
  int total_liv;
  int total_oc = 0;
  int total_fil_liv;
  int total_fil_crit;
  int oc_fil;

  int grupos[MAX_GRUPOS];
  int tamanhos[MAX_GRUPOS]; 
  int filas[MAX_GRUPOS];
  int cols[MAX_GRUPOS];
  int ingressos;
  int R, r;
  int cont_r;
  int Base, base;
  int Resto, resto;
  int s;
  int g;
  int u;
  int usada;
  int d;
  int dir;
  int f1;
  int c1;
  int offset;
  int f_teste;
  int c_teste;
  int alocados;
  int livres;
  int livres_vizinho;
  int achou_g;
  int sum_tam;
  int borda;
  int solo;

  system("cls");

  while (1) {
    do {
      printf("Login/Cadastro: ");
      flag = scanf("%d", &login);
      limparBuffer();

      if (flag == 0) {
        system("cls");
        printf("Login deve ser numerico.\n");
      } else if (login == 0) {
        system("cls");
        printf("Login nao pode ser 0\n");
      }
    } while (flag == 0 || login == 0);

    for (i = 0; i < TOTAL; i++) {
      if (usrs[i] == login) {
        usr_idx = i;
        break;
      } else {
        usr_idx = TOTAL;
      }
    }

    erro = 0;
    if (usr_idx == TOTAL) {

      for (i = 0; i < TOTAL; i++) {
        if (usrs[i] == 0) {
          usr_idx = i;
          break;
        }
      }

      if ((total_oc == TOTAL && usrs[usr_idx] == 0) || (usr_idx == TOTAL)) {
        system("cls");
        printf("A sala esta cheia.\n");
        erro = 1;
      }

      if (erro == 0) {
        do {
          printf("Criar senha: ");
          flag = scanf("%d", &pwds[usr_idx]);
          limparBuffer();
        } while (flag == 0);

        usrs[usr_idx] = login;
        pwd = pwds[usr_idx];
      }
    } else {
      do {
        printf("Senha: ");
        flag = scanf("%d", &pwd);
        limparBuffer();
      } while (flag == 0);
    }

    if (erro == 0) {

      if (pwd != pwds[usr_idx]) {
        system("cls");
        printf("Login ou senha invalidos\n");
      } else {
        final = 0;

        while (final == 0) {
          total_liv = 0;
          total_oc = 0;
          total_fil_liv = 0;
          total_fil_crit = 0;
          fil_max[0] = 0;
          fil_max[1] = 0;
          fil_min[0] = 0;
          fil_min[1] = 0;

          system("cls");

          printf("Usuario: %d\n\n", usrs[usr_idx]);
          printf("     |    TELA     |\n"
              "     ---------------\n");

          for (i = 0; i < LIN; i++) {
            oc_fil = 0;

            printf("%2d | ", i);
            for (j = 0; j < COL; j++) {
              alt_print = 1;
              

              if (matriz_cinema[i][j] != 0) {
                oc_fil++;

                if (matriz_cinema[i][j] == usrs[usr_idx]) {
                  printf("X ");
                } else {
                  printf("1 ");
                }
              } else {
                printf("0 ");
              }
            }

            if (oc_fil > fil_max[1]) {
              fil_max[0] = i;
              fil_max[1] = oc_fil;
            } else if (oc_fil < fil_min[1]) {
              fil_min[0] = i;
              fil_min[1] = oc_fil;
            }

            total_oc += oc_fil;
            total_liv += COL - oc_fil;

            if (oc_fil == 0) {
              fil_liv[total_fil_liv] = i;
              total_fil_liv++;
            } else if (oc_fil >= (3 * COL) / 4) {
              fil_crit[total_fil_crit] = i;
              total_fil_crit++;
              rest_liv_crit[i] = COL - oc_fil;
            }

            printf("\n");
          }
          printf("     ---------------\n");
          printf("     ");
          for (int i = 0; i < COL; i++) {
            printf("%d ", i);
          }
          printf("\n\n");

          printf("Legenda:\n"
              "X: Seus assentos\n"
              "1: Assentos ocupados\n"
              "0: Assentos livres\n\n");

          printf("Opcoes:\n"
              "1. Comprar ingresso\n"
              "2. Cancelar ingresso\n"
              "3. Recomendacao de assentos\n"
              "4. Obter estatisticas da sala\n"
              "5. Finalizar atendimento\n\n");

          do {
            printf("Opcao: ");
            flag = scanf("%d", &opt);
            limparBuffer();

            if (opt < 1 || opt > 5) {
              printf("Opcao fora dos limites.\n");
            }
          } while (flag == 0 || opt < 1 || opt > 5);

          switch (opt) {
            case 1:
              system("cls");

              if (total_oc == TOTAL) {
                printf("Desculpe, a sessao esta cheia.\n\n");
                system("pause");
                break;
              }

              printf("Usuario: %d\n\n", usrs[usr_idx]);
              printf("     |    TELA     |\n"
                  "     ---------------\n");

              for (i = 0; i < LIN; i++) {
                printf("%2d | ", i);
                for (j = 0; j < COL; j++) {
                  if (matriz_cinema[i][j] != 0) {
                    if (matriz_cinema[i][j] == usrs[usr_idx]) {
                      printf("X ");
                    } else {
                      printf("1 ");
                    }
                  } else {
                    printf("0 ");
                  }
                }
                printf("\n");
              }
              printf("     ---------------\n");
              printf("     ");
              for (i = 0; i < COL; i++) {
                printf("%d ", i);
              }
              printf("\n\n");

              erro = 0;
              k = 0;

              do {
                printf("Digite a quantidade de ingressos desejados: ");
                flag = scanf("%d", &ingressos);

                if (ingressos < 0 || ingressos > total_liv) {
                  if (total_liv == 1) {
                    printf("Quantidade invalida. A sala tem 1 assento livre.\n\n");
                  } else {
                    printf("Quantidade invalida. A sala tem %d assentos livres.\n\n", total_liv);
                  }
                }
              } while (flag == 0 || ingressos < 0 || ingressos > total_liv);

              if (ingressos == 0) {
                break;
              }

              printf("\n");

              while (k < ingressos) {
                erro = 0;

                do {
                  printf("Fileira: ");
                  flag = scanf("%d", &acao[k][0]);
                  limparBuffer();

                  if (acao[k][0] < 0 || acao[k][0] >= LIN) {
                    printf("Fileira fora dos limites. Tente novamente.\n\n");
                  }
                } while (flag == 0 || acao[k][0] < 0 || acao[k][0] >= LIN);

                do {
                  printf("Assento: ");
                  flag = scanf("%d", &acao[k][1]);
                  limparBuffer();

                  if (acao[k][1] < 0 || acao[k][1] >= COL) {
                    printf("Assento fora dos limites. Tente novamente.\n\n");
                  }
                } while (flag == 0 || acao[k][1] < 0 || acao[k][1] >= COL);

                if (matriz_cinema[acao[k][0]][acao[k][1]] != 0) {
                  printf("Esse assento ja esta ocupado! Tente novamente.\n\n");
                  erro = 1;
                } else {
                  for (i = 0; i < k; i++) {
                    if (acao[i][0] == acao[k][0] && acao[i][1] == acao[k][1]) {
                      printf("Esse assento ja esta sendo processado.\n\n");
                      erro = 1;
                      break;
                    }
                  }
                }

                if (erro == 0) {
                  k++;
                  system("cls");
                  printf("Usuario: %d\n\n", usrs[usr_idx]);
                  printf("     |    TELA     |\n"
                      "     ---------------\n");

                  for (i = 0; i < LIN; i++) {
                    printf("%2d | ", i);

                    for (j = 0; j < COL; j++) {
                      if (matriz_cinema[i][j] != 0) {
                        if (matriz_cinema[i][j] == usrs[usr_idx]) {
                          printf("X ");
                        } else {
                          printf("1 ");
                        }
                      } else {
                        alt_print = 1;
                        for (l = 0; l < k; l++) {
                          if (acao[l][0] == i && acao[l][1] == j) {
                            printf("C ");
                            alt_print = 0;
                            break;
                          }
                        }

                        if (alt_print == 1) {
                          printf("0 ");
                        }
                      }
                    }
                    printf("\n");
                  }
                  printf("     ---------------\n");
                  printf("     ");
                  for (i = 0; i < COL; i++) {
                    printf("%d ", i);
                  }
                  printf("\n\n");
                  printf("C: Assentos a serem comprados (%d/%d)\n\n", k, ingressos);
                }
              }

              printf("Finalizar?\n"
                     "1. Confirmar compra\n"
                     "2. Excluir compra\n\n");

              do {
                printf("Opcao: ");
                flag = scanf("%d", &opt);
                limparBuffer();

                if (opt < 1 || opt > 2) {
                  printf("Opcao fora dos limites.\n");
                }
              } while (flag == 0 || opt < 1 || opt > 2);

              switch (opt) {
                case 1:
                  for (j = 0; j < k; j++) {
                    matriz_cinema[acao[j][0]][acao[j][1]] = usrs[usr_idx];
                    usr_seats[usr_idx]++;
                  }
                  break;
                case 2:
                  break;
              }
              break;
            case 2:
              if (usr_seats[usr_idx] == 0) {
                system("cls");
                printf("Voce ainda nao reservou assentos.\n\n");
                system("pause");
                break;
              }

              system("cls");
              printf("Usuario: %d\n\n", usrs[usr_idx]);
              printf("     |    TELA     |\n"
                  "     ---------------\n");

              for (i = 0; i < LIN; i++) {
                printf("%2d | ", i);
                for (j = 0; j < COL; j++) {
                  if (matriz_cinema[i][j] != 0) {
                    if (matriz_cinema[i][j] == usrs[usr_idx]) {
                      printf("X ");
                    } else {
                      printf("1 ");
                    }
                  } else {
                    printf("0 ");
                  }
                }
                printf("\n");
              }
              printf("     ---------------\n");
              printf("     ");
              for (i = 0; i < COL; i++) {
                printf("%d ", i);
              }
              printf("\n\n");

              do {
                printf("Digite a quantidade de cancelamentos desejados: ");
                flag = scanf("%d", &ingressos);

                if (ingressos < 0 || ingressos > usr_seats[usr_idx]) {
                  if (usr_seats[usr_idx] == 1) {
                    printf("Quantidade invalida. Voce tem 1 assento reservado.\n\n");
                  } else {
                    printf("Quantidade invalida. Voce tem %d assentos reservados.\n\n", usr_seats[usr_idx]);
                  }
                }
              } while (flag == 0 || ingressos < 0 || ingressos > usr_seats[usr_idx]);

              if (ingressos == 0) {
                break;
              }

              printf("\n");

              k = 0;
              while (k < ingressos) {
                do {
                  printf("Fileira: ");
                  flag = scanf("%d", &acao[k][0]);
                  limparBuffer();

                  if (acao[k][0] < 0 || acao[k][0] >= LIN) {
                    printf("Fileira fora dos limites. Tente novamente.\n");
                  }
                } while (flag == 0 || acao[k][0] < 0 || acao[k][0] >= LIN);

                do {
                  printf("Assento: ");
                  flag = scanf("%d", &acao[k][1]);
                  limparBuffer();

                  if (acao[k][1] < 0 || acao[k][1] >= COL) {
                    printf("Assento fora dos limites. Tente novamente.\n\n");
                  }
                } while (flag == 0 || acao[k][1] < 0 || acao[k][1] >= COL);

                if (matriz_cinema[acao[k][0]][acao[k][1]] == 0) {
                  printf("Esse assento ja esta livre. Tente novamente.\n\n");
                } else {
                  erro = 1;

                  for (i = 0; i < k; i++) {
                    if (acao[i][0] == acao[k][0] && acao[i][1] == acao[k][1]) {
                      printf("Esse assento ja esta sendo processado.\n\n");
                      erro = 2;
                      break;
                    }

                  }

                  if (erro == 1 && matriz_cinema[acao[k][0]][acao[k][1]] == usrs[usr_idx]) {
                    k++;
                    erro = 0;
                  }

                  if (erro == 1) {
                    printf("Esse assento foi reservado por outro usuario. Tente novamente.\n\n");
                  } else {
                    system("cls");
                    printf("Usuario: %d\n\n", usrs[usr_idx]);
                    printf("     |    TELA     |\n"
                        "     ---------------\n");

                    for (i = 0; i < LIN; i++) {
                      printf("%2d | ", i);
                      for (j = 0; j < COL; j++) {
                        alt_print = 1;
                        for (l = 0; l < k; l++) {
                          if (acao[l][0] == i && acao[l][1] == j) {
                            printf("E ");
                            alt_print = 0;
                            break;
                          }
                        }
                        if (alt_print == 1) {
                          if (matriz_cinema[i][j] != 0) {
                            if (matriz_cinema[i][j] == usrs[usr_idx]) {
                              printf("X ");
                            } else {
                              printf("1 ");
                            }
                          } else {
                            printf("0 ");
                          }
                        }
                      }
                      printf("\n");
                    }
                    printf("     ---------------\n");
                    printf("     ");
                    for (i = 0; i < COL; i++) {
                      printf("%d ", i);
                    }
                    printf("\n\n");
                    printf("E: Assentos a serem cancelados (%d/%d)\n\n", k, ingressos);
                  }
                }
              }

              printf("Finalizar?\n"
                  "1. Confirmar cancelamento\n"
                  "2. Excluir cancelamento\n\n");

              do {
                printf("Opcao: ");
                flag = scanf("%d", &opt);
                limparBuffer();

                if (opt < 1 || opt > 2) {
                  printf("Opcao fora dos limites.\n");
                }
              } while (flag == 0 || opt < 1 || opt > 2);

              switch (opt) {
                case 1:
                  for (j = 0; j < k; j++) {
                    if (matriz_cinema[acao[j][0]][acao[j][1]] == usrs[usr_idx]) {

                      matriz_cinema[acao[j][0]][acao[j][1]] = 0;

                      usr_seats[usr_idx]--;
                    }
                  }
                  break;
                case 2:
                  break;
              }
              break;
            case 3:
              system("cls");
              printf("Usuario: %d\n\n", usrs[usr_idx]);
              printf("     |    TELA     |\n"
                  "     ---------------\n");

              for (i = 0; i < LIN; i++) {
                printf("%2d | ", i);
                for (j = 0; j < COL; j++) {
                  if (matriz_cinema[i][j] != 0) {
                    if (matriz_cinema[i][j] == usrs[usr_idx]) {
                      printf("X ");
                    } else {
                      printf("1 ");
                    }
                  } else {
                    printf("0 ");
                  }
                }
                printf("\n");
              }
              printf("     ---------------\n");
              printf("     ");
              for (i = 0; i < COL; i++) {
                printf("%d ", i);
              }
              printf("\n\n");

              if (total_oc == TOTAL) {
                printf("Desculpe, a sessao esta cheia.\n\n");
                system("pause");
                break;
              }

              do {
                printf("Digite a quantidade de ingressos desejados: ");
                flag = scanf("%d", &ingressos);

                if (ingressos <= 0 || ingressos > total_liv) {
                  printf( "Quantidade invalida. A sala tem %d assentos livres.\n", total_liv);
                }
              } while (flag == 0 || ingressos <= 0 || ingressos > total_liv);

              printf("\nBuscando lugares...\n\n");

              for (solo = 0; solo < 3; solo++) {
                for (borda = 0; borda < 2; borda++) {

                  for (R = 1; R <= ingressos; R++) {
                    sum_tam = 0;

                    Base = ingressos / R;

                    if (solo == 0 && R > 1 && Base < 2) {
                      continue;
                    }

                    Resto = ingressos % R;

                    cont_r = 0;

                    for (i = 0; i < R; i++) {
                      if (i < Resto) {
                        grupos[i] = Base + 1;
                      } else {
                        grupos[i] = Base;
                      }
                    }

                    for (s = 0; s < R; s++) {
                      sucesso = 0;

                      for (r = 1; r <= grupos[s]; r++) {

                        base = grupos[s] / r;

                        if (solo == 0 && r > 1 && base < 2) {
                          continue;
                        }

                        resto = grupos[s] % r;

                        if (base > COL) {
                          continue;
                        }

                        for (i = 0; i < r; i++) {
                          if (i < resto) {
                            tamanhos[cont_r + i] = base + 1;
                          } else {
                            tamanhos[cont_r + i] = base;
                          }
                        }

                        for (i = 0; i < LIN; i++) {

                          if (i % 2 == 0) {
                            f1 = (LIN + i) / 2;
                          } else {
                            f1 = (LIN - i) / 2;
                          }

                          for (j = 0; j <= COL - tamanhos[cont_r]; j++) {
                            livres = 0;

                            if (j % 2 == 0) {
                              c1 = (COL + j) / 2 - tamanhos[cont_r] / 2;
                            } else {
                              c1 = (COL - j) / 2 - tamanhos[cont_r] / 2;
                            }
                            
                            if (tamanhos[cont_r] == 1) {
                              k = 0;
                              if (c1 < COL - 1) {
                                if (matriz_cinema[f1][c1 + 1] != 0) {
                                  k++;
                                }
                              } else {
                                k++;
                              }
                              if (c1 > 0) {
                                if (matriz_cinema[f1][c1 - 1] != 0) {
                                  k++;
                                }
                              } else {
                                k++;
                              }

                              if ((solo == 0 && k > 0) || (solo == 1 && k > 1)) {
                                continue;
                              }
                            }

                            if (borda == 0 && (c1 + tamanhos[cont_r] == COL || c1 == 0)) {
                              break;
                            }

                            for (k = 0; k < tamanhos[cont_r]; k++) {
                              if (matriz_cinema[f1][c1 + k] == 0) {
                                livres++;
                              }
                            }

                            if (livres == tamanhos[cont_r]) {
                              usada = 0;
                              if (cont_r != 0) {
                                for (u = 0; u < cont_r; u++) {
                                  if (f1 == filas[u]) {
                                    if ((c1 >= cols[u] && c1 <= cols[u] + tamanhos[u] - 1) ||
                                        (cols[u] >= c1 && cols[u] <= c1 + tamanhos[cont_r] - 1)) {
                                      usada = 1;
                                      break;
                                    }
                                  }
                                }
                              }

                              if (usada == 0) {

                                filas[cont_r] = f1;
                                cols[cont_r] = c1;
                                alocados = 1;

                                for (g = 1; g < r; g++) {
                                  achou_g = 0;

                                  for (d = 1; d < r; d++) {
                                    if (d % 2 == 0) {
                                      dir = d / 2;
                                    } else {
                                      dir = -((d + 1) / 2);
                                    }

                                    f_teste = filas[cont_r] + dir;

                                    if (f_teste >= 0 && f_teste < LIN) {
                                      for (offset = 0; offset < 3; offset++) {
                                        switch (offset) {
                                          case 0:
                                            c_teste = c1;
                                            break;
                                          case 1:
                                            c_teste = c1 + 1;
                                            break;
                                          case 2:
                                            c_teste = c1 - 1;
                                            break;
                                        }

                                        if (borda == 0 && (c_teste + tamanhos[cont_r + g] == COL || c_teste == 0)) {
                                          break;
                                        }

                                        usada = 0;
                                        for (u = 0; u <= cont_r + alocados; u++) {
                                          if (f_teste == filas[u]) {
                                            if ((c_teste >= cols[u] &&
                                                  c_teste <= cols[u] + tamanhos[u] - 1) ||
                                                (cols[u] >= c_teste &&
                                                 cols[u] <= c_teste + tamanhos[cont_r + alocados] - 1)) {
                                              usada = 1;
                                              break;
                                            }
                                          }
                                        }

                                        if (usada == 1) {
                                          break;
                                        }

                                        if (c_teste >= 0 && c_teste <= COL - tamanhos[cont_r + g]) {
                                          livres_vizinho = 0;

                                          for (k = 0; k < tamanhos[cont_r + g]; k++) {
                                            if (matriz_cinema[f_teste][c_teste + k] == 0) {
                                              livres_vizinho++;
                                            }

                                          }

                                          if (livres_vizinho == tamanhos[cont_r + g]) {
                                            filas[cont_r + g] = f_teste;
                                            cols[cont_r + g] = c_teste;
                                            alocados++;
                                            achou_g = 1;
                                            break;
                                          }
                                        }
                                      }
                                    }
                                    if (achou_g == 1) {
                                      break;
                                    }
                                  }
                                  if (achou_g == 0) {
                                    break;
                                  }
                                }
                                if (alocados == r) {
                                  sucesso = 1;
                                  break;
                                }
                              }
                            }
                          }
                          if (sucesso == 1) {
                            break;
                          }
                        }
                        if (sucesso == 1) {
                          for (i = 0; i < r; i++) {
                            sum_tam += tamanhos[cont_r + i];
                          }
                          cont_r += r;
                          break;
                        }
                      }
                      if (sum_tam == ingressos) {
                        break;
                      }
                    }
                    if (sum_tam == ingressos) {
                      break;
                    }
                  }
                  if (sum_tam == ingressos) {
                    break;
                  }
                }
                if (sum_tam == ingressos) {
                  break;
                }
              }

              for (i = 0; i < cont_r - 1; i++) {
                for (j = i + 1; j < cont_r; j++) {
                  if ((filas[i] > filas[j]) || (filas[i] == filas[j] && cols[i] > cols[j])) {
                    aux = filas[i];
                    filas[i] = filas[j];
                    filas[j] = aux;

                    aux = cols[i];
                    cols[i] = cols[j];
                    cols[j] = aux;

                    aux = tamanhos[i];
                    tamanhos[i] = tamanhos[j];
                    tamanhos[j] = aux;
                  }
                }
              }

              system("cls");
              printf("Usuario: %d\n\n", usrs[usr_idx]);
              printf("     |    TELA     |\n"
                  "     ---------------\n");

              for (i = 0; i < LIN; i++) {
                printf("%2d | ", i);
                for (j = 0; j < COL; j++) {
                  if (matriz_cinema[i][j] != 0) {
                    if (matriz_cinema[i][j] == usrs[usr_idx]) {
                      printf("X ");
                    } else {
                      printf("1 ");
                    }
                  } else {
                    alt_print = 1;

                    for (k = 0; k < cont_r; k++) {
                      if (filas[k] == i) {
                        for (l = 0; l < tamanhos[k]; l++) {
                          if (cols[k] + l == j) {
                            printf("R ");
                            alt_print = 0;
                            break;
                          }
                        }
                      }

                      if (alt_print == 0) {
                        break;
                      }
                    }

                    if (alt_print == 1) {
                      printf("0 ");
                    }
                  }
                }
                printf("\n");
              }
              printf("     ---------------\n");
              printf("     ");
              for (i = 0; i < COL; i++) {
                printf("%d ", i);
              }
              printf("\n\n");

              printf("Assentos recomendados (R):\n");

              for (i = 0; i < cont_r; i++) {
                if (i == 0 || filas[i] != filas[i - 1]) {
                  printf("Fileira %d, assentos ", filas[i]);
                }

                for (j = 0; j < tamanhos[i]; j++) {
                  printf("%d ", cols[i] + j);
                }

                if (i == cont_r - 1 || filas[i] != filas[i + 1]) {
                  printf("\n");
                }
              }

              printf("\nDeseja reservar esses assentos?\n"
                  "1. Sim\n"
                  "2. Não\n\n");

              do {
                printf("Opcao: ");
                flag = scanf("%d", &opt);
                limparBuffer();

                if (opt < 1 || opt > 2) {
                  printf("Opcao fora dos limites.\n");
                }
              } while (flag == 0 || opt < 1 || opt > 2);

              if (opt == 1) {
                for (i = 0; i < cont_r; i++) {
                  for (j = 0; j < tamanhos[i]; j++) {
                    matriz_cinema[filas[i]][cols[i] + j] = usrs[usr_idx];
                    usr_seats[usr_idx]++;

                  }
                }
              }
              break;

            case 4:
              system("cls");
              printf("Usuario: %d\n\n", usrs[usr_idx]);
              printf("     |    TELA     |\n"
                  "     ---------------\n");

              for (i = 0; i < LIN; i++) {
                printf("%2d | ", i);
                for (j = 0; j < COL; j++) {
                  if (matriz_cinema[i][j] != 0) {
                    if (matriz_cinema[i][j] == usrs[usr_idx]) {
                      printf("X ");
                    } else {
                      printf("1 ");
                    }
                  } else {
                    printf("0 ");
                  }
                }
                printf("\n");
              }
              printf("     ---------------\n");
              printf("     ");
              for (i = 0; i < COL; i++) {
                printf("%d ", i);
              }
              printf("\n\n");


              printf("Total livre: %d\n", total_liv);
              printf("Total ocupado: %d\n", total_oc);
              printf("Percentual de ocupacao: %.2f%%\n",
                  (float)(total_oc * 100) / TOTAL);

              printf("Fileiras livres: ");
              for (int i = 0; i < total_fil_liv; i++) {
                printf("%d ", fil_liv[i]);
              }

              printf("\n\n");

              printf("Fileiras criticas: ");
              if (total_fil_crit == 0) {
                printf("Nenhuma");
              } else {
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

              printf("Fileira mais ocupada: %d (%d assentos)\n", fil_max[0], fil_max[1]);
              printf("Fileira menos ocupada: %d (%d assentos)\n", fil_min[0], fil_min[1]);

              printf("\n");
              system("pause");
              break;

            case 5:
              if (usr_seats[usr_idx] == 0) {
                system("cls");
                printf(
                  "Voce nao reservou assentos. Se sair, seu cadastro sera excluido.\n\n"
                  "Deseja mesmo sair?\n"
                  "1. Sim\n"
                  "2. Nao\n\n"
                );

                do {
                  printf("Opcao: ");
                  flag = scanf("%d", &opt);
                  limparBuffer();

                  if (opt < 1 || opt > 2) {
                    printf("Opcao fora dos limites.\n");
                  }
                } while (flag == 0 || opt < 1 || opt > 2);

                if (opt == 1) {
                  final = 1;
                }
              } else {
                final = 1;
              }

              break;
            default:
              break;
          }
        }
        system("cls");
      }

      if (usr_seats[usr_idx] == 0) {
        usrs[usr_idx] = 0;
      }
    }
  }

  return 0;
}

void limparBuffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
}
