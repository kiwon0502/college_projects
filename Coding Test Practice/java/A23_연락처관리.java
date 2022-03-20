import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.StringTokenizer;

public class A23_연락처관리_서기원 {
	
	private static int N, start, ans;
	private static int[] visit;
	private static List<Integer>[] graph;
	
	// 가장 깊은 depths의 node 중 최댓값을 구하는 문제
	// BFS를 통해 값을 갱신하다보면 마지막 depth가 가장 깊은 depths.
	
	public static void bfs() {
		Queue<Integer> q = new LinkedList<>();
		q.add(start);
		int maxDepth = -1;
		while (!q.isEmpty()) {
			int cur = q.poll();
			for (int i = 0; i < graph[cur].size(); i++) {
				int next = graph[cur].get(i);
				if (visit[next] != 0) continue;
				visit[next] = visit[cur] + 1; // depths + 1로 설정
				q.add(next);
			}
			maxDepth = visit[cur];
		}
		for (int i = 1; i <= 100; i++) {
			if (maxDepth != visit[i]) continue;
			ans = Math.max(ans, i); // 큰 값으로 갱신
		}
	}
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder sb = new StringBuilder();
		StringTokenizer st;
		for (int tc = 1; tc <= 10; tc++) { // 잘 세보니 10개만 받는 것 같아서 10으로 설정
			st = new StringTokenizer(br.readLine(), " ");
			N = Integer.parseInt(st.nextToken());
			start = Integer.parseInt(st.nextToken());
			visit = new int[101];
			graph = new ArrayList[101];
			ans = Integer.MIN_VALUE;
			for (int i = 1; i <= 100; i++) graph[i] = new ArrayList<Integer>();
			
			st = new StringTokenizer(br.readLine(), " ");
			for (int i = 0; i < N/2; i++) {
				int from = Integer.parseInt(st.nextToken());
				int to = Integer.parseInt(st.nextToken());
				graph[from].add(to);
			}
			
			visit[start] = 1;
			bfs();
			sb.append("#").append(tc).append(" ").append(ans).append("\n");
		}
		System.out.println(sb.toString());
	}

}
