import com.mxgraph.layout.mxCircleLayout;
import com.mxgraph.layout.mxIGraphLayout;
import com.mxgraph.util.mxCellRenderer;
import org.jgrapht.Graph;
import org.jgrapht.alg.connectivity.ConnectivityInspector;
import org.jgrapht.ext.JGraphXAdapter;
import org.jgrapht.graph.DefaultEdge;

import javax.imageio.ImageIO;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.Random;
import java.util.Vector;

public class NetworkTest {
    int n  = 1000;
    double TestGraph(Graph<Integer, DefaultEdge> graph, int[][] connectivity_matrix, int[][] flow_rate, double fail_ppb){
        Random rand = new Random();
        int c = 0;
        for(int i = 0; i < n; i++){
            for(DefaultEdge edge : graph.edgeSet()){
                if(fail_ppb < rand.nextDouble()){
                    graph.removeEdge(edge);
                }
            }
            ConnectivityInspector ci = new ConnectivityInspector(graph);
            if(ci.isConnected()){
                for(int ii =0;ii < 20; ii++){
                    for(int j = ii+1; j<20; j++){
                        if(connectivity_matrix[ii][j] >0){

                        }
                    }
                }
            }
        }
        return (double)c/n;
    }

    public static void main(String[] args) throws IOException {
        Random rand = new Random();

        int[][] connectivity_matrix = new int[20][20];
        for(int i =0;i < 20; i++){
            for(int j = i+1; j<20; j++){
                if(0.9 < rand.nextDouble()){
                    connectivity_matrix[i][j] = rand.nextInt();
                }
            }
        }
        NetworkGraph ng = new NetworkGraph(connectivity_matrix);

        JGraphXAdapter<Integer, DefaultEdge> graphAdapter =
                new JGraphXAdapter<Integer, DefaultEdge>(ng.g);
        mxIGraphLayout layout = new mxCircleLayout(graphAdapter);
        layout.execute(graphAdapter.getDefaultParent());

        BufferedImage image =
                mxCellRenderer.createBufferedImage(graphAdapter, null, 2, Color.WHITE, true, null);
        File imgFile = new File("graph.png");
        ImageIO.write(image, "PNG", imgFile);
    }
}
