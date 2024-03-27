package SumThreads.Question;

public class SumThreads {
  private Integer sum = 0;

  public static void main(String[] args) {
    SumThreads test = new SumThreads();
    System.out.println("What is sum ? " + test.sum);
  }

  // modify code to add synchronization mechanism
  public void SUM() {
    sum++;
  }

  public SumThreads() {
    // Create Threads
  }

  class SumTask implements Runnable {
    @Override
    public void run() {
      SUM();
    }
  }
}
