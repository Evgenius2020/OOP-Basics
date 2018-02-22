import java.util.List;

import static org.junit.Assert.*;

public class CalculatorTest {
    @org.junit.Test
    public void testPop() {
        Calculator calculator = new Calculator(null);
        boolean thrown = false;
        try {
            calculator.Pop();
        } catch (Exception e) {
            thrown = true;
        }
        assert thrown;
    }
}