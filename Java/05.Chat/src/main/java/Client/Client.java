package Client;

import java.net.Socket;
import java.util.Arrays;

public class Client {
    public static void main(String[] args) {
        try {
            Socket socket = new Socket("0.0.0.0", 8080);
            new Thread(new SendingThread(socket)).start();
            new Thread(new ReceivingThread(socket)).start();
        }
        catch (Exception e) {
            System.err.println(Arrays.toString(e.getStackTrace()));
        }
    }
}
