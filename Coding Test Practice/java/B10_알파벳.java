import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class B10_알파벳_서기원 {

	static char[][] board;
	static int R, C;
	static int[] dr = {1, -1, 0, 0};
	static int[] dc = {0, 0, 1, -1};
	static boolean[] alpha = new boolean[27]; // 해당 알파벳을 지나갔는지 확인
	static boolean[][] visited;
	
	// r행 c열을 방문하는 dfs 함수
	static int solve(int r, int c) {
		int ret = 0;
		visited[r][c] = true;
		for (int i = 0; i < 4; i++) {
			int nr = r + dr[i], nc = c + dc[i];
			if (nr < 0 || nc < 0 || nr >= R || nc >= C) continue;
			if (alpha[board[nr][nc] - 'A'] == true) continue; // 이미 해당 알파벳을 지나갓다면 pass
			alpha[board[nr][nc] - 'A'] = true; // 알파벳 지낫다고 표시
			ret = Math.max(ret, solve(nr, nc)); // 재귀 함수 호출
			alpha[board[nr][nc] - 'A'] = false; // 백트래킹
		}		
		return ret + 1; // 자기 자신을 포함한 값
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String[] line = br.readLine().split(" ");
		R = Integer.parseInt(line[0]);
		C = Integer.parseInt(line[1]);
		board = new char[R][C];
		visited = new boolean[R][C]; // 해당 지점을 지났는지 확인
		
		for (int i = 0; i < R; i++) {
			String line2 = br.readLine();
			for (int j = 0; j < C; j++) {
				board[i][j] = line2.charAt(j);
			}
		}
		
		alpha[board[0][0] - 'A'] = true;
		System.out.println(solve(0, 0));
		
	}

}
