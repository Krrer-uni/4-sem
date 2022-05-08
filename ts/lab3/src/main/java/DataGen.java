import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;

public class DataGen {
    public static void generateData(String filename, int size) throws IOException {
        Random rand = new Random();
        BufferedWriter writer = new BufferedWriter(new FileWriter(filename));
        for(int i = 0; i < size; i++){
            if(rand.nextInt() % 2 == 0){
                writer.append('0');
            }else{
                writer.append('1');
            }

        }
        writer.close();
    }
}
