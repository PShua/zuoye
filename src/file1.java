import java.io.*;
import java.util.ArrayList;
import java.util.List;
//对比解析标准答案与实际答案
public class file1 {

    // 对比两个答案文件并记录正确与错误的题号
    public static void compareAnswers(String expectedAnswersFile, String actualAnswersFile, String comparisonFile) {
        List<Integer> correctQuestions = new ArrayList<>(); // 存储正确的题号
        List<Integer> incorrectQuestions = new ArrayList<>(); // 存储错误的题号
        int corrnum=0;
        int incorrnum=0;
        try (BufferedReader expectedReader = new BufferedReader(new FileReader(expectedAnswersFile));
             BufferedReader actualReader = new BufferedReader(new FileReader(actualAnswersFile))) {

            String expectedLine;
            String actualLine;
            int lineNumber = 1;

            // 逐行对比两个文件
            while ((expectedLine = expectedReader.readLine()) != null && (actualLine = actualReader.readLine()) != null) {
                expectedLine = expectedLine.trim();
                actualLine = actualLine.trim();

                if (expectedLine.equals(actualLine)) {
                    correctQuestions.add(lineNumber);// 答案正确
                    corrnum++;
                } else {
                    incorrectQuestions.add(lineNumber); // 答案错误
                    incorrnum++;
                }
                lineNumber++;
            }

            // 生成对比结果文件
            try (BufferedWriter writer = new BufferedWriter(new FileWriter(comparisonFile))) {
                writer.write("correct Questions: " + corrnum + correctQuestions + "\n");
                writer.write("Incorrect Questions: " + incorrnum + incorrectQuestions + "\n");
            }

            System.out.println("Comparison results have been saved to " + comparisonFile);

        } catch (IOException e) {
            System.err.println("Error reading or writing file: " + e.getMessage());
        }
    }

    public static void main(String[] args) {
        // 文件路径

        String expectedAnswersFile = "answer.txt"; // 标准答案文件
        String actualAnswersFile = "arithmetic_answers.txt"; // 实际答案文件
        String comparisonFile = "comparison_results.txt"; // 对比结果文件

        // 对比答案并生成结果
        compareAnswers(expectedAnswersFile, actualAnswersFile, comparisonFile);
    }
}