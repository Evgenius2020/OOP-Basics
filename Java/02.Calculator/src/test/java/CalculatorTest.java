import Executors.*;
import org.junit.Test;
import java.util.HashMap;

public class CalculatorTest {
    @Test
    public void testDrop() {
        Calculator calculator = new Calculator(null);
        calculator.getStack().push("aaa");
        calculator.getStack().push("aaa");
        calculator.getDefinitions().put("aa", "aa");
        assert (calculator.getStack().size() == 2);
        assert (calculator.getDefinitions().size() == 1);

        calculator.drop();

        assert (calculator.getStack().size() == 0);
        assert (calculator.getDefinitions().size() == 0);
    }

    void testOperation(Calculator calculator, String operation, double exceptedResult) {
        Double result;
        boolean thrown = false;
        try {
            calculator.executeOperation(operation);
        }
        catch (Exception e) {
            thrown = true;
        }
        assert (!thrown);
        result = (Double)calculator.getStack().peek();
        assert (result == exceptedResult);
    }

    @Test
    public void testExecute() {
        HashMap<String, String> operationExecutorMap = new HashMap<>();
        operationExecutorMap.put("+", PlusExecutor.class.getName());
        operationExecutorMap.put("-", MinusExecutor.class.getName());
        operationExecutorMap.put("*", MultiplicationExecutor.class.getName());
        operationExecutorMap.put("/", DivisionExecutor.class.getName());
        operationExecutorMap.put("SQRT", SQRTExecutor.class.getName());
        ExecutorsFactory factory = new ExecutorsFactory(operationExecutorMap);
        Calculator calculator = new Calculator(factory);

        calculator.getStack().push(5);
        calculator.getStack().push(3);
        testOperation(calculator, "+", 8d);
        assert (calculator.getStack().size() == 1);

        calculator.getStack().push(4);
        testOperation(calculator, "-", 4d);

        calculator.getStack().push(5);
        testOperation(calculator, "*", 20d);

        calculator.getStack().push(5);
        testOperation(calculator, "/", 4d);

        testOperation(calculator, "SQRT", 2d);
        assert (calculator.getStack().size() == 1);
    }
}