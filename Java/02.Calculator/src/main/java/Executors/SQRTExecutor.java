package Executors;

import java.util.HashMap;

public class SQRTExecutor extends Executor {
    @Override
    public int getArgsNumber() {
        return 1;
    }

    @Override
    public Object execute(Object[] argv, HashMap<String, Object> definitions) {
        Double arg = ((Number)resolveArgumentSource(argv[0], definitions)).doubleValue();

        return Math.sqrt(arg);
    }
}
