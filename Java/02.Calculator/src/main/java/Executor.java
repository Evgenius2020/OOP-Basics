import java.util.HashMap;

public interface Executor {
    int getArgsNumber();
    Object execute(Object[] argv, HashMap<String, Object> definitions);
}