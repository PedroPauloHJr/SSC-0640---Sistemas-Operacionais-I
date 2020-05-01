#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define TAM_FILA 10//Tamanho do Buffer
#define PREENCHIMENTO 100//Quantos elementos serao produzidos/consumidos
//declaração do buffer
int buffer[TAM_FILA];
//declaração dos semaforos/condiçoes
pthread_mutex_t mutex  = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  cheio   = PTHREAD_COND_INITIALIZER;
pthread_cond_t  vazio   = PTHREAD_COND_INITIALIZER;
//Variaveis de controle das condições
int prod = TAM_FILA;//Representa quantos espaços temos para produzir
int consu = 0;//representa quantos espaços precisam ser consumidos
//funcao que sera executada pela thread consumidor
void *consumidor(){
    for(int i = 0;i < PREENCHIMENTO;i++){
        pthread_mutex_lock(&mutex);//trava o acesso ao recurso
        //verifica as condições envolvidas
        while(!consu){
            pthread_cond_wait(&cheio,&mutex);//Caso faltem recursos a thread entra em estado de espera, e libera o acesso ao buffer
        }
        buffer[i%TAM_FILA] = 0;    //Regiao Critica
        //Atualiza as variaveis de controle das condições/recursos
        prod++;
        consu--;
        pthread_cond_signal(&vazio);//Envia um sinal para as threads q estavam em estado de wait, avisando que agora existem espaços vazios
        printf("Consumi na posicao %d\n",i);
        pthread_mutex_unlock(&mutex);//libera o acesso ao buffer
    }
}
//funcao que sera executada pela thread do produtor
void *produtor(){
    for(int i = 0; i <PREENCHIMENTO;i++){
        pthread_mutex_lock(&mutex);//trava o acesso ao recurso
        //verifica as condições necessarias para que o produtor execute
        while(!prod){
            pthread_cond_wait(&vazio,&mutex);//Caso faltem recursos a thread entra em estado de espera e libera o acesso ao buffer
        }
        buffer[i%TAM_FILA] = i;   //Regiao Critica
         //Atualiza as variaveis de controle das condições/recursos
        prod--;
        consu++;
        pthread_cond_signal(&cheio);//Envia um sinal para as threads q estavam em estado de wait, avisando que agora existem espaços ocupados
        printf("Produzi na posicao %d\n",i);
        pthread_mutex_unlock(&mutex);//Libera o acesso ao buffer
    }
}

int main(int argc, char const *argv[]){
    //Declaração das Threads
    pthread_t tProdutor,tConsumidor;
    //Incialização das threads
    pthread_create(&tProdutor,NULL,produtor,NULL);
    pthread_create(&tConsumidor,NULL,consumidor,NULL);
    //Comandos para garantir a execução completa das threads
    pthread_join(tConsumidor,NULL);
    pthread_join(tProdutor,NULL);
    return 0;
}
