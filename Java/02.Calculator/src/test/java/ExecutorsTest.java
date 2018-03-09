import org.junit.Test;
import java.util.HashMap;
import java.util.LinkedList;

public class ExecutorsTest {
    @Test
    public void getValidArgsNumberTest() {
        assert (new PlusExecutor().getArgsNumber() == 2);
        assert (new DivisionExecutor().getArgsNumber() == 2);
    }

    @Test
    public void ExecuteTest() {
        Object[] argv;

        HashMap<String, Object> definitions = new HashMap<>();
        definitions.put("IntValue", 5);
        definitions.put("FloatValue", -7f);
        definitions.put("DoubleValue", 11d);

        PlusExecutor plusExecutor = new PlusExecutor();
        MinusExecutor minusExecutor = new MinusExecutor();
        MultiplicationExecutor multiplicationExecutor = new MultiplicationExecutor();
        DivisionExecutor divisionExecutor = new DivisionExecutor();
        SQRTExecutor sqrtExecutor = new SQRTExecutor();

        argv = new Object[]{2, 3};
        assert ((double) 5 == (double) plusExecutor.execute(argv, null));
        assert ((double) -1 == (double) minusExecutor.execute(argv, null));
        assert ((double) 6 == (double) multiplicationExecutor.execute(argv, null));
        assert ((double) 2 / 3 == (double) divisionExecutor.execute(argv, null));
        assert (Math.sqrt(2) == (double) sqrtExecutor.execute(argv, null));

        argv = new Object[]{"IntValue", 5};
        assert ((double) 10 == (double) plusExecutor.execute(argv, definitions));
        assert ((double) 0 == (double) minusExecutor.execute(argv, definitions));
        assert ((double) 25 == (double) multiplicationExecutor.execute(argv, definitions));
        assert ((double) 1 == (double) divisionExecutor.execute(argv, definitions));
        assert (Math.sqrt(5) == (double) sqrtExecutor.execute(argv, definitions));

        argv = new Object[]{7f, "FloatValue"};
        assert ((double) 0 == (double) plusExecutor.execute(argv, definitions));
        assert ((double) 14 == (double) minusExecutor.execute(argv, definitions));
        assert ((double) -49 == (double) multiplicationExecutor.execute(argv, definitions));
        assert ((double) -1 == (double) divisionExecutor.execute(argv, definitions));
        assert (Math.sqrt(7) == (double) sqrtExecutor.execute(argv, definitions));

        argv = new Object[]{"DoubleValue", "FloatValue"};
        assert ((double) 4 == (double) plusExecutor.execute(argv, definitions));
        assert ((double) 18 == (double) minusExecutor.execute(argv, definitions));
        assert ((double) -77 == (double) multiplicationExecutor.execute(argv, definitions));
        assert ((double) -11 / 7 == (double) divisionExecutor.execute(argv, definitions));
        assert (Math.sqrt(11) == (double) sqrtExecutor.execute(argv, definitions));
    }

    @Test
    public void classCastExceptionTest() {
        Object[] argv = new Object[] {"StringValue", 5};

        HashMap<String, Object> definitions = new HashMap<>();
        definitions.put("StringValue", "13");

        LinkedList<Executor> executors = new LinkedList<>();
        executors.push(new PlusExecutor());
        executors.push(new MinusExecutor());
        executors.push(new MultiplicationExecutor());
        executors.push(new DivisionExecutor());
        executors.push(new SQRTExecutor());

        for (Executor executor: executors) {
            boolean thrownClassCastException = false;
            try {
                executor.execute(argv, definitions);
            }
            catch (ClassCastException e) {
                thrownClassCastException = true;
            }
            assert (thrownClassCastException);
        }
    }

    @Test
    public void divisionByZeroTest() {
        boolean thrownArithmeticException = false;
        Double result = null;
        try {
            result = (Double)new DivisionExecutor().execute(new Object[] {3, 0}, null);
        }
        catch (ArithmeticException e) {
            thrownArithmeticException = true;
        }
        assert (!thrownArithmeticException);
        assert (result.isInfinite());
    }

    @Test
    public void sqrtOfNegativeValue() {
        boolean thrownArithmeticException = false;
        Double result = null;
        try {
            result = (Double)new SQRTExecutor().execute(new Object[] {-2}, null);
        }
        catch (ArithmeticException e) {
            thrownArithmeticException = true;
        }
        assert (!thrownArithmeticException);
        assert (result.isNaN());
    }
}