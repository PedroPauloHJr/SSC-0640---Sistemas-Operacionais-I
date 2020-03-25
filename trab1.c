// O consagrado                                       nUSP:
// George Alexandre Gantus                            nUSP: 10691988
// Pedro Paulo Herzog Junior                          nUSP: 10284692

// Neste programa, veremos o uso de 3 primitivas de chamadas de sistema da categoria
// de gerenciamento de E/S e arquivos: open, write e close.
// open eh uma chamada de sistema que eh usada para abrir um novo arquivo e obter o seu descritor:
// open(nome do arquivo, metodos de abertura, permissoes)
// write eh uma chamada de sistema que eh usada para escrever os dados de um buffer:
// write(descritor do arquivo, buffer com os dados a serem escritos, numero de bytes a serem escritos)
// close eh uma chamada de sistema que eh usada para fechar um decritor de arquivo aberto:
// close(descritor do arquivo)

// Bibliotecas utilizadas:
#include <fcntl.h>
#include <unistd.h>

// Iniciando o programa:
int main(void)
{
  // Criando o arquivo e obtendo o seu descritor:
  int filedesc, flag;
  filedesc = open("file.txt", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);

  // Verificando a integridade do arquivo:
  if(filedesc < 0)
  {
    // Caso haja algum erro durante a criacao do arquivo, imprime uma mensagem de erro e encerra o programa.
    write(2, "Erro durante a execução do programa.\n", 28);
    return 1;
  }

  // Escrevendo no arquivo criado:
  if(write(filedesc, "Trabalho 1 de S.O. I.\n", 22) != 22)
  {
    // Caso haja algum erro durante a escrita, imprime uma mensagem de erro e encerra o programa.
    write(2, "Erro durante a execução do programa.\n", 28);
    close(filedesc);
    return 1;
  }

  // Fecha o arquivo criado:
  if(close(filedesc) < 0)
  {
      return 1;
  }

  // Se o programa chegou ate aqui, imprime uma mensagem de sucesso:
  write(1, "Programa executado com sucesso.\n", 32);

  // Encerra o programa:
  return 0;
}
