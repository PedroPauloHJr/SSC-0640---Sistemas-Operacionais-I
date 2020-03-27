#include <stdio.h>
#include <unistd.h>
int main(void) {
  void *a = sbrk(0);//pega o final atual do programa
  int *p = (int *)a;//faz a conversao do valor do ponteiro para inteiro
  brk(p+10);//seta o novo final para o final +10 bytes
  printf("memoria é %d",*p);
}
