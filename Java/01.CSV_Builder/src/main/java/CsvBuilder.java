import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.Reader;
import java.util.Map;
import java.util.PriorityQueue;
import java.util.TreeMap;
import java.util.Vector;

public class CsvBuilder {
    public static String BuildCsv(String filename) {
        Vector<String> words = ReadWordsFromFile(filename);
        PriorityQueue<WordRecord> wordsFreq = CalculateWordsFrequency(words);
        return GenerateCsv(wordsFreq, words.size());
    }

    private static Vector<String> ReadWordsFromFile(String filename) {
        Vector<String> result = new Vector<>();
        Reader reader = null;
        try {
            reader = new InputStreamReader(new FileInputStream(filename));
            int i;
            String str = "";
            while ((i = reader.read()) != -1) {
                char c = (char) i;
                if (Character.isAlphabetic(c) || Character.isDigit((c))) {
                    str += c;
                    continue;
                }
                if (str != "") {
                    result.add(str);
                    str = "";
                }
            }
        } catch (IOException e) {
            System.err.println("Error while reading file:" + e.getLocalizedMessage());
        } finally {
            if (null != reader) {
                try {
                    reader.close();
                } catch (IOException e) {
                    e.printStackTrace(System.err);
                }
            }
        }
        return result;
    }

    private static class WordRecord implements Comparable<WordRecord>{
        public String word;
        public Integer frequency;

        public WordRecord(String word, Integer frequency) {
            this.word = word;
            this.frequency = frequency;
        }

        public int compareTo(WordRecord o) {
            if (frequency > o.frequency) {
                return -1;
            }
            if (frequency < o.frequency) {
                return 1;
            }
            return 0;
        }
    }

    private static PriorityQueue<WordRecord> CalculateWordsFrequency(Vector<String> words) {
        PriorityQueue<WordRecord> result = new PriorityQueue<>();

        TreeMap<String, Integer> map = new TreeMap<>();
        for (String word : words) {
            if (!map.containsKey(word)) {
                map.put(word, 1);
                continue;
            }
            int value = map.get(word);
            map.put(word, value + 1);
        }

        while (!map.isEmpty()) {
            Map.Entry curr = map.pollFirstEntry();
            result.add(new WordRecord((String)curr.getKey(), (Integer)curr.getValue()));
        }
        return result;
    }

    private static String GenerateCsv(PriorityQueue<WordRecord> wordsFreq, float wordsCount) {
        StringBuilder stringBuilder = new StringBuilder();
        while (!wordsFreq.isEmpty()) {
            WordRecord curr = wordsFreq.poll();
            stringBuilder.append(curr.word);
            stringBuilder.append(',');
            stringBuilder.append(curr.frequency);
            stringBuilder.append(',');
            stringBuilder.append(curr.frequency / wordsCount * 100);
            stringBuilder.append("%\n");
        }
        return stringBuilder.toString();
    }
}