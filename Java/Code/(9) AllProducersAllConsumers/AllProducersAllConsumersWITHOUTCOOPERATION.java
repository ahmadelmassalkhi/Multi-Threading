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
public class AllProducersAllConsumersWITHOUTCOOPERATION {
//------------- SOLUTION WITHOUT COOPERATION BETWEEN PRODUCERS THEMSELVES AND CONSUMER THEMSELVES-------------------

    public static MyQueue q = new MyQueue();
    public static boolean turnProd = true;
    public static final int MAX_SIZE = 10;
    //We need this flag because the test on the size is not enough - A producer/consumer may work again if the test on the size no more valid -->Wrong
    //Producer can work only if it is the turn of PRODUCERS and the queue is not empty
    //Consumer can work only if it is the turn of CONSUMERS and the queue is not Full

    public static void main(String[] args) {
        ExecutorService executor = Executors.newCachedThreadPool();
        for (int i = 1; i < 100; i++) {
            executor.execute(new Producer());
            executor.execute(new Consumer());
        }
        executor.shutdown();
        while (executor.isTerminated() == false) {
            Thread.yield();
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
                if (turnProd) {
                    //Add an element                
                    super.addLast(e);
                    System.out.println(e.toString() + "  is added by thread :" + Thread.currentThread().getId());

                    //Last producer
                    if (q.size() == MAX_SIZE) {
                        turnProd = false;
                        full.signalAll();
                    }
                }
                // If it is not Prod turn, we should wait the consumers to remove all elements   
                while (turnProd == false) {
                    empty.await();
                }

                l.unlock();
                //sleep(10);//This is to let another Producer add an element - Give it the chance but not sure in case the task is big (executing code outside critical section)--> Condition
            }
        }

        public void removeEl() throws InterruptedException {
            while (true) {
                l.lock();
                if (!turnProd) {
                    Date d = (Date) super.removeFirst();
                    System.out.println(d.toString() + "  is removed by thread : " + Thread.currentThread().getId());
                    //Last consumer
                    if (q.size() == 0) {
                        turnProd = true;
                        empty.signalAll();
                    }
                }
                // If it is  Prod turn, we should wait the prodcers to add all elements             
                while (turnProd) 
                try {
                    full.await();
                } catch (InterruptedException ex) {
                    Logger.getLogger(AllProducersAllConsumersWITHCOOPERATION.class.getName()).log(Level.SEVERE, null, ex);
                }
                // it should wait the producers to full the queue
                // it should wait the producers to full the queue

                l.unlock();
                //sleep(10);//This is to let another Consumer add an element - Give it the chance but not sure in case the task is big (executing code outside critical section) --> Condition

            }
        }
    }

}
