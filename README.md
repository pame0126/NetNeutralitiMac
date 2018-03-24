# NetNeutralitiMac
Tarea del curso Sistemas Operativos. Simulación del comportamiento del NetNeutrality en un restaurante de comida rápida de hamburguesas.

Los pasos a seguir para realizar hamburgesas son:
 - Ejecutar el servidor de <hilos>.
   $ ./prethread-Server -p 6667 -n <#_hilos> -r <path_de_imagenes_animación>
   --> -p : indica el puerto del servidor.
   --> -r : indica la ruta de imagenes que se usara para la animación.
   --> -n : cantidad de hilos a cargar.

 - Ejecutar el cliente para pedidos
   $ ./client -h 127.0.0.1 -c <prioridad> -p 6667
   --> -h : ip
   --> -c : prioridad (alta/media/baja)
   --> -p : indica el puerto que se conectara.
