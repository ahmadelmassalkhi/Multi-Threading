package Solution;
import java.util.LinkedList;
import java.util.Random;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.locks.ReentrantLock;
import java.util.concurrent.locks.Condition;


public class ProducerConsumer {
  public static Buffer buffer = new Buffer();

  public static void main(String[] args) {
    // modify code to create consumer and producer threads
    ExecutorService executor = Executors.newCachedThreadPool();

    int c = 1;
    while (c++ < 1000) {
      executor.execute(new Producer());
      executor.execute(new Consumer());
    }

    // schedule de-allocation of resources when ALL threads are finished executing
    executor.shutdown();
    // while there is threads still executing, yield current thread to give priority to others
    while (!executor.isTerminated()) Thread.yield();

    System.out.println("The final size is  " + buffer.size()); // must be 0
  }

  private static Random random = new Random();
  static class Producer extends Thread {

    @Override
    public void run() {
      // modify code to add synchronization mechanism
      int randomInt = random.nextInt(0, 1000);
      buffer.write(randomInt);
      System.out.println("Wrote " + randomInt + " to buffer");
    }
  }

  static class Consumer extends Thread {
    @Override
    public void run() {
      // modify code to add synchronization mechanism
      System.out.println("Read " + buffer.read() + " from buffer");
    }
  }

  private static ReentrantLock lock = new ReentrantLock();
  private static Condition notEmpty = lock.newCondition();
  private static Condition notFull = lock.newCondition();

  static class Buffer {
    private static LinkedList<Integer> list = new LinkedList<>();

    public void write(int e) {
      // modify code to add synchronization mechanism
      lock.lock();
      try {
        // wait until exists some space (queue not full)
        while(list.size() == 10) notFull.await();

        // add
        list.addLast(e);

        // we just added an element, so queue is definitely not empty
        notEmpty.signalAll();
      } catch (Exception er) {
      } finally {
        lock.unlock();
      }
    }

    public Integer read() {
      // modify code to add synchronization mechanism
        lock.lock();
        try {
          // wait until there is something to remove (queue not empty)
          while(list.size() == 0) notEmpty.await();
  
          // remove
          int removed = list.removeFirst();
          
          // we just removed an element, so queue is definitely not full
          notFull.signalAll();

          return removed;
        } catch (Exception e) {
            return null;
        } finally {
          lock.unlock();
        }
    }

    public int size() {
      return list.size();
    }
  }
}
