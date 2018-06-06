package Server;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.LinkedList;

public class ServingThread implements Runnable {
    private Socket _socket;
    private LinkedList<Message> _messageList;

    ServingThread(Socket socket, LinkedList<Message> messageList) {
        this._socket = socket;
        this._messageList = messageList;
    }

    public void run() {
        try {
            BufferedReader in = new BufferedReader(new InputStreamReader(_socket.getInputStream()));
            PrintWriter out = new PrintWriter(_socket.getOutputStream(), true);

            out.println("What is your name?");
            String userName = in.readLine();
            out.println("Hi, " + userName);
            addMessage(new Message("Server", userName + " is connected."));

            String messageText;
            int messagesFromIndex = 0;
            do {
                addMessagesToClient(messagesFromIndex, userName, out);
                messagesFromIndex = _messageList.size();
                messageText = in.readLine();
                if (messageText.equals("")) {
                    continue;
                }
                Message message = new Message(userName, messageText);
                addMessage(message);
            } while (!messageText.equals("bye"));

            addMessage(new Message("Server", userName + " is disconnected."));
        }
        catch (Exception e) {
            System.err.println("Connection refused");
        }
    }

    private synchronized void addMessagesToClient(int fromIndex, String username, PrintWriter out) {
        for(int i = fromIndex; i < _messageList.size(); i++) {
            Message message = _messageList.get(i);
            if (message.username.equals(username)) {
                continue;
            }
            out.println(message);
        }
    }

    private synchronized void addMessage(Message message) {
        _messageList.add(message);
        System.out.println(message);
    }
}