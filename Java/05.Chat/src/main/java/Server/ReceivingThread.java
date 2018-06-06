package Server;

import java.io.BufferedReader;
import java.util.LinkedList;

public class ReceivingThread implements Runnable {
    private LinkedList<Message> _messageList;
    private String _userName;
    private BufferedReader _inStream;

    ReceivingThread(LinkedList<Message> messageList, String userName, BufferedReader inStream) {
        this._messageList = messageList;
        this._userName = userName;
        this._inStream = inStream;
    }

    public void run() {
        try {
            String messageText;
            do {
                messageText = _inStream.readLine();
                if (messageText.equals("")) {
                    continue;
                }
                Message message = new Message(_userName, messageText);
                addMessage(message);
            } while (!messageText.equals("bye"));
        }
        catch (Exception e) {
            System.err.println("Connection refused");
        }
    }

    private synchronized void addMessage(Message message) {
        _messageList.add(message);
        System.out.println(message);
    }
}