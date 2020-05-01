Aqui encontraremos o trabalho 2 realizado na disciplina. Nesta resolução,
podemos notar dois arquivos .c. Isso porque, o semphore.c foi desenvolvido utilizando
a biblioteca semaphore.h e a pthreads.h, enquanto o pthread.c foi desenvolvido
com a pthreads.h apenas (além das bibliotecas padrão). Ambos, resolvem o problema 
proposto pelo o trabalho.

Para compilar o programa, temos:
	gcc pthread.c -lpthread -o pthread
                ou
  	gcc semaphore.c -lpthread -o semaphore
Para executar o programa, temos:
	./pthread
  	./semaphore
