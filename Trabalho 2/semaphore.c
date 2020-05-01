// George Alexandre Gantus                            nUSP: 10691988
// Pedro Paulo Herzog Junior                          nUSP: 10284692
// Vinícius Molina Garcia                             nUSP:  8929296

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>//Biblioteca responsavel pela criação e controle das threads
#include <semaphore.h>//Bliblioteca responsavel pela criação e controle dos semaforos
#include <unistd.h>
#define TAM_FILA 10//tamanho do Buffer
#define PREENCHIMENTO 100//Quantos elementos serao produzidos/consumidos

//Declaração do buffer
int buffer[TAM_FILA];
//Declaração dos semaforos
sem_t mutex;
sem_t vazio;
sem_t ocupado;
//Funcao que sera executada pela thread consumidor
void *consumidor(){
    for(int i = 0;i < PREENCHIMENTO;i++){
        sem_wait(&ocupado);//verifica se o semafoto que representa os espaços ocupados esta com valor zero se sim a thread dorme, se nao executa o down e a thread prossegue
        sem_wait(&mutex);//thread para garantir acesso unico a regiao critica
        buffer[i%TAM_FILA] = 0;    //Regiao Critica
        sem_post(&mutex);//Libera o acesso à regiao critica
        printf("Consumi na posicao %d\n",i);
        sem_post(&vazio);//Executa um Up no semaforo que representa os espaços vazios
    }
}
//Função que sera executada pela thread consumidor
void *produtor(){
    for(int i = 0; i <PREENCHIMENTO;i++){
        sem_wait(&vazio);//verifica se o semafoto que representa os espaços vazios esta com valor zero se sim a thread dorme, se nao executa o down e a thread prossegue
        sem_wait(&mutex);//Thread para garantir exclusao mutua no acesso à regiao critica
        buffer[i%TAM_FILA] = i;   //Regiao Critica
        sem_post(&mutex);//Libera o acesso à regiao critica
        printf("Produzi na posicao %d\n",i);
        sem_post(&ocupado);//Executa um Up no semaforo que representa os espaços vazios
    }
}

int main(int argc, char const *argv[]){
    //Declaração das threads
    pthread_t tProdutor,tConsumidor;
    //Inicialização dos semaforos
    sem_init(&mutex,0,1);
    sem_init(&vazio,0,TAM_FILA);
    sem_init(&ocupado,0,0);
    //Inicialização das threads
    pthread_create(&tProdutor,NULL,produtor,NULL);
    pthread_create(&tConsumidor,NULL,consumidor,NULL);
    //Comandos para garantir que as threads terminem sua execução
    pthread_join(tConsumidor,NULL);
    pthread_join(tProdutor,NULL);
    //Destruindo os semaforos
    sem_destroy(&vazio);
    sem_destroy(&ocupado);
    sem_destroy(&mutex);


    return 0;
}
