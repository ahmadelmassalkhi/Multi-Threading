package LinkedListThreads.Question;

import java.util.LinkedList;
import java.util.Random;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;


public class LinkedListThreads {
    // linked list
    private static LinkedList<String> ll = new LinkedList<>();

    public static void main(String[] args) throws InterruptedException {
        // modify code to create threads
        int c = 1;
        while (c <= 10) {
            c++;
        }
    }

    private static class AddTask extends Thread {
        @Override
        public void run() {
            // modify code to add synchronization mechanism
            Integer x = new Random().nextInt(100) + 1;
            ll.add(x.toString());
            System.out.println("An element was added  " + x);
        }
    }

    private static class RemoveTask extends Thread {
        @Override
        public void run() {
            // modify code to add synchronization mechanism
            String x = (String) ll.remove();
            System.out.println("An element was removed  " + x);
        }
    }
}
