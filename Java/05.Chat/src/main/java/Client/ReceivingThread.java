package Client;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.Socket;
import java.util.Arrays;

public class ReceivingThread implements Runnable {
    private Socket _socket;

    ReceivingThread(Socket socket) {
        _socket = socket;
    }

    public void run() {
        try {
            BufferedReader in = new BufferedReader(new InputStreamReader(_socket.getInputStream()));
            String receivedString;
            while (true) {
                receivedString = in.readLine();
                System.out.println(receivedString);
            }
        }
        catch (Exception e) {
            System.err.println(Arrays.toString(e.getStackTrace()));
        }
    }
}
