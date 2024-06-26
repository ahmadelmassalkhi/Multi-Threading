package Deadlock;

public class Deadlock {
  private Object object1 = new Object();
  private Object object2 = new Object();

  public static void main(String[] args) {
    new Deadlock();
  }

  public Deadlock() {
    new Thread1().start();
    new Thread2().start();
  }

  class Thread1 extends Thread {
    public void run() {
      synchronized (object1) {
        // do something
        try {
          Thread.sleep(100);
        } catch (InterruptedException ex) {
        }
        System.out.println("Attempt to acquire a lock on object2");

        synchronized (object2) {
          // do something
        }
      }
    }
  }

  class Thread2 extends Thread {
    public void run() {
      synchronized (object2) {
        // do something
        try {
          Thread.sleep(100);
        } catch (InterruptedException ex) {
        }
        System.out.println("Attempt to acquire a lock on object1");

        synchronized (object1) {
          // do something
        }
      }
    }
  }
}
