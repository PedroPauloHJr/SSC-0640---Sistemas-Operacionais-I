// George Alexandre Gantus                            nUSP: 10691988
// Pedro Paulo Herzog Junior                          nUSP: 10284692
// Vinícius Molina Garcia                             nUSP:  8929296

//Neste codigo apresentamos um exemplo de aplicação de IO-bound neste caso programas que fazem contagens para sensos de dados que são
//bastante utilizados em instituições como IBGE e etc que estão interessadas em obter informações de um grande volume de dados
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char const *argv[])
{
    //descrição do software
    printf("Senso de jovens, contaremos o numero de pessoas com idade entre 0 e 18 anos de um grupo pessoas.\n");
    //declaração de variaveis
    int i = 0;
    int contador = 0;
    FILE *file = fopen("in.txt","r");
    //trecho do codigo que executa repetidas vezes operações de entra e saida
    while(!feof(file)){
        fscanf(file,"%d ",&i);//le do arquivo os dados de entrada
        if(i >= 0 && i <= 18){
            printf("%d ",i);
            contador++;//operação simples so cpu de realizar um incremento para realizar uma contagem
        }
    }
    //resultado;
    printf("\nNumero de jovens com idade entre 0 e 18 anos: %d \n",contador);
    fclose(file);
    return 0;
}
