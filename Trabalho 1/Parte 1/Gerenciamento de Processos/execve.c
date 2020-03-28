// O consagrado                                       nUSP:
// George Alexandre Gantus                            nUSP: 10691988
// Pedro Paulo Herzog Junior                          nUSP: 10284692


//Neste programa vamos usar a chamada de sistema execve da categoria gerenciamento de processos
//Execve- A chamda de sistema execve cria um processo ao executar um programa neste caso vamos executar o programa que usa as outras system calls de processos
//execve(caminho do arquivo,argumentos,ambiente)
#include <stdio.h>
#include <unistd.h>
int main(void) {
  printf("Programa que chama a main\n");//mostra que este processo é iniciado
  char* argv[] = { "ola", "mundo", NULL };//declara os argumentos usados na abertura do programa
  char* envp[] = { "", "environment", NULL };//o ambiente que vamos utilizar
  execve("./main", argv, envp);//cria o novo processo com o programa
  return 0;
}
