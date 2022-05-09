package zad2;

import java.util.HashMap;
import java.util.Map;
import java.util.Vector;

public class Propagator {
    public HashMap<Character, Integer> keys;

    public Propagator() {
        keys = new HashMap<Character, Integer>();
        keys.put(' ', -1);
        keys.put('*', -1);
    }

    public void add_key(Character key, Integer val) {
        keys.put(key, val);
    }

    public Vector<Character> propagate(Vector<Character> ethernet) {
        Vector<Character> new_state = new Vector<>(ethernet.size());
        for (int i = 0; i < ethernet.size(); i++) {
            new_state.add(' ');
        }
        char key = ethernet.elementAt(0);
        if (keys.get(key) == 0) {
            move_right(ethernet, new_state, key, 0);
        }
        for (int i = 1; i < ethernet.size() - 1; i++) {
            key = ethernet.elementAt(i);
            if (key == ' ' || key == '*') {
                continue;
            } else if (keys.get(key) == i) {
                move_left(ethernet, new_state, key, i);
                move_right(ethernet, new_state, key, i);
            } else if (keys.get(key) < i) {
                move_right(ethernet, new_state, key, i);
            } else {
                move_left(ethernet, new_state, key, i);
            }
        }
        key = ethernet.elementAt(ethernet.size() - 1);
        if (keys.get(key) == ethernet.size() - 1) {
            move_left(ethernet, new_state, key, ethernet.size() - 1);
        }
        return new_state;
    }

    private void move_right(Vector<Character> ethernet, Vector<Character> new_state, char key, int i) {
        if (ethernet.get(i + 1) == '*') {
            new_state.set(i, '*');
        } else if (ethernet.get(i + 1) != ' ' && ethernet.get(i + 1) != key) {
            new_state.set(i, '*');
        } else if (new_state.elementAt(i + 1) != ' ') {
            new_state.set(i + 1, '*');
        } else {
            new_state.set(i + 1, key);
        }
    }

    private void move_left(Vector<Character> ethernet, Vector<Character> new_state, char key, int i) {
        if (ethernet.get(i - 1) == '*') {
            new_state.set(i, '*');
        } else if (ethernet.get(i - 1) != ' ' && ethernet.get(i - 1) != key) {
            new_state.set(i, '*');
        } else if (new_state.elementAt(i - 1) != ' ') {
            new_state.set(i - 1, '*');
        } else {
            new_state.set(i - 1, key);
        }
    }
}
