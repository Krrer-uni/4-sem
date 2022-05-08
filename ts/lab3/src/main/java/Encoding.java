import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;

public class Encoding {
    public static void main(String[] args) throws IOException {
        int block_size = 10;
        int data_size = 20;
        String data_gen_filename = "data.txt";
        String encoded_data_filename = "encoded.txt";

        DataGen.generateData(data_gen_filename,data_size);
        DataReceiver reader = new DataReceiver(data_gen_filename);
        BufferedWriter writer = new BufferedWriter(new FileWriter(encoded_data_filename));

        String data_block = "";
        int encoded_frames = 0;
        do{
            data_block = reader.readFromFile(block_size);
            if(data_block.length() == 0) break;
            writer.append(DataframeWrapper.Encode(data_block));
            encoded_frames++;
        }while (data_block.length() == block_size);

        writer.close();
        System.out.println("Number of encoded dataframes: " + encoded_frames);
    }
}
