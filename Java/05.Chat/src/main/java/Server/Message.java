package Server;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class Message {
    public final String time;
    public final String username;
    public final String text;

    Message(String username, String message) {
        this.username = username;
        this.text = message;
        DateTimeFormatter _timeFormat = DateTimeFormatter.ofPattern("HH:mm:ss");
        this.time = LocalDateTime.now().format(_timeFormat);
    }

    @Override
    public String toString() {
        return String.format("[%s]%s: %s", time, username, text);
    }
}
