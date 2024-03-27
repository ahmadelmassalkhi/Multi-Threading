package CountingTwoWords.Solution;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;


/****************************************************************************/
/* GIVEN CODE */

public class CountingTask extends Thread {

    File file;
    String word;
    private int counter = 0;

    public int getCounter() {
        return counter;
    }

    public CountingTask(File file, String word) {
        this.file = file;
        this.word = word;
    }

    @Override
    public void run() {
        FileReader fr = null;
        try {
            fr = new FileReader(this.file); // Creation of File Reader object
        } catch (FileNotFoundException ex) {
            Logger.getLogger(CountingTask.class.getName()).log(Level.SEVERE, null, ex);
        }
        BufferedReader br = new BufferedReader(fr); // Creation of BufferedReader object

        String[] words = null;
        String s;
        System.out.println("Searching...");
        try {
            while ((s = br.readLine()) != null) // Reading Content from the file
            {
                words = s.split(" "); // Split the word using space
                for (int i = 0; i < words.length; i++) {
                    if (words[i].equals("Alice"))
                        counter++;
                }
            }
        } catch (IOException ex) {
            Logger.getLogger(CountingTask.class.getName()).log(Level.SEVERE, null, ex);
        }

        try {
            fr.close();
        } catch (IOException ex) {
            Logger.getLogger(CountingTask.class.getName()).log(Level.SEVERE, null, ex);
        }
        System.out.println("The number of word Alice is  : " + this.getCounter());
    }
}
/****************************************************************************/