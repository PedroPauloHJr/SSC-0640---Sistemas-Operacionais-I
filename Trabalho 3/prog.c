
// George Alexandre Gantus                            nUSP: 10691988
// Pedro Paulo Herzog Junior                          nUSP: 10284692
// Vinícius Molina Garcia                             nUSP:  8929296

//Incluindo as bibliotecas necessarias para o programa:
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Le uma linha do arquivo de entrada para a execucao:
int receber_comando(FILE *arquivo, char processo[2], char *comando, int *tamanho)
{
  // Testa se o ponteiro do arquivo esta no final:
  if(feof(arquivo))
  {
    // Se esta no fim do arquivo, retorna sem ler.
    return 1;
  }
  // Lendo um processo por vez:
  fscanf(arquivo, "%s %c %d", processo, comando, tamanho);

  // Retorna com sucesso.
  return 0;
}

// Iniciando o programa propriamente dito:
int main()
{
  // Declarando e alocando as variaveis utilizadas nesta aplicacao:
  int i, tamanho;
  char processo[2], comando;
  FILE *arquivo = fopen("entrada.txt", "r");

  // Teste de integridade do arquivo de entrada:
  if(arquivo == NULL)
  {
    printf("ARQUIVO DE ENTRADA NAO ENCONTRADO\n");
    return 1;
  }

  // Teste de integridade da leitura do arquivo de entrada:
  if(receber_comando(arquivo, processo, &comando, &tamanho) == 1)
  {
    printf("FALHA NA LEITURA DO ARQUIVO\n");
    return 1;
  }

  // Encerrando o programa:
  fclose(arquivo);
  return EXIT_SUCCESS;
}
