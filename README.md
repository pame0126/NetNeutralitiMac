# NetNeutralitiMac
Tarea del curso Sistemas Operativos. Simulación del comportamiento del NetNeutrality en un restaurante de comida rápida de hamburguesas.

Los pasos a seguir para realizar hamburgesas son:
 - Ejecutar el servidor de Prethreads junto a la interfaz.
   $ ./prethread-Server -p 6667 -n <num_hilos> -r <path_de_imagenes_animación>
   --> -p : indica el puerto del servidor.
   --> -r : indica la ruta de imagenes que se usara para la animación.
   --> -n : cantidad de hilos a cargar.

 - Ejecutar el servidor de Forks.
   $ ./preforked-Server -p 6667 -n <num_procesos> -r <path_de_imagenes_animación>
   --> -p : indica el puerto del servidor.
   --> -r : indica la ruta de imagenes que se usara para la animación.
   --> -n : cantidad de procesos a cargar.

 - Ejecutar el cliente para pedidos
   $ ./client -h 127.0.0.1 -c <prioridad> -p 6667
   --> -h : ip
   --> -c : prioridad (alta/media/baja)
   --> -p : indica el puerto que se conectara.

 - Ejecutar StressCMD
   $ ./stress - <num_pedidos> -h 127.0.0.1 -c <prioridad> -p 6667
   --> -n : número de pedidos que se le cargara al servidor.
   --> -h : ip
   --> -c : prioridad (alta/media/baja)
   --> -p : indica el puerto que se conectara.

El servidor de Forks no esta funcionando bien.
