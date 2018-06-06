package Server;

import java.io.PrintWriter;
import java.util.LinkedList;

public class SendingThread implements Runnable {
    private LinkedList<Message> _messageList;
    private String _userName;
    private PrintWriter _outStream;

    SendingThread(LinkedList<Message> messageList, String userName, PrintWriter outstream)
    {
        this._messageList = messageList;
        this._userName = userName;
        this._outStream = outstream;
    }

    @Override
    public void run() {
        int messagesFromIndex = 0;
        while (true) {
            addMessagesToClient(messagesFromIndex, _userName, _outStream);
            messagesFromIndex = _messageList.size();
        }
    }

    private synchronized void addMessagesToClient(int fromIndex, String username, PrintWriter outStream) {
        for(int i = fromIndex; i < _messageList.size(); i++) {
            Message message = _messageList.get(i);
            if (message.username.equals(username)) {
                continue;
            }
            outStream.println(message);
        }
    }
}
