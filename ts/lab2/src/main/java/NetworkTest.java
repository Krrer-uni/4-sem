import com.mxgraph.layout.mxCircleLayout;
import com.mxgraph.layout.mxCompactTreeLayout;
import com.mxgraph.layout.mxFastOrganicLayout;
import com.mxgraph.layout.mxIGraphLayout;
import com.mxgraph.util.mxCellRenderer;
import org.jgrapht.Graph;
import org.jgrapht.GraphPath;
import org.jgrapht.alg.connectivity.ConnectivityInspector;
import org.jgrapht.alg.shortestpath.DijkstraShortestPath;
import org.jgrapht.ext.JGraphXAdapter;
import org.jgrapht.graph.DefaultEdge;
import org.jgrapht.graph.DefaultUndirectedGraph;

import javax.imageio.ImageIO;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.Iterator;
import java.util.Random;
import java.util.Vector;

public class NetworkTest {
    int n  = 10000;
    double TestGraph(Graph<Integer, DefaultEdge> graph, double fail_ppb, Vector<NetworkEdge> edges,double T_max, int connectivity){
        Random rand = new Random();
//        Vector<NetworkEdge> edges = new Vector<>();

        int packet_size = 1500 * 8; //bitów na pakiet
        int c = 0;
        int[][] connectivity_matrix = new int[20][20];
        boolean failed = false;
        for(int counter = 0; counter < n; counter++){
            for(int i =0;i < 20; i++){
                for(int j = i+1; j<20; j++){
                    if(0.75 < rand.nextDouble()){
                        connectivity_matrix[i][j] = connectivity;
                    } else connectivity_matrix[i][j] = 0;
                }
            }
            int[][] flow = new int[20][20];
            int N = 0;
            failed = false;
            Graph<Integer,DefaultEdge> testGraph = graph;
            Vector<NetworkEdge> toBeRemoved = new Vector<>();
            for(DefaultEdge edge : testGraph.edgeSet()){
                if(fail_ppb < rand.nextDouble()){
//                    testGraph.removeEdge(edge);
                    toBeRemoved.add(new NetworkEdge(testGraph.getEdgeSource(edge),testGraph.getEdgeTarget(edge),0));
                }
            }
            for(NetworkEdge edge : toBeRemoved){
                testGraph.removeEdge(edge.source,edge.target);
            }
            ConnectivityInspector ci = new ConnectivityInspector(testGraph);
            DijkstraShortestPath sp = new DijkstraShortestPath(testGraph);
            if(ci.isConnected()){
                for(int i =0;i < 20; i++){
                    for(int j = i+1; j<20; j++){
                        if(connectivity_matrix[i][j] >0){
                            N+=2*connectivity_matrix[i][j];
//                            edges.add(new NetworkEdge(i,j, capacity[i][j]));
                            GraphPath gp = sp.getPath(i,j);
//                            System.out.println("Path from " + i +" to " + j);
//                            for(Object a : gp.getVertexList()){
//                                System.out.print(a+ " ");
//                            }
                            Iterator iter = gp.getVertexList().iterator();
                            int source = (int) iter.next();
                            while(iter.hasNext()){
                                int target = (int) iter.next();
                                flow[source][target] += 2 * connectivity_matrix[i][j]; //razy dwa bo robię macierz przekątniową
                                source = target;
//                                System.out.print(target + " ");
                            }
//                            System.out.println("");
                        }
                    }
                }
                for(NetworkEdge ne : edges){
                    ne.flow_rate = flow[ne.source][ne.target];
                    if(ne.flow_rate >= ne.capacity/packet_size){
                        failed = true;
//                        System.out.println("failed at (" + ne.source + "," + ne.target +")");
//                        System.out.println("(" + ne.source + "," + ne.target +") flow = " + ne.flow_rate * packet_size + " capacity = " + ne.capacity);
                    }
//                    System.out.println("(" + ne.source + "," + ne.target +") flow = " + ne.flow_rate + " capacity = " + ne.capacity);
                }
                if(!failed) {
                    double T_s = 0;
                    for(NetworkEdge ne : edges){
                        T_s += (double)ne.flow_rate/((double)ne.capacity/packet_size - ne.flow_rate);
                    }
                    T_s /= N;
//                    System.out.println(T_s);
                    if(T_s < T_max) c++;
                }
            }
//            else{
//                System.out.println("Is not connected");
//            }
            for(NetworkEdge edge : toBeRemoved){
                testGraph.addEdge(edge.source, edge.target);
            }
        }
        return (double)c/(double)n;
    }

    public static void main(String[] args) throws IOException {
        Random rand = new Random();

        int connectivity = 3000;
        int[][] connectivity_matrix = new int[20][20];
        for(int i =0;i < 20; i++){
            for(int j = i+1; j<20; j++){
                if(0.75 < rand.nextDouble()){
                    connectivity_matrix[i][j] = connectivity;
                }
            }
        }
//        NetworkGraph ng = new NetworkGraph(connectivity_matrix);
        Graph<Integer, DefaultEdge> g = new DefaultUndirectedGraph<>(DefaultEdge.class);
        for(int i = 0; i < 20; i++){
            g.addVertex(i);
        }
//        for(int i =0;i < 20; i++){
//            for(int j = i+1; j<20; j++){
//                if(0.8 < rand.nextDouble()){
//                    g.addEdge(i,i);
//                }
//            }
//        }
        Vector<NetworkEdge> edges = new Vector<>();
        int c = 1000000000; //bity na sekunde
        edges.add(new NetworkEdge(0,5,c));
        edges.add(new NetworkEdge(1,8,c));
        edges.add(new NetworkEdge(1,18,c));
        edges.add(new NetworkEdge(2,8,c));
        edges.add(new NetworkEdge(8,9,c));
        edges.add(new NetworkEdge(8,10,c));
        edges.add(new NetworkEdge(8,19,c));

        edges.add(new NetworkEdge(2,3,c));
        edges.add(new NetworkEdge(2,15,c));
        edges.add(new NetworkEdge(3,7,c));
        edges.add(new NetworkEdge(3,4,c));

        edges.add(new NetworkEdge(4,5,c));
        edges.add(new NetworkEdge(5,9,c));
        edges.add(new NetworkEdge(4,6,c));

        edges.add(new NetworkEdge(6,12,c));
        edges.add(new NetworkEdge(6,13,c));

        edges.add(new NetworkEdge(7,12,c));
        edges.add(new NetworkEdge(11,12,c));
        edges.add(new NetworkEdge(12,14,c));
        edges.add(new NetworkEdge(10,11,c));

        edges.add(new NetworkEdge(16,17,c));
        edges.add(new NetworkEdge(11,16,c));
        edges.add(new NetworkEdge(15,16,c));
        edges.add(new NetworkEdge(0,15,c));
        edges.add(new NetworkEdge(13,17,c));

        edges.add(new NetworkEdge(14,15,c));
        edges.add(new NetworkEdge(14,19,c));
        edges.add(new NetworkEdge(14,18,c));
        edges.add(new NetworkEdge(17,19,c));

//        for(int i = 0; i < 19; i++){
//            g.addEdge(i,i+1);
//        }
        for(NetworkEdge edge : edges){
            g.addEdge(edge.source, edge.target);
        }
        System.out.println("Number of edges = " + edges.size());

        NetworkTest testGraph = new NetworkTest();
//        int capacity = 10000000;
        for(int counter = 0; counter < 70; counter++){
            System.out.println( testGraph.TestGraph(g,0.999, edges, 0.1, connectivity));
//            for(NetworkEdge edge : edges){
//                edge.capacity = capacity;
//            }
//            capacity +=10000000;
            connectivity +=100;
//            for(int i =0;i < 20; i++){
//                for(int j = i+1; j<20; j++){
//                    if(connectivity_matrix[i][j] > 0)
//                        connectivity_matrix[i][j] = connectivity;
//                }
//            }
        }
//        System.out.println(testGraph.TestGraph(g,connectivity_matrix,connectivity_matrix,0.99, edges, 0.1));
        JGraphXAdapter<Integer, DefaultEdge> graphAdapter =
                new JGraphXAdapter<Integer, DefaultEdge>(g);
        mxIGraphLayout layout = new mxFastOrganicLayout(graphAdapter);
        layout.execute(graphAdapter.getDefaultParent());

        BufferedImage image =
                mxCellRenderer.createBufferedImage(graphAdapter, null, 2, Color.WHITE, true, null);
        File imgFile = new File("graph.png");
        ImageIO.write(image, "PNG", imgFile);
    }
}
