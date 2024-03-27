package CountingTwoWords.Solution;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;


public class CountingTwoWords {

    public static void main(String[] args) throws FileNotFoundException, InterruptedException {
        // Get the current working directory
        String currentDir = System.getProperty("user.dir");

        // Construct file paths relative to the current directory
        File f1 = new File(currentDir + "/Solution/" + "alice-chap1-6.txt");
        File f2 = new File(currentDir + "/Solution/" + "alice-chap7-12.txt");

        // Create a fixed thread pool with maximum two threads
        ExecutorService executor = Executors.newFixedThreadPool(2);
        CountingTask job1 = new CountingTask(f1, "Alice");
        CountingTask job2 = new CountingTask(f2, "Alice");
        executor.execute(job1);
        executor.execute(job2);

        executor.shutdown();
        while (!executor.isTerminated()) Thread.yield();

        System.out.println("The number of word Alice is  : " + (job1.getCounter() + job2.getCounter()));
        System.out.println("The number of word Alice is - Job 1  : " + job1.getCounter());
        System.out.println("The number of word Alice is - Job 2  : " + job2.getCounter());
    }
}
