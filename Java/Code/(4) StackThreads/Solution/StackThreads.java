package StackThreads.Solution;
import java.util.LinkedList;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;


public class StackThreads {
    private static Stack s = new Stack();

    public static void main(String[] args) throws InterruptedException {
        while (true) {
            PopTask pop = new PopTask();
            PushTask push = new PushTask();
            pop.start();
            push.start();
            System.out.println("Empty Stack ? " + s.isEmpty());
            Thread.sleep(1000);
        }
    }

    // inner class Thread Pop
    private static class PopTask extends Thread {
        @Override
        public void run() {
            s.pop();
            System.out.println("pop");
        }
    }

    // inner class Thread Push
    private static class PushTask extends Thread {
        @Override
        public void run() {
            s.push("A");
            System.out.println("push");
        }
    }

    /****************************************************************/
    /* MODIFIED CODE SEGMENT */

    private static ReentrantLock lock = new ReentrantLock();
    private static Condition notEmpty = lock.newCondition();

    // inner class Stack
    private static class Stack {
        private static LinkedList<String> list = new LinkedList<>();

        public void push(String e) {
            lock.lock();
            try {
                // push
                list.push(e);
                // we just pushed an element, so the stack is definitely not empty
                notEmpty.signalAll();
            } catch (Exception er) {
            } finally {
                lock.unlock();
            }
        }

        public String pop() {
            lock.lock();
            try {
                // wait until there is something to pop
                while(isEmpty()) notEmpty.await();
                // pop
                return list.pop();
            } catch (Exception er) {
                return null;
            } finally {
                lock.unlock();
            }
        }

        public boolean isEmpty() {
            return list.isEmpty();
        }
    }
    /****************************************************************/

}
