package Server;

import java.net.ServerSocket;
import java.util.Arrays;
import java.util.LinkedList;

public class Server {
    public static void main(String args[]) {
        try {
            ServerSocket serverSocket = new ServerSocket(8080);
            LinkedList<Message> messageList = new LinkedList<>();
            System.out.println("Started listening at " + serverSocket.getLocalSocketAddress());
            while (true) {
                new Thread(new ServingThread(serverSocket.accept(), messageList)).start();
                System.out.println("New client is connected.");
            }
        }
        catch (Exception e) {
            System.err.print(Arrays.toString(e.getStackTrace()));
        }
    }
}

