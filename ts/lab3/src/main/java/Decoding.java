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
                int i = 1;
                while (true) {
                    k = reader.read();
                    i++;
                    if (k == -1) return;
                    if(i%6 != 0 || (char)k == '1'){
                        msg.append((char) k);
                    }
                    System.out.println(msg);
                    try{
                        //musisz zrobić drugi msg bo w pierwszym sprawdzasz czy 0111111 nie pojawiło się w data.txt, sprawdzasz PO usunięciu rozpychania, to nie zadziała
                        //musi byc drugi string
                    if(msg.substring(msg.length()-7,msg.length()).equals("0111111")){
//                        System.out.println(msg);
                        k = reader.read();
                        if((char)k != '0'){
                            malformed_frames_count++;
                            break;
                        }
                        msg = new StringBuilder(msg.substring(0,msg.length()-7));
//                        System.out.println(msg);

                        String data  = msg.substring(0,msg.length()-32);

                        CRC32 checksum = new CRC32();
                        checksum.update(data.getBytes());
                        long crc = checksum.getValue();
                        String calculated_checksum = String.format("%32s", Long.toBinaryString(crc)).replace(' ', '0');
                        String right = msg.substring(msg.length() - 32, msg.length());
                        if(calculated_checksum.equals(right)){
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
