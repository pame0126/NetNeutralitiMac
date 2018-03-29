#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "interfaz.h"
#include "archivos.h"

/* GtkWidget punteroa a objetos*/
        GtkWidget *window;
        GtkWidget *button;
        GtkWidget *box;
        GtkWidget *boxInicial;
        GtkWidget *boxLabel;
        
        GtkWidget *separator;
        GtkWidget *label;
        GtkWidget *quitbox;
        
        GtkWidget *image;
        
/**************************************************************************/

/* This is a callback function. The data arguments are ignored
 * in this example. More on callbacks below. */
void hello( GtkWidget *widget, gpointer   data )
{
        g_print ("Hello World\n");
}

gint delete_event( GtkWidget *widget,
                   GdkEvent  *event,
                   gpointer   data )
{

        g_print ("delete event occurred\n");

        return TRUE;
}

/* Another callback */
void destroy( GtkWidget *widget, gpointer   data )
{
        gtk_main_quit ();
}

void imagenes_conversion_ruta(char*dir, char*com1, char*com2, char*n_gif){
	strcpy(com1, "mogrify -resize  420x420 ");
    strcpy(com2, "convert -delay 100 -loop 0 ");

	strcat(com1, dir);
	strcat(com1, "*.png");

	strcat(com2, dir);
	strcat(com2, "*.png ");
	strcat(n_gif, dir);
	strcat(n_gif, "migif.gif");
	strcat(com2, n_gif);
}
void gtk_agregar_label_msj(GtkWidget *widget, gpointer data){
	//elimina el label anterior
	gtk_widget_destroy(label);
	/* Crea otra etiqueta y la muestra. */
	char*msj = leer_fichero();
   label = gtk_label_new (msj);
					gtk_misc_set_alignment (GTK_MISC (label), 0, 0);
					gtk_box_pack_start (GTK_BOX (boxLabel), label, FALSE, FALSE, 0);
					gtk_widget_show (label);
}
int interfaz(char*ruta)
{

        char*msj = calloc(1000, sizeof(char));
        strcpy(msj, "Ordenes de McNetNeutrality\t\t\t\t\t\t\n");
        char*dir = ruta;
        
        char*command1 = calloc(1000,sizeof(char));
        char*command2 = calloc(1000,sizeof(char));
        char*nombre_gif = calloc(100,sizeof(char));
		
		imagenes_conversion_ruta(dir, command1, command2, nombre_gif);
		system(command1);//es para redimensionar las imágenes al mismo tamaño
		system(command2);//es para crear el gif en base a las imagenes

        /* Inicializa el GTK de al ventana tomando encuenta las entradas */
        gtk_init (NULL, NULL);

        /*Crea una nueva ventana*/
        window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

        /* Señal para eliminar evento de la ventana*/
        g_signal_connect (G_OBJECT (window), "delete_event",
                          G_CALLBACK (destroy), NULL);

        /* Señal para destruir la ventana*/
        g_signal_connect (G_OBJECT (window), "destroy",
                          G_CALLBACK (destroy), NULL);

        /* Modifica la dimension de la ventana en pixeles */
        gtk_container_set_border_width (GTK_CONTAINER (window), 10);
		
		
		
		/*Crea cajas verticales inicial*/
		boxInicial = gtk_vbox_new (FALSE, 0);
		/*Agrega un boton*/
		button = gtk_button_new_with_label ("Refresh");
		//gtk_misc_set_alignment (GTK_MISC (button), 0, 0);
					gtk_box_pack_start (GTK_BOX (boxInicial), button, FALSE, FALSE, 0);
					gtk_widget_show (button);
		
		g_signal_connect (G_OBJECT (button), "clicked",
                             G_CALLBACK (gtk_agregar_label_msj), NULL);
		
		/*Crea cajas horizontales*/
		box = gtk_hbox_new (FALSE, 0);
		
		/* crea una etiqueta. */
				/*Imagen nueva*/
				image = gtk_image_new_from_file (nombre_gif);

                /* Alínea la etiqueta a la izquierda.  Se hablará más adelante de esta
                 * función. */
                gtk_misc_set_alignment (GTK_MISC (image), 0, 0);

                /* Coloca la etiqueta dentro de la caja vertical (hbox box).  Los
                 * widgets que se añaden a una vbox se colocan, por orden, uno
                 * encima del otro. */
                gtk_box_pack_start (GTK_BOX (box), image, FALSE, FALSE, 0);

                /* Muestra la etiqueta */
                gtk_widget_show (image);
                
                
                
                /* Crea un separador, se verán más adelante,
                 * aunque son bastante sencillos. */
                separator = gtk_vseparator_new ();
                
                /* Coloca el separador en una vbox. Todos estos
                 * widgets han sido colocados en una vbox, así que estarán
                 * ordenados verticalmente. */
                gtk_box_pack_start (GTK_BOX (box), separator, FALSE, TRUE, 5);
                gtk_widget_show (separator);
                
                
                
                /*Pila para los labels*/
                boxLabel = gtk_vbox_new (FALSE, 0);
                
                
                /* Crea otra etiqueta y la muestra. */
                label = gtk_label_new (msj);
					gtk_misc_set_alignment (GTK_MISC (label), 0, 0);
					gtk_box_pack_start (GTK_BOX (boxLabel), label, FALSE, FALSE, 0);
					gtk_widget_show (label);
				
                gtk_box_pack_start (GTK_BOX (box), boxLabel, FALSE, FALSE, 0);
                gtk_widget_show (boxLabel);
                
        /*Al conjunto de cajas verticales se agrega las cajas horizontales*/
        gtk_box_pack_start (GTK_BOX (boxInicial), box, FALSE, FALSE, 0);
        gtk_widget_show (box);
        
        /*Se agrega como componente la caja inicial vertical*/
        gtk_container_add (GTK_CONTAINER (window), boxInicial);

        /*Se muestrasn los componentes*/
        
        gtk_widget_show (boxInicial);
        gtk_widget_show (window);
			
	
        /*Bucle*/
        gtk_main ();

        return 0;
}
