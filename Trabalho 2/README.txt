Aqui encontraremos o trabalho 2 realizado na disciplina. Nesta resolução,
podemos notar dois arquivos .c. Isso porque, o semphore.c foi desenvolvido utilizando
a biblioteca semaphore.h e a pthreads.h, enquanto o pthread.c foi desenvolvido
com a pthreads.h apenas (além das bibliotecas padrão).

Para compilar o programa, temos:
	gcc pthread.c -lptread -o pthread
                ou
  	gcc semphore.c -lptread -o semaphore
Para executar o programa, temos:
	./pthread
  	./semaphore
