import java.io.*;

public class DataReceiver {
    BufferedReader reader;
    DataReceiver(String filename) throws FileNotFoundException {
        reader = new BufferedReader(new FileReader(filename));
    }

    public String readFromFile(int len) throws IOException {
        String msg = "";
        for (int i = 0; i < len; i++){
            int r = reader.read();
            if(r != -1){
                msg += (char)r;
            } else {
                return msg;
            }
        }
        return msg;
    }
}
