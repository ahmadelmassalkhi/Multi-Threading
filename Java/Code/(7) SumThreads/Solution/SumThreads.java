package SumThreads.Solution;
import java.util.concurrent.*;


public class SumThreads {
  private Integer sum = 0;

  public static void main(String[] args) {
    SumThreads test = new SumThreads();
    System.out.println("What is sum ? " + test.sum); // must be equal to number of thread (100000)
  }

  // modify code to add synchronization mechanism
  public synchronized void SUM() {
    sum++;
  }

  public SumThreads() {
    // Create Threads
    ExecutorService executor = Executors.newCachedThreadPool();

    int c = 0;
    while (c++ < 100000) {
      executor.execute(new SumTask());
    }

    executor.shutdown();
    while(executor.isTerminated() == false) Thread.yield();
  }

  class SumTask implements Runnable {
    @Override
    public void run() {
      SUM();
    }
  }
}
