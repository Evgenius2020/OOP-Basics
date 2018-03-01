import java.util.HashMap;
import java.util.Stack;

public class Calculator {
    private HashMap<String, Object> _definitions;
    private Stack<Object> _stack;
    private ExecutorsFactory _factory;

    public Calculator(ExecutorsFactory factory) {
        _definitions = new HashMap<>();
        _stack = new Stack<>();
        _factory = factory;
    }

    public Stack<Object> getStack() {
        return _stack;
    }

    public HashMap<String, Object> getDefinitions() {
        return _definitions;
    }

    public void executeOperation(String operation) throws Throwable {
        Executor executor = _factory.getInstance(operation);
        int argc = executor.GetArgsNumber();
        if (argc > _stack.size()) {
            throw new Exception(Exceptions.NotEnoughArguments);
        }
        Object[] argv = new Object[argc];
        for (int i = 0; i < argc; i++) {
            argv[i] = _stack.pop();
        }
        Object result = executor.execute(argv, _definitions);
        _stack.push(result);
    }

    public void drop() {
        _definitions = new HashMap<>();
        _stack = new Stack<>();
    }
}