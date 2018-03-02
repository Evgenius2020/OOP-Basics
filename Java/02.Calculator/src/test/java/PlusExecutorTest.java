import org.junit.Test;
import java.util.HashMap;

public class PlusExecutorTest {
    @Test
    public void getValidArgsNumberTest() {
        assert (new PlusExecutor().getArgsNumber() == 2);
    }

    @Test
    public void ExecuteTest() {
        Object[] argv;
        argv = new Object[]{2, 3 };
        PlusExecutor plusExecutor = new PlusExecutor();
        assert ((double)5 == (double)plusExecutor.execute(argv, null));

        HashMap<String, Object> definitions = new HashMap<>();
        definitions.put("IntValue", 5);
        definitions.put("FloatValue", 7f);
        definitions.put("DoubleValue", 11d);
        definitions.put("StringValue", "13");

        argv = new Object[] {"IntValue", 5};
        assert ((double)10 == (double)plusExecutor.execute(argv, definitions));

        argv = new Object[] {7f, "FloatValue"};
        assert ((double)14 == (double)plusExecutor.execute(argv, definitions));

        argv = new Object[] {"DoubleValue", "FloatValue"};
        assert ((double)18 == (double)plusExecutor.execute(argv, definitions));

        argv = new Object[] {"DoubleValue", "StringValue"};
        boolean thrown = false;
        try {
            plusExecutor.execute(argv, definitions);
        }
        catch (ClassCastException e) {
            thrown = true;
        }
        assert (thrown);
    }
}