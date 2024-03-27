package Question;
import java.util.LinkedList;
import java.util.Random;


public class ProducerConsumerWithoutSyn {
  public static Buffer buffer = new Buffer();

  public static void main(String[] args) {
    // modify code to create consumer and producer threads

    System.out.println("The final size is  " + buffer.size());
  }

  private static Random random = new Random();
  static class Producer extends Thread {

    @Override
    public void run() {
      int randomInt = random.nextInt();
      buffer.write(randomInt);
      System.out.println("Wrote " + randomInt + " to buffer");
    }
  }

  static class Consumer extends Thread {
    @Override
    public void run() {
      System.out.println("Read " + buffer.read() + " from buffer");
    }
  }

  static class Buffer {
    private static LinkedList<Integer> list = new LinkedList<>();

    public void write(int e) {
      // modify code to add synchronization mechanism
      list.addLast(e);
      System.out.println(e + "  is added");
    }

    public int read() {
      // modify code to add synchronization mechanism
      return list.removeFirst();
    }

    public int size() {
      return list.size();
    }
  }
}
