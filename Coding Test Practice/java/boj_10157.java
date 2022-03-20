import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class boj_10157 {
	
	static int[][] auditorium;
	static int C, R, K;
	static int cnt = 1;
	static int[] dx = {-1, 0, 1, 0}; // 상, 우, 하, 좌
	static int[] dy = {0, 1, 0, -1};
	
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		C = Integer.parseInt(st.nextToken());
		R = Integer.parseInt(st.nextToken());
		K = Integer.parseInt(br.readLine());
		
		if (K > C * R) {
			System.out.println("0");
			System.exit(0);
		}
		
		auditorium = new int[R][C];
		
		int x = R - 1;
		int y = 0;
		int dir = 0;
		
		while (cnt != K) {
			auditorium[x][y] = cnt;
			int nx = x + dx[dir];
			int ny = y + dy[dir];
			
			if (nx < 0 || ny < 0 || nx >= R || ny >= C || auditorium[nx][ny] != 0) {
				dir = (dir+1)%4;
				nx = x + dx[dir];
				ny = y + dy[dir];
			}
			
			x = nx;
			y = ny;
			cnt++;
		}
		
		System.out.println((y+1) + " " + (R-x));
		
	}

}
