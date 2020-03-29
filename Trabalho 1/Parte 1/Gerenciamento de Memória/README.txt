Para compilar o programa, temos:
	gcc mmap.c -o mmap
	gcc sbrk_brk.c -o sbrk_brk
	gcc sbrk.c -o sbrk
Para executar o programa, temos:
	./mmap
	./sbrk_brk
	./sbrk
O arquivo "strace (uso de chamadas ao sistema).txt" trata-se do log que contém as estatísticas 
relacionadas ao uso de chamadas ao sistema em cada um dos programas desenvolvidos.
O arquivo "strace (tempo gasto).txt" contém a relação de todas as system calls invocadas pela 
aplicação e tempo gasto por cada uma delas.
O arquivo "file.txt" é criado durante a execução do programa que contém uma das saídas do mesmo.
