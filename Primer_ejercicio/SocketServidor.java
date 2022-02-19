import java.net.*;
import java.io.*;

//Funcion principal
public class SocketServidor
{    
    public static void main(String[] args) throws IOException {
    
        if (args.length != 1){
            System.err.println("Uso desde consola:  <numero puerto>");

            System.exit(1);
        }

        try
        {
            //System.out.println("SI LLEGAx3");
            int numeroPuerto = Integer.parseInt(args[0]);// convertimos el numero de puerto
            ServerSocket socket = new ServerSocket(Integer.parseInt(args[0]));//escuchando peticiones
            //System.out.println("SI LLEGAx4");
            // Se acepata una conexión con un cliente. Esta llamada se queda
            // bloqueada hasta que se arranque el cliente.
            Socket cliente = socket.accept();
            
            //System.out.println("SI LLEGAx5");
            // Se hace que el cierre del socket 
            cliente.setSoLinger (true, 10);

            // Se prepara un dato para enviar el cliente
            DatoSocket dato = new DatoSocket("Hola que tal");

            // Se prepara un flujo de salida de datos, es decir, la clase encargado de escribir datos en el socket.
            DataOutputStream bufferSalida = 
                new DataOutputStream (cliente.getOutputStream());
            
            // Se envía el dato.
            dato.writeObject (bufferSalida);
            System.out.println ("Servidor envia: " + dato.toString());

            // Se prepara el flujo de entrada de datos, es decir, clase que lee los datos del socket
            DataInputStream bufferEntrada =
               new DataInputStream (cliente.getInputStream());

            // Se crea un dato a leer y se le dice que se rellene con el flujo de entrada de datos.
            DatoSocket aux = new DatoSocket("");
            aux.readObject (bufferEntrada);
            System.out.println ("Servidor recibe: " + aux.toString());
            
            // Se cierra el socket con el cliente setSoLinger()
            cliente.close();
            
            // Se cierra el socket que acepto al cliente
            socket.close();
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }
    }
}