package Question;

import java.util.Scanner;


public class CounterThreads {
    public static Counter counter = new Counter();

    public static void main(String[] args) throws InterruptedException {
        Scanner input = new Scanner(System.in);

        System.out.println("Enter the number of times each task should run inc() :");
        int nbTimes = input.nextInt();

        System.out.println("enter number of thread that should be created : ");
        int nbThreads = input.nextInt();
        Thread tasks[] = new Thread[nbThreads];

        /* continue code */

        System.out.println("the value of counter = " + counter.getCount());
    }

    // inner class
    static class Counter {
        long count;

        /* modify code to add synchronization mechanism */
        void inc() {
            count = count + 1;
        }

        long getCount() {
            return count;
        }
    }

    static class CounterTask extends Thread {
        private final int nbTimes;

        public CounterTask(int n) {
            nbTimes = n;
        }

        @Override
        public void run() {
            /* fill in some code */
        }

    }

}
