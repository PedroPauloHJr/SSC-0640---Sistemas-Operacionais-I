Para compilar o programa, temos:
	gcc execve.c -o execve
	gcc main.c -o main
Para executar o programa, temos:
	./execve
O arquivo "strace (uso de chamadas ao sistema).txt" trata-se do log que contém as estatísticas 
relacionadas ao uso de chamadas ao sistema em cada um dos programas desenvolvidos.
O arquivo "strace (tempo gasto).txt" contém a relação de todas as system calls invocadas pela 
aplicação e tempo gasto por cada uma delas.
