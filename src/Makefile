all:
	gcc -o prethread-Server thpool.h thpool.c hamburgesa.h hamburgesa.c servidorPrethread.h servidorPrethread.c -pthread
	gcc hamburgesa.h hamburgesa.c cliente.h cliente.c ordenes.h ordenes.c -o client
	gcc -o preforked-Server hamburgesa.h hamburgesa.c servidorForks.c
	gcc hamburgesa.h hamburgesa.c cliente.h cliente.c ordenes.h ordenes.c -o stress

prethread-server:
	gcc -o prethread-Server thpool.h thpool.c hamburgesa.h hamburgesa.c servidorPrethread.h servidorPrethread.c -pthread
preforked-Server:
	gcc -o preforked-Server hamburgesa.h hamburgesa.c servidorForks.c
client:
	gcc hamburgesa.h hamburgesa.c cliente.h cliente.c ordenes.h ordenes.c -o client
stress:
	gcc hamburgesa.h hamburgesa.c cliente.h cliente.c ordenes.h ordenes.c -o stress
