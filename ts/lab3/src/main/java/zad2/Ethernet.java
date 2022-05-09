package zad2;

import java.util.Random;
import java.util.Vector;

public class Ethernet {

    private final int cable_len;
    private int packet_len;
    public Vector<Character> cable;
    private Propagator propagator;
    private Vector<Transmitter> stations;

    public Ethernet(int cable_len) {
        this.cable_len = cable_len;
        this.packet_len = cable_len * 2;
        cable = new Vector<>(cable_len);
        propagator = new Propagator();
        stations = new Vector<>();
        for (int i = 0; i < cable_len; i++) {
            cable.add(' ');
        }

    }

    public String print_cable() {
        StringBuilder cable_status = new StringBuilder(">");
        for (int i = 0; i < cable_len; i++) {
            cable_status.append(cable.elementAt(i));
        }
        cable_status.append('<');
        return cable_status.toString();
    }

    public void step() {
        cable = propagator.propagate(cable);
        for (Transmitter transmitter : stations) {
            transmitter.step();
        }
    }

    public void add_station(Character key, int slot) {
        stations.add(new Transmitter(slot, key));
        propagator.add_key(key, slot);
    }

    private class Transmitter {
        int slot;
        Character symbol;
        int wait_timer;
        int reset_timer;
        int message_timer;
        int magnitude;
        Random rand;

        public Transmitter(int slot, Character symbol) {
            this.slot = slot;
            this.symbol = symbol;
            wait_timer = 0;
            reset_timer = -1;
            message_timer = 0;
            magnitude = 2;
            rand = new Random();
        }

        private void transmit() {
            cable.set(slot, symbol);
        }

        private void emergency() {
            message_timer = packet_len;
            wait_timer = packet_len * ((rand.nextInt() & Integer.MAX_VALUE) % magnitude);
            reset_timer = magnitude * packet_len;
            magnitude *=2;
        }

        private void reset() {
            magnitude = 2;
            reset_timer = -1;
        }

        public void step() {
            if (message_timer > 0 && wait_timer == 0) {

                if (cable.elementAt(slot) == ' ') {
                    transmit();
                    message_timer--;
                } else if (cable.elementAt(slot) == '*') {
                    cable.set(slot, ' ');
                    emergency();
                } else {
                    cable.set(slot, ' ');
                    reset();
                }
            } else if(cable.elementAt(slot) != ' '){
                cable.set(slot, ' ');
                reset();
            }else if (message_timer == 0 && reset_timer == -1) {

                if (rand.nextFloat() < 0.01) {
                    message_timer = packet_len;
                }
            }
            if (reset_timer > 0) {
                reset_timer--;
            }else if(reset_timer == 0){
                reset();
                reset_timer--;
            }
            if (wait_timer > 0) {
                wait_timer--;
            }
        }
    }

    public static void main(String[] args) throws InterruptedException {
        Ethernet connection = new Ethernet(50);
        System.out.println(connection.print_cable());
        connection.add_station('a', 0);
        connection.add_station('b', 49);
        connection.add_station('c',25);
//        connection.add_station('c', 100);
        while (true) {
            connection.step();
            System.out.println(connection.print_cable());
            Thread.sleep(5);
        }
    }
}
