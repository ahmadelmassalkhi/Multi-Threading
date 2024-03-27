package LinkedListThreads.Solution;

import java.util.LinkedList;
import java.util.Random;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;


public class LinkedListThreads {
    // linked list
    private static LinkedList<String> ll = new LinkedList<>();

    public static void main(String[] args) throws InterruptedException {
        ExecutorService executorService = Executors.newCachedThreadPool();

        int c = 1;
        while (c <= 1000) {
            executorService.submit(new AddTask());
            executorService.submit(new RemoveTask());
            c++;
        }

        // no more threads are allowed to get submitted anymore, terminates when all threads terminate
        executorService.shutdown();

        // yield (give priority to other threads) while still exists active threads
        while(executorService.isTerminated() == false) Thread.yield();

        System.out.println("IsEmpty = " + ll.isEmpty());
    }

    // lock & condition
    private static ReentrantLock lock = new ReentrantLock();
    private static Condition notEmpty = lock.newCondition();

    private static class AddTask extends Thread {
        @Override
        public void run() {
            lock.lock();
            try {
                // add
                Integer x = new Random().nextInt(100) + 1;
                ll.add(x.toString());
                System.out.println("An element was added  " + x);

                // we just added an element, so the linkedList is definitely not empty
                notEmpty.signalAll();
            } catch (Exception e) {
            } finally {
                lock.unlock();
            }
        }
    }

    private static class RemoveTask extends Thread {
        @Override
        public void run() {
            lock.lock();
            try {
                // wait until there is something to remove
                while(ll.isEmpty()) notEmpty.await();

                // remove
                String x = (String) ll.remove();
                System.out.println("An element was removed  " + x);
            } catch (Exception e) {
            } finally {
                lock.unlock();
            }
        }
    }
}
