public class Main {
    public static void main(String args[]) {
        String csvtext = CsvBuilder.BuildCsv("input.txt");
        System.out.print(csvtext);
    }
}