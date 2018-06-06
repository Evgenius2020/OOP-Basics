package Server;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.Arrays;
import java.util.LinkedList;

public class ServingThread implements Runnable {
    private Socket _socket;
    private LinkedList<Message> _messageList;

    public ServingThread(Socket socket, LinkedList<Message> messageList) {
        _socket = socket;
        _messageList = messageList;
    }

    @Override
    public void run() {
        try {
            BufferedReader in = new BufferedReader(new InputStreamReader(_socket.getInputStream()));
            PrintWriter out = new PrintWriter(_socket.getOutputStream(), true);

            out.println("What is your name?");
            String userName = in.readLine();
            out.println("Hi, " + userName);
            addMessage(new Message("Server", userName + " is connected."));

            Thread sendingThread = new Thread(new SendingThread(_messageList, userName, out));
            sendingThread.start();
            new Thread(new ReceivingThread(_messageList, userName, in)).run();
            sendingThread.interrupt();

            addMessage(new Message("Server", userName + " is disconnected."));
        }
        catch (Exception e) {
            System.err.println(Arrays.toString(e.getStackTrace()));
        }
        finally {
            System.err.println("Connection refused.");
        }
    }

    private synchronized void addMessage(Message message) {
        _messageList.add(message);
        System.out.println(message);
    }
}
