// O consagrado                                       nUSP:
// George Alexandre Gantus                            nUSP: 10691988
// Pedro Paulo Herzog Junior                          nUSP: 10284692

//Neste codigo faremos o uso das system calls getpid,getgid e fork todas relacionadas a gerenciamento de processos
//getpid retorna o id do processo - getpid(void)
//getgid retorna o id do grupo de processos - getgid(void)
//fork cria um novo processo do zero, rodando o mesmo programa do codigo a partir do fork
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
int main(int argc, char const *argv[])
{
    fork();//cria o novo processo
    int id = getpid();//recebe o id do processo
    int ide = getgid();//recebe o id do grupo de processos
    return 0;
    printf("O id do precesso é: %d , e o id do grupo de processo é %d \n",id,ide);//printa os dados obtidos
    return 0;
}
