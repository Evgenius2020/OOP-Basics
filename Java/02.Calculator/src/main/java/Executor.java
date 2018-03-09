import java.util.HashMap;

public abstract class Executor {
    public abstract int getArgsNumber();
    public abstract Object execute(Object[] argv, HashMap<String, Object> definitions);

    public static Object resolveArgumentSource
            (Object argument, HashMap<String, Object> definitions)
            throws ClassCastException {
        if ((argument.getClass() == String.class) &&
                (definitions.containsKey(argument))) {
            return definitions.get(argument);
        }
        return argument;
    }
}