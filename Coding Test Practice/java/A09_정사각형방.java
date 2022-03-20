
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class A09_정사각형방_서기원 {

	static int[] dr = {1, -1, 0, 0};
	static int[] dc = {0, 0, 1, -1};
	static int MAX = 1001;
	static int N, idx, ans;
	static int[][] arr;
	static boolean[][] visited;
	
	static void dfs(int r, int c, int cnt, int start) {
		visited[r][c] = true;
		
		for (int i = 0; i < 4; i++) {
			int nr = r + dr[i];
			int nc = c + dc[i];
			
			if (nr < 0 || nc < 0 || nr >= N || nc >= N || visited[nr][nc]) continue;
			if (arr[nr][nc] == arr[r][c] + 1) {
				dfs(nr, nc, cnt + 1, start);
			}
		}
		
		if (cnt > ans) {
			ans = cnt;
			idx = start;
		}
		else if (cnt == ans) {
			idx = Math.min(idx, start);
		}
		
		visited[r][c] = false;		
	}
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int T = Integer.parseInt(br.readLine());
		for (int tc = 1; tc <= T; tc++) {
			N = Integer.parseInt(br.readLine());
			
			arr = new int[N][N];
			visited = new boolean[N][N];
			idx = 0;
			ans = 0;
			
			for (int i = 0; i < N; i++) {
				StringTokenizer st = new StringTokenizer(br.readLine());
				for (int j = 0; j < N; j++) {
					arr[i][j] = Integer.parseInt(st.nextToken());
				}
			}
			
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					dfs(i, j, 1, arr[i][j]);
				}
			}
			
			System.out.println("#" + tc + " " + idx + " " + ans);
		}
	}

}
