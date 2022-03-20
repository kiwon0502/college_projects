import java.util.Scanner;

public class B13_해밀턴순환회로_서기원 {

	static int N, ans = Integer.MAX_VALUE;
	static int[][] cost;
	static boolean[] visited;
	
	public static void dfs(int cnt, int cur, int sum) {
		if (sum > ans) return;
		if (cnt == N) {
			if (cost[cur][1] != 0) ans = Math.min(ans, sum + cost[cur][1]);
			return;
		}
		for (int i = 2; i <= N; i++) {
			if (cost[cur][i] == 0 || visited[i]) continue;
			visited[i] = true;
			dfs(cnt + 1, i, sum + cost[cur][i]);
			visited[i] = false;
		}
	}
	
	public static void main(String[] args) throws Exception {
		Scanner sc = new Scanner(System.in);
		N = sc.nextInt();
		cost = new int[N+1][N+1];
		visited = new boolean[N+1];
		for (int i = 1; i <= N; i++) for (int j = 1; j <= N; j++) cost[i][j] = sc.nextInt();
		visited[1] = true;
		dfs(1, 1, 0);
		System.out.print(ans);
	}

}
