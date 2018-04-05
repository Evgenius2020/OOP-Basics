package Executors;

import java.util.HashMap;

public class DivisionExecutor extends Executor {
    @Override
    public int getArgsNumber() {
        return 2;
    }

    @Override
    public Object execute(Object[] argv, HashMap<String, Object> definitions) {
        Double left = ((Number) Executor.resolveArgumentSource(argv[0], definitions)).doubleValue();
        Double right = ((Number) Executor.resolveArgumentSource(argv[1], definitions)).doubleValue();

        return left / right;
    }
}
