#include <stdio.h>
#include <stdlib.h>

#define LIN 10
#define COL 8
#define TOTAL (LIN * COL)

int main() {
  int seats[LIN][COL] = {0}, usrs[TOTAL] = {0}, pwds[TOTAL], resrv[TOTAL][TOTAL][2] = {-1},
      usr_seats[TOTAL], usr_idx, login, pwd, final = 0, opt, total_usrs = 0, alt_print = 1, qtd_seats, fileira_resrv, coluna_resrv, free_seats = TOTAL;
  // Inicializar assentos reservados
  // Nenhum assento está reservado
  // As coordenadas de cada assento
  // não devem coincidir com coordenadas existentes na sala

  system("cls");

  // Teste
  total_usrs = 2;

  usrs[0] = 999;
  pwds[0] = 123;
  usr_seats[0] = 3;

  resrv[0][0][0] = 2;
  resrv[0][0][1] = 3;

  resrv[0][1][0] = 2;
  resrv[0][1][1] = 4;

  resrv[0][2][0] = 2;
  resrv[0][2][1] = 5;

  usrs[1] = 888;
  pwds[1] = 543;
  usr_seats[1] = 5;

  resrv[1][0][0] = 4;
  resrv[1][0][1] = 1;

  resrv[1][1][0] = 4;
  resrv[1][1][1] = 2;

  resrv[1][2][0] = 4;
  resrv[1][2][1] = 3;

  resrv[1][3][0] = 4;
  resrv[1][3][1] = 4;

  resrv[1][4][0] = 4;
  resrv[1][4][1] = 5;

  for (int i = 0; i < total_usrs; i++) {
    for (int j = 0; j < usr_seats[i]; j++) {
      seats[resrv[i][j][0]][resrv[i][j][1]] = 1;
    }
  }
  // Fim do teste

  while (1) {
    printf("Login/Cadastro: ");
    scanf("%d", &login);

    // Ver se login já existe
    // Se existir, pegar o índice
    // Se não, colocar um índice fora do limite
    // Não aceitar login = 0
    if (login != 0) {
      for (int i = 0; i < TOTAL; i++) {
        if (usrs[i] == login) {
          usr_idx = i;
          break;
        } else {
          usr_idx = TOTAL;
        }
      }
    } else {
      system("cls");
      printf("Login nao pode ser 0\n");
      continue;
    }

    // Se o índice estiver fora do limite,
    // o login ainda não existe -> Pedir criação de senha
    if (usr_idx == TOTAL) {
      // Procurar
      for (int i = 0; i < TOTAL; i++) {
        if (usrs[i] == 0) {
          usr_idx = i;
          break;
        }
      }
      printf("Criar senha: ");
      scanf("%d", &pwds[usr_idx]);
      usrs[usr_idx] = login;
      pwd = pwds[usr_idx];
      total_usrs++;
    } else {
      printf("Senha: ");
      scanf("%d", &pwd);
    }

    // Checar se a senha está correta
    if (pwd != pwds[usr_idx]) {
      system("cls");
      printf("Login ou senha invalidos\n");
    } else {
      final = 0;

      while (final == 0) {
        // Impressão dos assentos
        system("cls");

        printf("     |    TELA     |\n"
               "     ---------------\n");

        for (int i = 0; i < LIN; i++) {
          printf("%2d | ", i);
          for (int j = 0; j < COL; j++) {
            alt_print = 1;
            for (int k = 0; k < usr_seats[usr_idx]; k++) {
              // Se as coordenadas do assento corresponderem a algum assento
              // reservado pelo usr, imprimir x
              // Caso contrário, imprimir o estado do assento (0 ou 1)
              if (resrv[usr_idx][k][0] == i && resrv[usr_idx][k][1] == j) {
                printf("x ");
                alt_print = 0;
              }
            }
            if (alt_print == 1) {
              printf("%d ", seats[i][j]);
            }
          }
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
               "x: Seus assentos\n"
               "1: Assentos ocupados\n"
               "0: Assentos livres\n\n");

        // Impressão do menu
        printf("Opcoes:\n"
               "1. Comprar ingresso\n"
               "2. Cancelar ingresso\n"
               "3. Recomendacao de assentos\n"
               "4. Finalizar atendimento\n");

        printf("\nOpcao: ");
        scanf("%d", &opt);

        switch (opt) {
          case 1:
              do {
                printf("Digite a quantidade de ingressos que quer comprar:");
                scanf("%d", &qtd_seats);
              } while (qtd_seats > free_seats); // executa novamente se a quantidade de assentos solicitados for maior que o disponível


                // seleção das poltronas
                int count_seats = 0;
                while (count_seats < qtd_seats) {

                    do {
                        printf("Selecione a fileira do %dº ingresso: ", count_seats + 1);
                        scanf("%d", &fileira_resrv);
                        if (fileira_resrv < 0 || fileira_resrv >= LIN){
                            printf("Posicao invalida. Tente novamente.\n");
                        }
                    } while (fileira_resrv < 0 || fileira_resrv >= LIN);

                    do {
                        printf("Selecione a coluna do %dº ingresso: ", count_seats + 1);
                        scanf("%d", &coluna_resrv);
                        if (fileira_resrv < 0 || fileira_resrv >= LIN){
                            printf("Posicao invalida. Tente novamente.\n");
                        }
                    } while (coluna_resrv < 0 || coluna_resrv >= COL);

                    // verificar se ocupado
                    if (seats[fileira_resrv][coluna_resrv] != 0) {
                        printf("Assento ocupado. Escolha outro.\n");
                        continue;
                    }

                    // marcar como ocupado
                    seats[fileira_resrv][coluna_resrv] = 1;

                    // salvar na matriz
                    resrv[usr_idx][usr_seats[usr_idx]][0] = fileira_resrv;
                    resrv[usr_idx][usr_seats[usr_idx]][1] = coluna_resrv;

                    usr_seats[usr_idx]++;

                    printf("Ingresso %d reservado com sucesso!\n", count_seats + 1);

                    //incrementa o contador de assentos comprados
                    count_seats++;
                }
                // atualiza a quantidade de assentos livres
                free_seats -= qtd_seats;
                break;
          case 2:
              break;
          case 3:
              break;
          case 4:
            final = 1;
            break;
          // default:
        }
      }
      system("cls");
    }

    if (usr_seats[usr_idx] == 0) {
      usrs[usr_idx] = 0;
    }
  }

  return 0;
}
