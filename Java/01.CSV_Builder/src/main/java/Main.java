public class Main {
    public static void main(String args[]) {
        if (args.length == 0) {
            System.out.print("Please enter filename");
            return;
        }
        String csvtext = CsvBuilder.BuildCsv(args[0]);
        System.out.print(csvtext);
    }
}