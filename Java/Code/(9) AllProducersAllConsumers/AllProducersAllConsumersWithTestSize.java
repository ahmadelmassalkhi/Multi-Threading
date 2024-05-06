/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package producerconsumer;

import static java.lang.Thread.sleep;
import java.util.Date;
import java.util.LinkedList;
import java.util.concurrent.Executor;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.lang.model.element.Element;

/**
 *
 * @author Kamal
 */
public class AllProducersAllConsumersWithTestSize {
//------------ NO COOPERATION BETWEEN PRODUCES THEMSELVES and NO COOPERATION BETWEEN CONSUMERS THEMSELVES -----
    public static MyQueue q = new MyQueue();

    public static void main(String[] args) throws InterruptedException {
        ExecutorService executor = Executors.newCachedThreadPool();
        for (int i = 1; i < 100; i++) {
            executor.execute(new Producer());
            executor.execute(new Consumer());
        }

        executor.shutdown();
        while (executor.isTerminated() == false) {
            Thread.yield();
            //System.out.println("Yield Main");
        }

        System.out.println("The size = " + q.size());

    }

    static class Producer extends Thread {

        @Override
        public void run() {
            Date d = new Date();
            try {
                q.addEl(d);
            } catch (InterruptedException e) {
            }
        }

    }

    static class Consumer extends Thread {

        @Override
        public void run() {
            try {
                q.removeEl();
            } catch (InterruptedException e) {
            }
        }

    }

    //inner class Queue
    static class MyQueue extends LinkedList {

        public Lock l = new ReentrantLock();
        Condition empty = l.newCondition();
        Condition full = l.newCondition();

        public void addEl(Date e) throws InterruptedException {
            while (true) {
                l.lock();
                while (q.size() < 10) {// CHANGE while to if to let a producer add one element
                    super.addLast(e);
                    System.out.println(e.toString() + "  is added by " + Thread.currentThread().getId());

                }
                full.signalAll();
                empty.await();
                l.unlock();
                
            }
        }

        public void removeEl() throws InterruptedException {
            while (true) {
                l.lock();
                while (q.size() > 0) { // CHANGE while to if to let a consumer remove one element
                    Date d = (Date) super.removeFirst();
                    System.out.println(d.toString() + "  is removed by " + Thread.currentThread().getId());

                }
                empty.signalAll();
                full.await();
                l.unlock();
                
            }
        }

    }

}
