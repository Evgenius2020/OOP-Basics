import Executors.*;

import java.io.*;
import java.util.HashMap;

public class Main {
    public static void main(String args[]) throws IOException {
        BufferedReader reader;
        if (args.length == 1) {
            reader = new BufferedReader(new FileReader(args[0]));
        }
        else{
            reader = new BufferedReader(new InputStreamReader(System.in));
        }

        HashMap<String, String> operationExecutorMap = new HashMap<>();
        operationExecutorMap.put("+", PlusExecutor.class.getName());
        operationExecutorMap.put("-", MinusExecutor.class.getName());
        operationExecutorMap.put("*", MultiplicationExecutor.class.getName());
        operationExecutorMap.put("/", DivisionExecutor.class.getName());
        operationExecutorMap.put("SQRT", SQRTExecutor.class.getName());

        Calculator calculator = new Calculator(new ExecutorsFactory(operationExecutorMap));
        String currLine;
        while (true) {
            currLine = reader.readLine();
            if (currLine == null) {
                break;
            }

            String[] words = currLine.split(" ");
            try {
                String cmd = words[0].toUpperCase();
                if (cmd.compareTo("PUSH") == 0) {
                    try {
                        calculator.getStack().push(Double.parseDouble(words[1]));
                    } catch (Exception e) {
                        calculator.getStack().push(new String(words[1]));
                    }
                    continue;
                }
                if (cmd.compareTo("POP") == 0) {
                    calculator.getStack().pop();
                    continue;
                }
                if (cmd.compareTo("PRINT") == 0) {
                    System.out.println(calculator.getStack().peek().toString());
                    continue;
                }
                if (cmd.compareTo("DEFINE") == 0) {
                    calculator.getDefinitions().put(words[1], Double.parseDouble(words[2]));
                    continue;
                }
                if (cmd.compareTo("EXIT") == 0) {
                    break;
                }
                if (operationExecutorMap.containsKey(cmd)) {
                    calculator.executeOperation(cmd);
                    continue;
                }
                throw new Exceptions.NotSupportedCommand();
            }
            catch (Exception e) {
                System.out.println(e.toString());
            }
        }
    }
}