import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.PriorityQueue;

public class A28_최단경로_서기원 {

	static int V, E, K;
	static List<Node>[] graph;
	static int[] dist;
	
	static void dijkstra(int start) {
		PriorityQueue<Node> pq = new PriorityQueue<>();
		pq.add(new Node(start, 0));
		dist[start] = 0;
		
		while (!pq.isEmpty()) {
			Node curNode = pq.poll();
			if (dist[curNode.end] < curNode.w) continue;
			for (Node node : graph[curNode.end]) {
				if (dist[node.end] > dist[curNode.end] + node.w) {
					dist[node.end] = dist[curNode.end] + node.w;
					pq.add(new Node(node.end, dist[node.end]));
				}
			}
		}		
	}
	
	@SuppressWarnings("unchecked")
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String[] line = br.readLine().split(" ");
		V = Integer.parseInt(line[0]);
		E = Integer.parseInt(line[1]);
		K = Integer.parseInt(br.readLine());
		graph = new ArrayList[V+1];
		dist = new int[V+1];
		Arrays.fill(dist, Integer.MAX_VALUE);
		for (int i = 1; i <= V; i++) graph[i] = new ArrayList<>();
		
		for (int i = 0; i < E; i++) {
			line = br.readLine().split(" ");
			int u = Integer.parseInt(line[0]);
			int v = Integer.parseInt(line[1]);
			int w = Integer.parseInt(line[2]);
			
			graph[u].add(new Node(v, w));
		}
		
		StringBuilder sb = new StringBuilder();
		dijkstra(K);
		for (int i = 1; i <= V; i++) {
			if (dist[i] == Integer.MAX_VALUE) sb.append("INF\n");
			else sb.append(dist[i]).append("\n");
		}
		System.out.print(sb.toString());
	}

}

class Node implements Comparable<Node> {
	int end, w;
	
	public Node(int end, int w) {
		this.end = end;
		this.w = w;
	}
	
	@Override
	public int compareTo(Node o) {
		return w - o.w;
	}
	
}