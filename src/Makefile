all:
	gcc -o prethread-Server thpool.h thpool.c hamburgesa.h hamburgesa.c servidorPrethread.h servidorPrethread.c -pthread
	gcc hamburgesa.h hamburgesa.c cliente.h cliente.c main.c -o client

prethread-server:
	gcc -o prethread-Server thpool.h thpool.c hamburgesa.h hamburgesa.c servidorPrethread.h servidorPrethread.c -pthread
client:
	gcc hamburgesa.h hamburgesa.c cliente.h cliente.c main.c -o client
