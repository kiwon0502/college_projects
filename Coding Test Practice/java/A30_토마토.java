import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.Queue;

public class A30_토마토_서기원 {

	static int M, N;
	static Queue<int[]> ripe_tomato = new LinkedList<>();
	static int[][] storage;
	static int[] dr = {1, -1, 0, 0};
	static int[] dc = {0, 0, 1, -1};
	
	public static int bfs() {
		// bfs를 활용하여 익지 않은 토마토 모두 탐색
		// 탐색시 해당 시간으로 update하여 얼마나 지났는지를 확인
		while (!ripe_tomato.isEmpty()) {
			int[] cur = ripe_tomato.poll();
			
			int r = cur[0];
			int c = cur[1];
			
			for (int i = 0; i < 4; i++) {
				int nr = r + dr[i];
				int nc = c + dc[i];
				
				if (nr < 0 || nc < 0 || nr >= N || nc >= M) continue;
				if (storage[nr][nc] == 0) {
					ripe_tomato.add(new int[] {nr, nc});
					storage[nr][nc] = storage[r][c] + 1;
				}
			}
		}
		
		int ret = -5;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (storage[i][j] == 0) return -1;
				ret = Math.max(ret, storage[i][j]);
			}
		}
		return ret - 1;
	}
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String[] line = br.readLine().split(" ");
		M = Integer.parseInt(line[0]);
		N = Integer.parseInt(line[1]);
		storage = new int[N][M];
		for (int i = 0; i < N; i++) {
			line = br.readLine().split(" ");
			for (int j = 0; j < M; j++) {
				storage[i][j] = Integer.parseInt(line[j]);
				if (storage[i][j] == 1) ripe_tomato.add(new int[] {i, j});
			}
		}
		System.out.println(bfs());
	}

}
