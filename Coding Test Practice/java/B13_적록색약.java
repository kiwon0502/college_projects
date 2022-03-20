import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Arrays;

public class B13_적록색약_서기원 {

	public static int N;
	public static int[][] pic;
	public static boolean[][] visited;
	public static int[] dr = {1, -1, 0, 0};
	public static int[] dc = {0, 0, 1, -1};
	
	// dfs를 사용하여 한번씩만 탐색하여 구역을 구분
	
	public static void dfs(int r, int c, int color, boolean color_weak) {
		visited[r][c] = true;
		for (int i = 0; i < 4; i++) {
			int nr = r + dr[i];
			int nc = c + dc[i];
			if (nr < 0 || nc < 0 || nr >= N || nc >= N || visited[nr][nc]) continue;
			if (pic[nr][nc] == color) dfs(nr, nc, color, color_weak);
			else {
				if (color_weak && color < 3 && pic[nr][nc] < 3) dfs(nr, nc, color, color_weak);
			}
		}
	}
	
	public static int getAreaNum(boolean color_weak) {
		int ret = 0;
		for (boolean a[] : visited) Arrays.fill(a, false);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (!visited[i][j]) {
					dfs(i, j, pic[i][j], color_weak);
					ret++;
				}
			}
		}
		return ret;
	}
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		N = Integer.parseInt(br.readLine());
		pic = new int[N][N];
		visited = new boolean[N][N];
		
		for (int i = 0; i < N; i++) {
			String line = br.readLine();
			for (int j = 0; j < N; j++) {
				switch (line.charAt(j)) {
					case 'R':
						pic[i][j] = 1;
						break;
					case 'G':
						pic[i][j] = 2;
						break;
					case 'B':
						pic[i][j] = 3;
						break;
				}
			}
		}
		System.out.printf("%d %d", getAreaNum(false), getAreaNum(true));
	}

}
