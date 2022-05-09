package zad1;

import java.io.*;
import java.util.Arrays;
import java.util.Objects;
import java.util.zip.CRC32;

public class Decoding {
    public static void main(String[] args) throws IOException {
        String data_filename = "encoded.txt";
        String decoded_data_filename = "decoded.txt";

        BufferedReader reader = new BufferedReader(new FileReader(data_filename));
        BufferedWriter writer = new BufferedWriter(new FileWriter(decoded_data_filename));

        StringBuilder header = new StringBuilder("");
        int decoded_frames_count = 0;
        int malformed_frames_count = 0;
        while (true) {
            int c = reader.read();
            if (c == -1) break;
            header.append((char) c);
            if (header.length() > 8) {
                header.delete(0, 1);
            }
            if (header.toString().equals("01111110")) {
                header = new StringBuilder("");
                StringBuilder msg = new StringBuilder("");
                int k = reader.read();
                if (k == -1) return;
                msg.append((char) k);

                while (true) {
                    k = reader.read();

                    if (k == -1) return;
                    msg.append((char) k);
//                    if(i%6 != 0 || (char)k == '1'){

//                    }
//                    System.out.println(msg);
                    try{
                    if(msg.substring(msg.length()-8,msg.length()).equals("01111110")){
//                        System.out.println(msg);
                        msg = new StringBuilder(msg.substring(0,msg.length()-8));
//                        System.out.println(msg);
                        for(int i = msg.length()-1; i > 0;i--){
                            if(i%6 == 5){
                                msg.delete(i,i+1);
                            }
                        }
//                        System.out.println(msg);
                        String data  = msg.substring(0,msg.length()-32);

                        CRC32 checksum = new CRC32();
                        checksum.update(data.getBytes());
                        long crc = checksum.getValue();
                        if(Objects.equals(msg.substring(msg.length() - 32, msg.length()), String.format("%32s", Long.toBinaryString(crc)).replace(' ', '0'))){
                            writer.append(data);
                            decoded_frames_count++;
                            break;
                        } else {
                            malformed_frames_count++;
                            break;
                        }
                    }
                    } catch (Exception ignored){}
                }
            }

        }
        writer.close();
        System.out.println("Number of decoded dataframes: " + decoded_frames_count);
        System.out.println("Number of destroyed dataframes: " + malformed_frames_count);
    }
}
