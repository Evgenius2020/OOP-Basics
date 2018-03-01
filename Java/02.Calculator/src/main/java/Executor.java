import java.util.HashMap;

public interface Executor {
    int GetArgsNumber();

    Object execute(Object[] argv, HashMap<String, Object> definitions);
}