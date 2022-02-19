#include <stdio.h>
#include </home/edgar/Escritorio/sistemas/Socket_Cliente.h>
#include </home/edgar/Escritorio/sistemas/Socket.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h> 
#include <unistd.h> 
#include <arpa/inet.h>

int main (){
	//Socket y variables autilizar 
	int Socket_Con_Servidor;
	int Longitud_Cadena = 0;
	int Aux;
	char Cadena[100];

	
	//Se abre la conexion con el servidor, en este caso la direccion es "localhost"->Misma maquina
	//"cpp_java" es un servicio dado de alta en /etc/services.
   	//El servicio debe ser 35557 que es el puerto que va a atender el servidor
   	//java.s
	*/
	Socket_Con_Servidor = Abre_Conexion_Inet ("localhost", "cpp_java");
	if (Socket_Con_Servidor == 1)
	{
		printf ("No puedo establecer conexion con el servidor\n");
		exit (-1);
	}

   // Se lee un entero con la longitud de la cadena
   Lee_Socket (Socket_Con_Servidor, (char *)&Aux, sizeof(int));
   Longitud_Cadena = ntohl (Aux);
   

   //Se lee la cadena de la longitud indicada
   Lee_Socket (Socket_Con_Servidor, Cadena, Longitud_Cadena);
   printf ("Cliente recibe: %s\n", Cadena);
   
	//Se envia la cadena en este caso Cliente: Hola
	strcpy (Cadena, "Hola");
   	Longitud_Cadena = 6;

   //Se tranforma en formato de red para que ambos programas se puedan comunicar correctamente
   //Esto lo podemos lograr gracias a la funcion htonl();
   //htonl() pasa un entero de formato hardware (el del micro) a formato red (Hardware TO Network).
   Aux = htonl (Longitud_Cadena);
   Escribe_Socket (Socket_Con_Servidor, (char *)&Aux, sizeof(Longitud_Cadena));
 

   /* Se envía la cadena */
	Escribe_Socket (Socket_Con_Servidor, Cadena, Longitud_Cadena);
   printf ("Cliente envia: %s\n", Cadena);

	/*
	* Se cierra el socket con el servidor
	*/
	close (Socket_Con_Servidor);
}