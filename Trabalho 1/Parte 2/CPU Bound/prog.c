// O consagrado                                       nUSP:
// George Alexandre Gantus                            nUSP: 10691988
// Pedro Paulo Herzog Junior                          nUSP: 10284692

// Neste programa, geraremos a Sequencia de Fibonacci, com o intuito de demonstrar que ele
// trata-se de um programa orientado a CPU (CPU Bound).

// Bibliotecas utilizadas:
#include <stdio.h>

// Funcao que calcula a Sequencia de Fibonacci por recursao. Este algoritmo recursivo
// torna o programa CPU Bound.
int fibonacci(int n)
{
  // Caso seja o primeiro ou o segundo termo da sequencia, retorna os valores iniciais (1):
  if((n == 1) || (n == 2))
  {
    return 1;
  }

  // Se nao, calcula o proximo termo da sequencia, somando os dois termos anteriores, por recursao:
  return (fibonacci(n - 1) + fibonacci(n - 2));
}

// Iniciando o programa:
int main(void)
{
  // Declarando as variaveis necssarias para a execucao do algoritmo:
  int n, i;

  // Recebe do usuario o tamanho da sequencia desejada:
  printf("Quantos termos voce quer na Sequencia de Fibonacci?\n");
  scanf("%d", &n);

  // Imprimindo a Sequencia de Fibonacci no tamanho desejado:
  for(i = 0; i < n; i++)
  {
    printf("%d ", fibonacci((i + 1)));
  }
  printf("\n");

  // Encerra o programa:
  return 0;
}
