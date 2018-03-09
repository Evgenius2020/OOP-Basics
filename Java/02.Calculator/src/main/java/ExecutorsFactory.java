import java.util.HashMap;

public class ExecutorsFactory {
    HashMap<String, String> _operationExecutorMap;

    public ExecutorsFactory(HashMap<String, String> operationExecutorMap) {
        _operationExecutorMap = operationExecutorMap;
    }

    public Executor getInstance(String operation)
            throws ClassNotFoundException, IllegalAccessException,
            InstantiationException, Exceptions.ExecutorNotDefinedException {
        if (!_operationExecutorMap.containsKey(operation)) {
            throw new Exceptions.ExecutorNotDefinedException();
        }
        String className = _operationExecutorMap.get(operation);
        return (Executor)Class.forName(className).newInstance();
    }
}