import org.jgrapht.Graph;
import org.jgrapht.graph.DefaultEdge;
import org.jgrapht.graph.DefaultUndirectedGraph;

public class NetworkGraph {

    Graph<Integer, DefaultEdge> g = new DefaultUndirectedGraph<>(DefaultEdge.class);

    Integer verticies = 20;

    int[][] connectivity_matrix = new int[verticies][verticies];
    public NetworkGraph(int[][] connectivity_matrix){
        this.connectivity_matrix = connectivity_matrix;
        for(int i = 0; i < verticies; i++){
            g.addVertex(i);
        }
        for(int i = 0; i < verticies; i++){
            for (int j = i+1; j < verticies ; j++){
                if(connectivity_matrix[i][j] != 0){
                    g.addEdge(i,j);
                }
            }
        }
    }

}