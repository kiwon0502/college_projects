
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class A15_배열돌리기1_서기원 {

	private static int N, M, R;
	private static int[][] arr;
	private static int[] dr = {0, 1, 0, -1};
	private static int[] dc = {1, 0, -1, 0};
	
	// box 개수만큼 껍질 존재
	// 껍질을 반시계 방향으로 회전
	// (i, i) 인자를 저장하고 회전시킨 이후 해당하는 부분에 넣는다 (swap의 원리와 비슷)
	
	public static void rotate(int box) {
		for (int i = 0; i < box; i++) {
			int sVal = arr[i][i];
			int r = i, c = i;
			int dir = 0;
			while (dir < 4) {
				int nr = r + dr[dir];
				int nc = c + dc[dir];
				
				if (nr == i && nc == i) break;
				if (nr < i || nr >= N - i || nc < i || nc >= M - i) {
					dir++;
					continue;
				}
				arr[r][c] = arr[nr][nc];
				r = nr;
				c = nc;
			}
			arr[i + 1][i] = sVal;
		}
	}
	
	public static void input() throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		R = Integer.parseInt(st.nextToken());
		arr = new int[N][M];
		
		for (int i = 0; i < N; i++) {
			st = new StringTokenizer(br.readLine());
			for (int j = 0; j < M; j++) {
				arr[i][j] = Integer.parseInt(st.nextToken());
			}
		}		
	}
	
	public static void print() {
		StringBuilder sb = new StringBuilder();
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				sb.append(arr[i][j] + " ");
			}
			sb.append("\n");
		}
		System.out.println(sb.toString());
	}
	
	public static void main(String[] args) throws Exception {
		input();
		for (int i = 0; i < R; i++) rotate(Math.min(N, M) / 2);
		print();
	}

}
