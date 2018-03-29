all:
	gcc -o prethread-Server thpool.h thpool.c hamburgesa.h hamburgesa.c servidorPrethread.h servidorPrethread.c -pthread
	gcc hamburgesa.h hamburgesa.c cliente.h cliente.c ordenes.h ordenes.c -o client
	gcc -o preforked-Server hamburgesa.h hamburgesa.c servidorForks.c
	gcc hamburgesa.h hamburgesa.c cliente.h cliente.c ordenes.h ordenes.c -o stress
	

prethread-server:
	gcc archivos.* interfaz.h interfaz.c thpool.h thpool.c hamburgesa.h hamburgesa.c servidorPrethread.h servidorPrethread.c -o prueba -pthread `pkg-config --cflags --libs gtk+-2.0`
preforked-Server:
	gcc -o preforked-Server hamburgesa.h hamburgesa.c servidorForks.c
client:
	gcc archivos.* hamburgesa.h hamburgesa.c cliente.h cliente.c ordenes.h ordenes.c -o client
stress:
	gcc hamburgesa.h hamburgesa.c cliente.h cliente.c ordenes.h ordenes.c -o stress
gtk-interfaz:
	gcc archivos.* interfaz.h interfaz.c -o io `pkg-config --cflags --libs gtk+-2.0`

prueba:
	gcc archivos.* interfaz.h interfaz.c thpool.h thpool.c hamburgesa.h hamburgesa.c servidorPrethread.h servidorPrethread.c -o prueba -pthread `pkg-config --cflags --libs gtk+-2.0`
