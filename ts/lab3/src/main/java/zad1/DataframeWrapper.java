package zad1;

import java.util.zip.CRC32;

public class DataframeWrapper {
    public static String Encode(String data){
        CRC32 checksum = new CRC32();
        checksum.update(data.getBytes());
        long crc = checksum.getValue();
        data += String.format("%32s",Long.toBinaryString(crc)).replace(' ', '0');
//        System.out.println( String.format("%32s",Long.toBinaryString(crc)).replace(' ', '0'));
        StringBuilder msg = new StringBuilder(ending_byte);
        msg.append(data.charAt(0));
        for(int i = 1; i < data.length(); i++){
            if(i%5 == 0){
                msg.append('0');
            }
            msg.append(data.charAt(i));
        }
        msg.append(ending_byte);
        return msg.toString();
    }
    private static final String ending_byte = "01111110";
}
