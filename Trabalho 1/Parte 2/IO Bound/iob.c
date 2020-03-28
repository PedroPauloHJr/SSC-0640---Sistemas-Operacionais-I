// O consagrado                                       nUSP:
// George Alexandre Gantus                            nUSP: 10691988
// Pedro Paulo Herzog Junior                          nUSP: 10284692

//Neste codigo apresentamos um exemplo de aplicação de IO-bound neste caso programas que fazem contagens para sensos de dados que são
//bastante utilizados em instituições como IBGE e etc que estão interessadas em obter informações de um grande volume de dados
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char const *argv[])
{
    //descrição do software
    printf("Senso de jovens, contaremos o numero de pessoas com idade entre 0 e 18 anos de um grupo pessoas Digite -1 terminar sair\n");
    //declaração de variaveis
    int i = 0;
    int contador = 0;
    //trecho do codigo que executa repetidas vezes operações de entra e saida
    while(i >= 0){
        print("digite uma idade:");
        scanf("%d ",&i);//le do arquivo os dados de entrada
        printf("\n");
        if(i >= 0 && i <= 18){
            contador++;//operação simples so cpu de realizar um incremento para realizar uma contagem
        }
    }
    //resultado;
    printf("O numero de jovens é %d \n",contador);
    return 0;
}
