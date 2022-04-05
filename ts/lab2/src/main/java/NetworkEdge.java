public class NetworkEdge {
    int source;
    int target;
    int capacity;
    int flow_rate;

    public NetworkEdge(int source, int dest, int capacity){
        this.source = source;
        this.target = dest;
        this.capacity = capacity;
        this.flow_rate = 0;
    }
}
