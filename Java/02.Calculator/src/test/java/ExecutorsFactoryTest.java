import org.junit.Test;
import java.util.HashMap;

public class ExecutorsFactoryTest {
    @Test
    public void getInstanceTest() {
        boolean thrown;
        Object instance;
        HashMap<String, String> operationExecutorMap = new HashMap<>();
        operationExecutorMap.put("+", "PlusExecutor");

        PlusExecutor plusExecutor = null;
        thrown = false;
        try {
            instance = new ExecutorsFactory(operationExecutorMap).getInstance("+");
            plusExecutor = (PlusExecutor)instance;
        }
        catch (Throwable e) {
            thrown = true;
        }
        assert (!thrown);
        assert (plusExecutor.getArgsNumber() == 2);

        thrown = false;
        try {
            new ExecutorsFactory(operationExecutorMap).getInstance("SQRT");
        }
        catch (Throwable e) {
            thrown = true;
        }
        assert (thrown);
    }
}