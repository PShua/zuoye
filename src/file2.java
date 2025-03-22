import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
//生成一个标准答案类
public class file2 {
    public static void main(String[] args) {
        // 定义文件路径
        String filePath = "answer.txt";

        try (PrintWriter writer = new PrintWriter(new FileWriter(filePath))) {
            // 生成1到100的数字并写入文件
            for (int i = 1; i <= 10; i++) {
                writer.println(i);
            }
            System.out.println("答案文件已生成: " + filePath);
        } catch (IOException e) {
            System.err.println("写入文件时发生错误: " + e.getMessage());
        }
    }
}