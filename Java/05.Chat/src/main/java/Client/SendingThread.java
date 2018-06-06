package Client;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.Arrays;

public class SendingThread implements Runnable {
    private Socket _socket;

    SendingThread(Socket socket) {
        _socket = socket;
    }

    public void run() {
        try {
            PrintWriter out = new PrintWriter(_socket.getOutputStream(), true);
            BufferedReader isReader = new BufferedReader(new InputStreamReader(System.in));
            while (true) {
                out.println(isReader.readLine());
            }
        }
        catch (Exception e) {
            System.err.println(Arrays.toString(e.getStackTrace()));
        }
    }
}
