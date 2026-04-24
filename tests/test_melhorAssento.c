#include <stdio.h>

int main() {
    int total_pessoas = 10; // Exemplo que você deu
    int max_fileiras = total_pessoas / 2; // O máximo de fileiras é dividir em duplas

    printf("--- Buscando melhores distribuicoes para %d pessoas ---\n\n", total_pessoas);

    // Testamos dividir em 2 fileiras, depois 3, até o limite de duplas...
    for (int r = 2; r <= max_fileiras; r++) {

        int base = total_pessoas / r;
        int resto = total_pessoas % r;

        // REGRA DE OURO: O menor grupo possível é a 'base'.
        // Se a base for maior ou igual a 2, ninguém fica sozinho!
        if (base >= 2) {
            printf("Opcao dividindo em %d fileiras:\n", r);

            // 1. Primeiro, imprimimos os grupos que recebem o "resto" (base + 1)
            for (int i = 0; i < resto; i++) {
                printf(" -> %d amigos juntos\n", base + 1);
            }

            // 2. Depois, imprimimos os grupos com o tamanho base
            for (int i = 0; i < (r - resto); i++) {
                printf(" -> %d amigos juntos\n", base);
            }
            printf("\n");

            // OBS: Se você quiser apenas a "melhor" opção (2 fileiras),
            // você pode colocar um 'break;' aqui para ele parar na primeira que encontrar!
        }
    }

    return 0;
}
