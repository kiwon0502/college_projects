import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;

public class A22_DFS와BFS_서기원 {

	private static int N, M, V;
	private static int[][] adj = new int[1005][1005];
	private static boolean[] visited = new boolean[1005];
	private static StringBuilder forDFS, forBFS;
	
	// DFS 함수
	public static void dfs(int node) {
		visited[node] = true;
		forDFS.append(node).append(" ");
		for (int i = 1; i <= N; i++) {
			if (visited[i] || adj[node][i] == 0) continue;
			dfs(i);
		}
	}
	
	// BFS 함수
	public static void bfs(int start) {
		Queue<Integer> q = new LinkedList<>();
		q.add(start);
		visited[start] = true;
		
		while (!q.isEmpty()) {
			int cur = q.poll();
			forBFS.append(cur).append(" ");
			
			for (int i = 1; i <= N; i++) {
				if (visited[i] || adj[cur][i] == 0) continue;
				q.add(i);
				visited[i] = true;
			}
		}
	}
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		forDFS = new StringBuilder();
		forBFS = new StringBuilder();
		
		String[] line = br.readLine().split(" ");
		N = Integer.parseInt(line[0]);
		M = Integer.parseInt(line[1]);
		V = Integer.parseInt(line[2]);
		
		
		for (int i = 0; i < M; i++) {
			line = br.readLine().split(" ");
			int u = Integer.parseInt(line[0]);
			int v = Integer.parseInt(line[1]);
			adj[u][v] = adj[v][u] = 1;
		}

		Arrays.fill(visited, false);
		dfs(V);
		Arrays.fill(visited, false); // visited 배열 초기화
		bfs(V);
		
		System.out.println(forDFS.toString());
		System.out.println(forBFS.toString());
		
	}

}
