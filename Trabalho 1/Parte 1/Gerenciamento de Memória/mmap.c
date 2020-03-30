// George Alexandre Gantus                            nUSP: 10691988
// Pedro Paulo Herzog Junior                          nUSP: 10284692
// Vinícius Molina Garcia                             nUSP:  8929296

/*Neste caso trabalhamos com uma chamada de sistema deveras interessante: a mmpap. Esta realiza o mapeamento de arquvios na memória,
de forma que a escrita e leitura em arquivos possa ser feita como simples escriras e leituras em memória*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#define FILEPATH "./teste.txt"
#define NUMINTS  (1000)
#define FILESIZE (NUMINTS * sizeof(int))

int writef()
{
    int i;
    int fd;
    int result;
    int *map;  //vetor de inteiros a ser mapeado

    /* Abrir o arquivo para realizar a escrita
     *  - Cria o arquivo se este não existe.
     *  - Trunca seu tamanho para 0 se ele já existe.
     *
     * Note: não é suficiente utilizar o método "O_WRONLY" ao realizar o mmap
     */
    fd = open(FILEPATH, O_RDWR | O_CREAT | O_TRUNC, (mode_t)0600);
    if (fd == -1) {
    perror("Erro ao abrir o arquivo");
    exit(EXIT_FAILURE);
    }

    /* Seta o tamanho do arquivo para o tamanho do array de inteiros
     */
    result = lseek(fd, FILESIZE-1, SEEK_SET);
    if (result == -1) {
    close(fd);
    perror("Error calling lseek() to 'stretch' the file");
    exit(EXIT_FAILURE);
    }
    
    /* Alguma coisa precisa ser escrita no arquivo para ele adquirir o novo tamanho, então colocamos um caracter '\0' ao final do mesmo.
     */
    result = write(fd, "", 1);
    if (result != 1) {
    close(fd);
    perror("Error writing last byte of the file");
    exit(EXIT_FAILURE);
    }

    /* Agora o arquivo está pronto para ser mapeado na memória.
     */
    map = (int*)mmap(0, FILESIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (map == MAP_FAILED) {
    close(fd);
    perror("Error mmapping the file");
    exit(EXIT_FAILURE);
    }
    
    /* Agora podemos escrever o array de inteiros na memória.
     */
    for (i = 1; i <=NUMINTS; ++i) {
    map[i] = 2 * i; 
    }

    /* Liberamos a memória mapeada
     */
    if (munmap(map, FILESIZE) == -1) {
    perror("Error un-mmapping the file");
    }

    /* Desmapear não fecha o arquivo, então fazemos esta parte agora.
     */
    close(fd);
    return 0;
}
int readf()
{
    int i;
    int fd;
    int *map; 

    fd = open(FILEPATH, O_RDONLY);
    if (fd == -1) {
    perror("Error opening file for reading");
    exit(EXIT_FAILURE);
    }

    map = mmap(0, FILESIZE, PROT_READ, MAP_SHARED, fd, 0);
    if (map == MAP_FAILED) {
    close(fd);
    perror("Error mmapping the file");
    exit(EXIT_FAILURE);
    }
    
    /* Lê o arquivo inteiro por inteiro através do mapeamento
     */
    for (i = 1; i <=NUMINTS; ++i) {
    printf("%d: %d\n", i, map[i]);
    }

    if (munmap(map, FILESIZE) == -1) {
    perror("Error un-mmapping the file");
    }
    close(fd);
    return 0;
}

int main(int argc, char *argv[]){
  writef();
  readf();

  return 0;

}
