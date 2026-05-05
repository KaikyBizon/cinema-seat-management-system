# Geral

| Formato | Variável      | Descrição                                       |
| ------- | ------------- | ----------------------------------------------- |
| Matriz  | matriz_cinema | Representa a sala de cinema                     |
| Matriz  | acao          | Seleção de assentos para compra ou cancelamento |
| Int     | opt           | Opção do menu                                   |
| Int     | i, j, k, l    | Iteradores diversos                             |
| Int     | flag          | Valor de retorno do scanf                       |
| Int     | aux           | Variável auxiliar para ordenação de subgrupos   |
| Int     | sucesso       | Indica que algo foi bem-sucedido                |
| Int     | erro          | Indica que um erro ocorreu                      |
| Int     | alt_print     | Indica o símbolo a ser impresso na tela         |
| Int     | final         | Indica a finalização do atendimento             |

# Gerenciamento de usuários

| Formato | Variável   | Descrição                           |
| ------- | ---------- | ----------------------------------- |
| Matriz  | resrv      | Assentos pertencentes a usuários    |
| Vetor   | usrs       | Identificadores de usuários         |
| Vetor   | pwds       | Senhas dos usuários                 |
| Vetor   | usr_seats  | Quantidade de assentos de usuários  |
| Int     | usr_idx    | Índice do usuário atual             |
| Int     | login      | Indentificador do usuário atual     |
| Int     | pwd        | Senha do usuário atual              |
| Int     | total_usrs | Número total de usuários no sistema |

# Estatísticas

| Formato | Variável       | Descrição                                         |
| ------- | -------------- | ------------------------------------------------- |
| Vetor   | fil_max        | Coordenadas da maior fileira                      |
| Vetor   | fil_min        | Coordenadas da menor fileira                      |
| Vetor   | fil_liv        | Fileiras livres                                   |
| Vetor   | fil_crit       | Fileiras críticas (> 75%)                         |
| Vetor   | rest_liv_crit  | Número de assentos livres em cada fileira crítica |
| Int     | total_liv      | Número de assentos livres                         |
| Int     | total_oc       | Número de assentos ocupados                       |
| Int     | total_fil_liv  | Número de fileiras livres                         |
| Int     | total_fil_crit | Número de fileiras críticas                       |
| Int     | oc_fil         | Número de assentos ocupados na fileira analisada  |

# Recomendação de assentos

| Formato | Variável       | Descrição                                                                       |
| ------- | -------------- | ------------------------------------------------------------------------------- |
| Vetor   | grupos         | Subdivisão do total de pessoas em grupos menores                                |
| Vetor   | tamanhos       | Tamanho da sequência contínua de pessoas em assentos na mesma fileira           |
| Vetor   | filas          | Fileira de cada subgrupo                                                        |
| Vetor   | cols           | Coluna em que cada subgrupo começa                                              |
| Int     | ingressos      | Total de ingressos que o usuário deseja reservar                                |
| Int     | R              | Número de blocos menores do total de pessoas                                    |
| Int     | s              | Indica qual grupo está sendo analisado                                          |
| Int     | r              | Número de divisões do bloco menor                                               |
| Int     | g              | Contador que indica qual subgrupo está sendo testado                            |
| Int     | u, v           | Interadores para checar se o assento já está sendo usado                        |
| Int     | d              | Contador que utilizado para calcular a direção de busca                         |
| Int     | dir            | Direção da busca da fileira                                                     |
| Int     | f1             | Fileira do primeiro subgrupo                                                    |
| Int     | c1             | Coluna do primeiro subgrupo                                                     |
| Int     | offset         | Deslocamento da coluna para busca                                               |
| Int     | f_teste        | Fileira testada para as pessoas restantes                                       |
| Int     | c_teste        | Coluna testada para as pessoas restantes                                        |
| Int     | alocados       | Contador de grupos com lugar encontrado                                         |
| Int     | livres         | Número de assentos livres encontrado em sequência                               |
| Int     | Base           | Tamanho base dos grupos menores independentes                                   |
| Int     | base           | Tamanho base dos subgrupos                                                      |
| Int     | Resto          | Resto da divisão (número de grupos menores com um integrante a mais)            |
| Int     | resto          | Resto da subdivisão (número de subgrupos com um integrante a mais)              |
| Int     | achou_g        | Indica que um lugar foi encontrado para um subgrupo                             |
| Int     | usada          | Indica que a fileira já está sendo usada por um subgrupo                        |
| Int     | livres_vizinho | Assentos livres na fileira testada                                              |
| Int     | cont_r         | Zero relativo na análise de subgrupos                                           |
| Int     | sum_tam        | Soma dos tamanhos dos subgrupos                                                 |
| Int     | canto          | Indica se os cantos devem ser contados na análise                               |
| Int     | solo           | Indica o grau em que é permitido deixar uma pessoa isolada no meio de estranhos |
