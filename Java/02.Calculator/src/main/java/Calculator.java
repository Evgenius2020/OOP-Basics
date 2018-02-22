import java.util.HashMap;
import java.util.Stack;

public class Calculator {
    private Stack<Object> _stack;
    private HashMap<String, Object> _defines;
    private ExecutorsFactory _factory;

    public Calculator(ExecutorsFactory factory) {
        _stack = new Stack<Object>();
        _defines = new HashMap<String, Object>();
        _factory = factory;
    }

    public Object Pop() {
        return _stack.pop();
    }

    public void Push(Object value) {
        _stack.push(value);
    }

    public String Print() {
        return _stack.peek().toString();
    }

    public void ExecuteOperation(String operation) throws Throwable {
        Executor executor = _factory.GetInstance(operation);
        int argc = executor.GetArgsNumber();
        if (argc > _stack.size()) {
            throw new Exception(Exceptions.NotEnoughArguments);
        }
        Object[] argv = new Object[argc];
        for (int i = 0; i < argc; i++) {
            argv[i] = _stack.pop();
        }
        Object result = executor.execute(argv, _defines);
        _stack.push(result);
    }

    public void Define(String name, Object value) {
        _defines.put(name, value);
    }
}