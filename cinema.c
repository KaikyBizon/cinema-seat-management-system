#include <stdio.h>
#include <stdlib.h>

#define LIN 10
#define COL 8
#define TOTAL (LIN * COL)
#define MAX_GRUPOS ((TOTAL + 1) / 2)

void limparBuffer();

int main() {
  int matriz_cinema[LIN][COL] = {0};
  int usrs[TOTAL] = {0};
  int pwds[TOTAL];
  int usr_seats[TOTAL] = {0};
  int usr_idx;
  int login;
  int pwd;
  int final;
  int opt;
  int total_usrs = 0;
  int alt_print, acao[TOTAL][2];

  int resrv[LIN][COL] = {0};

  // Variáveis para estatísticas
  int fil_crit[LIN];
  int fil_liv[LIN];
  int total_liv;
  int total_oc;
  int total_fil_liv;
  int total_fil_crit;
  int oc_fil;
  int fil_max[2];
  int fil_min[2];
  int rest_liv_crit[LIN];

  int grupos[MAX_GRUPOS];
  int tamanhos[MAX_GRUPOS]; // guarda quantas pessoas ficam em cada subgrupo
  int filas[MAX_GRUPOS];    // guarda em qual linha cada subgrupo vai sentar
  int cols[MAX_GRUPOS];     // guarda em qual coluna cada subgrupo comeca

  int ingressos; // quantidade total de ingressos que o usuario vai digitar
  int R, r;      // em quantas partes o grupo esta sendo dividido
  int i;         // contador linhas
  int j;         // contador colunas
  int k;         // contador pra checar os assentos um do lado do outro
  int g;         // contador que indica qual subgrupo esta sendo testado
  int d;
  int s;
  int f1;  // fileira onde o primeiro grupo vai tentar sentar
  int c1;  // coluna onde o primeiro grupo vai tentar sentar
  int dir; // direcao da busca (1 pra olhar a fileira de tras, -1 pra olhar a da
           // frente)
  int offset;   // deslocamento pro switch (0 = meio, 1 = direita, 2 = esquerda)
  int f_teste;  // fileira que o codigo testa pros amigos que sobraram
  int c_teste;  // coluna que o codigo testa pros amigos que sobraram
  int sucesso;  // avisa o programa se achou lugar pra todo mundo (1) ou nao (0)
  int v;        // iteradores auxiliares para checar fileiras vizinhas
  int alocados; // contador de quantos subgrupos ja acharam lugar
  int erro;
  int livres;
  int Base, base;
  int Resto, resto;
  int achou_g;
  int usada;
  int livres_vizinho;
  int cont_r;
  int sum_tam;
  int aux;
  int flag;

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

    // Ver se login já existe
    // Se existir, pegar o índice
    // Se não, colocar um índice fora do limite
    // Não aceitar login = 0
    for (i = 0; i < TOTAL; i++) {
      if (usrs[i] == login) {
        usr_idx = i;
        break;
      } else {
        usr_idx = TOTAL;
      }
    }
    // Se o índice estiver fora do limite,
    // o login ainda não existe -> Pedir criação de senha
    erro = 0;
    if (usr_idx == TOTAL) {
      // Procurar
      for (i = 0; i < TOTAL; i++) {
        if (usrs[i] == 0) {
          usr_idx = i;
          break;
        }
      }

      if (i == TOTAL - 1 && usrs[i] != 0) {
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
        total_usrs++;
      }
    } else {
      do {
        printf("Senha: ");
        flag = scanf("%d", &pwd);
        limparBuffer();
      } while (flag == 0);
    }

    // Checar se a senha está correta
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

          // Impressão dos assentos
          system("cls");

          printf("Usuario: %d\n\n", usrs[usr_idx]);
          printf("     |    TELA     |\n"
              "     ---------------\n");

          for (i = 0; i < LIN; i++) {
            // assentos ocupados na fileira
            oc_fil = 0;

            printf("%2d | ", i);
            for (j = 0; j < COL; j++) {
              alt_print = 1;

              // Estatisticas
              oc_fil += matriz_cinema[i][j];
              // Fim das estatisticas

              if (resrv[i][j] == usrs[usr_idx]) {
                printf("X ");
              } else {
                printf("%d ", matriz_cinema[i][j]);
              }
            }

            // Estatisticas
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
            // Fim das estatisticas

            printf("\n");
          }
          printf("     ---------------\n");
          printf("     ");
          for (int i = 0; i < COL; i++) {
            printf("%d ", i);
          }
          printf("\n\n");
          // Fim da impressão dos assentos

          // Impressão da legenda
          printf("Legenda:\n"
              "X: Seus assentos\n"
              "1: Assentos ocupados\n"
              "0: Assentos livres\n\n");

          // Impressão do menu
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
            // Compra
            case 1:
              // Impressão dos assentos
              system("cls");
              printf("Usuario: %d\n\n", usrs[usr_idx]);
              printf("     |    TELA     |\n"
                  "     ---------------\n");

              for (i = 0; i < LIN; i++) {
                printf("%2d | ", i);
                for (j = 0; j < COL; j++) {
                  if (resrv[i][j] == usrs[usr_idx]) {
                    printf("X ");
                  } else {
                    printf("%d ", matriz_cinema[i][j]);
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
              // Fim da impressão dos assentos

              sucesso = 0;
              g = 0;
              while (sucesso == 0) {
                if (total_oc == TOTAL) {
                  printf("Desculpe, a sessao esta cheia.\n\n");
                  system("pause");
                  break;
                }

                erro = 0;
                printf("Comprar:\n");

                do {
                  printf("  Fileira: ");
                  flag = scanf("%d", &acao[g][0]);
                  limparBuffer();

                  if (acao[g][0] < 0 || acao[g][0] >= LIN) {
                    printf("Fileira fora dos limites. Tente novamente.\n");
                  }
                } while (flag == 0 || acao[g][0] < 0 || acao[g][0] >= LIN);

                do {
                  printf("  Assento: ");
                  flag = scanf("%d", &acao[g][1]);
                  limparBuffer();

                  if (acao[g][1] < 0 || acao[g][1] >= COL) {
                    printf("Assento fora dos limites. Tente novamente.\n");
                  }
                } while (flag == 0 || acao[g][1] < 0 || acao[g][1] >= COL);

                if (matriz_cinema[acao[g][0]][acao[g][1]] == 1) {
                  printf("Esse assento ja esta ocupado! Tente novamente.\n\n");
                } else {
                  for (i = 0; i < g; i++) {
                    if (acao[i][0] == acao[g][0] && acao[i][1] == acao[g][1]) {
                      printf("Esse assento ja esta sendo processado.\n\n");
                      erro = 1;
                      break;
                    }
                  }
                  if (erro == 0) {
                    g++;
                    // Impressão dos assentos
                    system("cls");
                    printf("Usuario: %d\n\n", usrs[usr_idx]);
                    printf("     |    TELA     |\n"
                        "     ---------------\n");

                    for (i = 0; i < LIN; i++) {
                      printf("%2d | ", i);
                      for (j = 0; j < COL; j++) {
                        if (resrv[i][j] == usrs[usr_idx]) {
                          printf("X ");
                        } else {
                          alt_print = 1;
                          for (r = 0; r < g; r++) {
                            if (acao[r][0] == i && acao[r][1] == j) {
                              printf("C ");
                              alt_print = 0;
                              break;
                            }
                          }
                          if (alt_print == 1) {
                            printf("%d ", matriz_cinema[i][j]);
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
                    printf("C: Assentos a serem comprados\n\n");
                    // Fim da impressão dos assentos

                    printf("Finalizar compra?\n"
                        "1. Sim\n"
                        "2. Nao\n"
                        "3. Excluir compra\n\n");

                    do {
                      printf("Opcao: ");
                      flag = scanf("%d", &opt);
                      limparBuffer();

                      if (opt < 1 || opt > 3) {
                        printf("Opcao fora dos limites.\n");
                      }
                    } while (flag == 0 || opt < 1 || opt > 3);

                    switch (opt) {
                      case 1:
                        for (j = 0; j < g; j++) {
                          resrv[acao[j][0]][acao[j][1]] = usrs[usr_idx];
                          usr_seats[usr_idx]++;

                          matriz_cinema[acao[j][0]][acao[j][1]] = 1;
                        }
                        sucesso = 1;
                        break;
                      case 2:
                        break;
                      case 3:
                      default:
                        sucesso = 1;
                    }
                  }
                  printf("\n");
                }
              }

              break;
              // Cancela
            case 2:
              // Impressão dos assentos
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
                  if (resrv[i][j] == usrs[usr_idx]) {
                    printf("X ");
                  } else {
                    printf("%d ", matriz_cinema[i][j]);
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
              // Fim da impressão dos assentos

              sucesso = 0;
              g = 0;
              while (sucesso == 0) {
                printf("Cancelar:\n");

                do {
                  printf("  Fileira: ");
                  flag = scanf("%d", &acao[g][0]);
                  limparBuffer();

                  if (acao[g][0] < 0 || acao[g][0] >= LIN) {
                    printf("Fileira fora dos limites. Tente novamente.\n");
                  }
                } while (flag == 0 || acao[g][0] < 0 || acao[g][0] >= LIN);

                do {
                  printf("  Assento: ");
                  flag = scanf("%d", &acao[g][1]);
                  limparBuffer();

                  if (acao[g][1] < 0 || acao[g][1] >= COL) {
                    printf("Assento fora dos limites. Tente novamente.\n");
                  }
                } while (flag == 0 || acao[g][1] < 0 || acao[g][1] >= COL);

                if (matriz_cinema[acao[g][0]][acao[g][1]] == 0) {
                  printf("Esse assento ja esta livre. Tente novamente.\n");
                } else {
                  erro = 1;

                  for (i = 0; i < g; i++) {
                    if (acao[i][0] == acao[g][0] && acao[i][1] == acao[g][1]) {
                      printf("Esse assento ja esta sendo processado.\n\n");
                      erro = 2;
                      break;
                    }

                  }

                  if (erro == 1 && resrv[acao[g][0]][acao[g][1]] == usrs[usr_idx]) {
                    g++;
                    erro = 0;
                  }

                  if (erro == 1) {
                    printf("Esse assento foi reservado por outro usuario. Tente novamente.\n");
                  } else {
                    // Impressão dos assentos
                    system("cls");
                    printf("Usuario: %d\n\n", usrs[usr_idx]);
                    printf("     |    TELA     |\n"
                        "     ---------------\n");

                    for (i = 0; i < LIN; i++) {
                      printf("%2d | ", i);
                      for (j = 0; j < COL; j++) {
                        alt_print = 1;
                        for (r = 0; r < g; r++) {
                          if (acao[r][0] == i && acao[r][1] == j) {
                            printf("E ");
                            alt_print = 0;
                            break;
                          }
                        }
                        if (alt_print == 1) {
                          if (resrv[i][j] == usrs[usr_idx]) {
                            printf("X ");
                          } else {
                            printf("%d ", matriz_cinema[i][j]);
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
                    printf("E: Assentos a serem cancelados\n\n");
                    // Fim da impressão dos assentos
                    printf("Finalizar cancelamento?\n"
                        "1. Sim\n"
                        "2. Nao\n"
                        "3. Excluir cancelamento\n\n");

                    do {
                      printf("Opcao: ");
                      flag = scanf("%d", &opt);
                      limparBuffer();

                      if (opt < 1 || opt > 3) {
                        printf("Opcao fora dos limites.\n");
                      }
                    } while (flag == 0 || opt < 1 || opt > 3);

                    switch (opt) {
                      case 1:
                        for (j = 0; j < g; j++) {
                          if (resrv[acao[j][0]][acao[j][1]] == usrs[usr_idx]) {
                            matriz_cinema[acao[j][0]][acao[j][1]] = 0;

                            resrv[acao[j][0]][acao[j][1]] = 0;

                            usr_seats[usr_idx]--;
                          }
                        }
                        sucesso = 1;
                        break;
                      case 2:
                        break;
                      case 3:
                      default:
                        sucesso = 1;
                        break;
                    }
                  }
                }
                printf("\n");
              }
              break;
              // Recomenda
            case 3:
              // Impressão dos assentos
              system("cls");
              printf("Usuario: %d\n\n", usrs[usr_idx]);
              printf("     |    TELA     |\n"
                  "     ---------------\n");

              for (i = 0; i < LIN; i++) {
                printf("%2d | ", i);
                for (j = 0; j < COL; j++) {
                  if (resrv[i][j] == usrs[usr_idx]) {
                    printf("X ");
                  } else {
                    printf("%d ", matriz_cinema[i][j]);
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
              // Fim da impressão dos assentos

              if (total_oc == TOTAL) {
                printf("Desculpe, a sessao esta cheia.\n\n");
                system("pause");
                break;
              }

              do {
                printf("Digite a quantidade de ingressos desejados: ");
                flag = scanf("%d", &ingressos);

                // previne que o usuario peca mais lugares do que a sala tem ou
                // valores negativos
                if (ingressos <= 0 || ingressos > total_liv) {
                  printf( "Quantidade invalida. A sala tem %d assentos livres.\n", total_liv);
                }
              } while (flag == 0 || ingressos <= 0 || ingressos > total_liv);

              printf("\nBuscando lugares...\n\n");

              // calcula o limite de grupos (ex: 7 ingressos / 2 = maximo de 3
              // grupos)

              // tenta nao dividir (r=1), se falhar divide em 2 (r=2), etc.
              for (R = 1; R <= ingressos; R++) {
                sum_tam = 0;

                Base = ingressos / R;
                Resto = ingressos % R;

                cont_r = 0;

                for (i = 0; i < R; i++) {
                  if (i < Resto) {
                    grupos[i] = Base + 1; // os primeiros grupos ganham a sobra
                  } else {
                    grupos[i] = Base; // o resto fica com a quantidade base
                  }
                }

                for (s = 0; s < R; s++) {
                  sucesso = 0;

                  for (r = 1; r <= grupos[s]; r++) {

                    // quantas pessoas vao ficar em cada grupo por padrao
                    base = grupos[s] / r;
                    // quem sobrou da divisao e precisa de um assento extra
                    resto = grupos[s] % r;

<<<<<<< HEAD
                      if (base > COL) {
                        continue;
=======
                    if (base > COL) {
                      continue;
                    }

                    // distribui as pessoas nos subgrupos
                    for (i = 0; i < r; i++) {
                      if (i < resto) {
                        tamanhos[cont_r + i] =
                          base + 1; // os primeiros grupos ganham a sobra
                      } else {
                        tamanhos[cont_r + i] =
                          base; // o resto fica com a quantidade base
                      }
                    }

                    // procura lugar pro grupo1 alternando do centro pros cantos
                    for (i = 0; i < LIN; i++) {

                      if (i % 2 == 0) {
                        f1 = (LIN + i) / 2;
                      } else {
                        f1 = (LIN - i) / 2;
>>>>>>> e906962 (Modificação na armazenagem de assentos do usr e proteção contra chars)
                      }

                      // desliza pela fileira testando as colunas
                      for (j = 0; j <= COL - tamanhos[cont_r]; j++) {
                        livres = 0; // conta quantos zeros achou em sequencia

                        // analisa sequencias de assentos do centro para fora
                        if (j % 2 == 0) {
                          c1 = (COL + j) / 2 - tamanhos[cont_r] / 2;
                        } else {
                          c1 = (COL - j) / 2 - tamanhos[cont_r] / 2;
                        }

                        // verifica os assentos lado a lado pro tamanho do grupo 1
                        for (k = 0; k < tamanhos[cont_r]; k++) {
                          if (matriz_cinema[f1][c1 + k] == 0) {
                            livres++;
                          }
                        }

                        // se a quantidade de zeros for igual ao tamanho do grupo
                        // 1, achou lugar
                        if (livres == tamanhos[cont_r]) {
                          filas[cont_r] = f1; // guarda a linha do grupo 1
                          cols[cont_r] = c1;  // guarda a coluna do grupo 1
                          alocados =
                            1; // marca que ja guardamos lugar pra 1 subgrupo

                          // tenta encaixar o resto do pessoal estritamente colado
                          // aos que ja sentaram
                          for (g = 1; g < r; g++) {
                            achou_g = 0; // avisa se achou lugar pra esse subgrupo
                                         // (g) especifico

                                         // tenta colar na fileira de tras (+1) ou da frente
                                         // (-1) dos amigos
                            for (d = 1; d <= r; d++) {
                              if (d % 2 == 0) {
                                dir = d / 2;
                              } else {
                                dir = -((d + 1) / 2);
                              }

                              f_teste = filas[cont_r] + dir; // calcula a fileira vizinha exata

                              // verifica se a fileira vizinha existe (nao saiu da
                              // matriz)
                              if (f_teste >= 0 && f_teste < LIN) {

                                // checa se essa fileira ja nao esta sendo usada
                                // pelo proprio grupo
                                usada = 0;
                                for (v = 0; v < cont_r + alocados; v++) {
                                  if (filas[v] == f_teste) {
                                    usada = 1;
                                  }
                                }

                                // se a fileira esta livre pra gente expandir o
                                // bloco
                                if (usada == 0) {

                                  // tenta alinhar a coluna (mesma coluna, puxa
                                  // pra direita, puxa pra esquerda)
                                  for (offset = 0; offset < 3; offset++) {
                                    switch (offset) {
                                      case 0:
                                        c_teste = c1;
                                        break; // fica embaixo ou em cima
                                      case 1:
                                        c_teste = c1 + 1;
                                        break; // puxa um pro lado
                                      case 2:
                                        c_teste = c1 - 1;
                                        break; // puxa um pro outro
                                    }

                                    // garante que a coluna de teste nao estoure a
                                    // parede da sala
                                    if (c_teste >= 0 &&
                                        c_teste <= COL - tamanhos[cont_r + g]) {
                                      livres_vizinho =
                                        0; // conta os zeros da vizinhanca

                                      for (k = 0; k < tamanhos[cont_r + g]; k++) {
                                        if (matriz_cinema[f_teste][c_teste + k] ==
                                            0) {
                                          livres_vizinho++;
                                        }
                                      }

                                      // se os lugares baterem com o tamanho desse
                                      // subgrupo
                                      if (livres_vizinho == tamanhos[cont_r + g]) {
                                        filas[cont_r + g] = f_teste; // salva a fileira vizinha pra ele
                                        cols[cont_r + g] = c_teste; // salva a coluna dele
                                        alocados++;  // registra que mais um grupo cresceu o bloco
                                        achou_g = 1; // marca que deu certo pra ele
                                        break; // sai do for
                                      }
                                    }
                                  }
                                }
                              }
                              if (achou_g == 1) {
                                break; // sai do laco de direcao se ja achou
                              }
                            }
                            if (achou_g == 0) {
                              break; // se nao achou lugar colado pra esse
                                     // subgrupo, a divisao toda falha
                            }
                          }

                          // se a quantidade de grupos colados for a mesma
                          // necessária
                          if (alocados == r) {
                            sucesso = 1; // deu tudo certo
                            break;       // para de tentar outras colunas
                          }
                        }
                      }
                      if (sucesso == 1) {
                        break; // para de testar outras linhas pro grupo principal
                      }
                    }
                    if (sucesso == 1) {
                      for (i = 0; i < r; i++) {
                        sum_tam += tamanhos[cont_r + i];
                      }
                      cont_r += r;
                      break; // para de tentar novas divisoes se a atual ja formou
                             // o bloco
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
                  if (filas[i] > filas[j]) {
                    aux = filas[i];
                    filas[i] = filas[j];
                    filas[j] = aux;
                  }
                }
              }

              // Impressão dos assentos
              system("cls");
              printf("Usuario: %d\n\n", usrs[usr_idx]);
              printf("     |    TELA     |\n"
                  "     ---------------\n");

              for (i = 0; i < LIN; i++) {
                printf("%2d | ", i);
                for (j = 0; j < COL; j++) {
                  alt_print = 1;
                  if (resrv[i][j] == usrs[usr_idx]) {
                    printf("X ");
                    alt_print = 0;
                  } else {
                    for (r = 0; r < cont_r; r++) {
                      if (filas[r] == i) {
                        for (s = 0; s < tamanhos[r]; s++) {
                          if (cols[r] + s == j) {
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
                      printf("%d ", matriz_cinema[i][j]);
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
              // Fim da impressão dos assentos

              printf("Assentos recomendados (R):\n");

              for (i = 0; i < cont_r; i++) {
                printf("Fileira %d, assentos ", filas[i]);
                for (j = 0; j < tamanhos[i]; j++) {
                  printf("%d ", cols[i] + j);
                }
                printf("\n");
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
                    resrv[filas[i]][cols[i] + j] = usrs[usr_idx];
                    usr_seats[usr_idx]++;

                    matriz_cinema[filas[i]][cols[i] + j] = 1;
                  }
                }
              }

              break;
              // Estatísticas
            case 4:
              // Impressão dos assentos
              system("cls");
              printf("Usuario: %d\n\n", usrs[usr_idx]);
              printf("     |    TELA     |\n"
                  "     ---------------\n");

              for (i = 0; i < LIN; i++) {
                printf("%2d | ", i);
                for (j = 0; j < COL; j++) {
                  if (resrv[i][j] == usrs[usr_idx]) {
                    printf("X ");
                  } else {
                    printf("%d ", matriz_cinema[i][j]);
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
              // Fim da impressão dos assentos

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
              // Sair
            case 5:
              final = 1;
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
