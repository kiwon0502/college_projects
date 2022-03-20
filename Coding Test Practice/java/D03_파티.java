import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.PriorityQueue;
import java.util.StringTokenizer;

public class D03_파티_서기원 {

	static int N, M, X;
	static StringTokenizer st;
	static int[] dist, time;
	static ArrayList<int[]>[] graph;
	
	public static void dijkstra(int start) {
		Arrays.fill(dist, Integer.MAX_VALUE);
		PriorityQueue<int[]> pq = new PriorityQueue<>(
				(int[] o1, int[] o2) -> o1[0] - o2[0]);
		pq.add(new int[] {0, start});
		dist[start] = 0;
		
		while (!pq.isEmpty()) {
			int[] top = pq.poll();
			int cur = top[1];
			int d = top[0];
			if (dist[cur] < d) continue;
			for (int[] node : graph[cur]) {
				if (dist[node[1]] > d + node[0]) {
					dist[node[1]] = d + node[0];
					pq.add(new int[] {dist[node[1]], node[1]});
				}
			}
		}
		
		time[start] += dist[X];
		if (start == X) {
			for (int i = 1; i <= N; i++) time[i] += dist[i];
		}
	}
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		st = new StringTokenizer(br.readLine());
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		X = Integer.parseInt(st.nextToken());
		dist = new int[N+1];
		time = new int[N+1];
		graph = new ArrayList[N+1];
		for (int i = 1; i <= N; i++) graph[i] = new ArrayList<>();

		for (int i = 0; i < M; i++) {
			st = new StringTokenizer(br.readLine());
			int u = Integer.parseInt(st.nextToken());
			int v = Integer.parseInt(st.nextToken());
			int w = Integer.parseInt(st.nextToken());
			graph[u].add(new int[] {w, v});
		}
		
		for (int i = 1; i <= N; i++) dijkstra(i);
		Arrays.sort(time);
		System.out.print(time[N]);
	}

}
