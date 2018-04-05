package Executors;

import java.util.HashMap;

public class PlusExecutor extends Executor {
    @Override
    public int getArgsNumber() {
        return 2;
    }

    @Override
    public Object execute(Object[] argv, HashMap<String, Object> definitions) {
        Double left = ((Number)resolveArgumentSource(argv[0], definitions)).doubleValue();
        Double right = ((Number)resolveArgumentSource(argv[1], definitions)).doubleValue();

        return left + right;
    }
}
