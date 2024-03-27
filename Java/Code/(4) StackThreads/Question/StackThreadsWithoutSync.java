package StackThreads.Question;
import java.util.LinkedList;


public class StackThreadsWithoutSync {

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

    // inner class Stack
    private static class Stack {
        private static LinkedList<String> list = new LinkedList<>();

        public void push(String e) {
            // modify code to add synchronization mechanism
            list.push(e);
        }

        public Object pop() {
            // modify code to add synchronization mechanism
            return list.pop();
        }

        public boolean isEmpty() {
            return list.isEmpty();
        }
    }

}
