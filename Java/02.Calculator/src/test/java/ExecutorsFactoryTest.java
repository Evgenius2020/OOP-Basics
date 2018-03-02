import org.junit.Test;

public class ExecutorsFactoryTest {
    @Test
    public void getInstanceTest() {
        boolean thrown = false;
        Object obj;
        PlusExecutor plusExecutor = null;

        try {
            obj = ExecutorsFactory.getInstance("PlusExecutor");
            plusExecutor = (PlusExecutor)obj;
        }
        catch (Throwable e) {
            thrown = true;
        }
        assert (!thrown);
        assert (plusExecutor.getArgsNumber() == 2);
    }
}