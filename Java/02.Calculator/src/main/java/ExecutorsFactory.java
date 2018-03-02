public class ExecutorsFactory {
    public static Executor getInstance(String operation)
            throws ClassNotFoundException, IllegalAccessException, InstantiationException {
        return (Executor)Class.forName(operation).newInstance();
    }
}