import java.util.HashMap;

public class PlusExecutor implements Executor {
    @Override
    public int getArgsNumber() {
        return 2;
    }

    Number resolveArgumentSource(Object obj, HashMap<String, Object> definitions) throws ClassCastException {
        if (obj.getClass() == String.class) {
            return (Number)definitions.get(obj);
        }
        if (obj instanceof Number){
            return (Number)obj;
        }
        return null;
    }

    @Override
    public Object execute(Object[] argv, HashMap<String, Object> definitions) throws ClassCastException{
        Double left = resolveArgumentSource(argv[0], definitions).doubleValue();
        Double right = resolveArgumentSource(argv[1], definitions).doubleValue();

        return left + right;
    }
}
