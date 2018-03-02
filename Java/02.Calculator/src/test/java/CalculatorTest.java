import org.junit.Test;

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
}