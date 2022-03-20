import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.Queue;

public class A31_미세먼지안녕_서기원 {

	static int R, C, T, a[][];
	static int cleaner = -1;
	static Queue<Dust> dusts;
	static int[] dr = {1, -1, 0, 0};
	static int[] dc = {0, 0, 1, -1};
	
	static class Dust {
		int r, c, w;
		public Dust(int r, int c, int w) {
			this.r = r;
			this.c = c;
			this.w = w;
		}
	}
	
	static int getSum() {
		int ret = 0;
		for (int i = 0; i < R; i++) for (int j = 0; j < C; j++) if (a[i][j] > 0) ret += a[i][j];
		return ret;
	}
	
	static void checkDust() { // 먼지의 움직이기 전 초기 값 저장을 위한 queue 설정
		dusts = new LinkedList<>();
		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				if (a[i][j] == -1 || a[i][j] == 0) continue;
				dusts.add(new Dust(i, j, a[i][j]));
			}
		}
	}
	
	static void spread() { // 먼지의 움직임
		while (!dusts.isEmpty()) {
			Dust cur = dusts.poll();
			if (cur.w < 5) continue; // 5 이하는 확산해도 0
			int spreadAmount = cur.w / 5;
			int cnt = 0;
			for (int dir = 0; dir < 4; dir++) {
				int nr = cur.r + dr[dir];
				int nc = cur.c + dc[dir];
				if (nr < 0 || nc < 0 || nr >= R || nc >= C || a[nr][nc] == -1) continue;
				a[nr][nc] += spreadAmount;
				cnt++;
			}
			a[cur.r][cur.c] -= spreadAmount * cnt; 
		}
	}
	
	static void clean() { // 공기 청정기의 정화 작용
		int top = cleaner, down = cleaner + 1;
		for (int i = top-1; i > 0; i--) a[i][0] = a[i-1][0];
		for (int i = 0; i < C-1; i++) a[0][i] = a[0][i+1];
		for (int i =0; i < top; i++) a[i][C-1] = a[i+1][C-1];
		for (int i = C-1; i > 1; i--) a[top][i] = a[top][i-1];
		a[top][1] = 0;
		
		for (int i = down+1; i < R-1; i++) a[i][0] = a[i+1][0];
		for (int i = 0; i < C-1; i++) a[R-1][i] = a[R-1][i+1];
		for (int i = R-1; i > down; i--) a[i][C-1] = a[i-1][C-1];
		for (int i = C-1; i > 1; i--) a[down][i] = a[down][i-1];
		a[down][1] = 0;
	}
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String[] line = br.readLine().split(" ");
		R = Integer.parseInt(line[0]);
		C = Integer.parseInt(line[1]);
		T = Integer.parseInt(line[2]);
		a = new int[R][C];
		for (int i = 0; i < R; i++) {
			line = br.readLine().split(" ");
			for (int j = 0; j < C; j++) {
				a[i][j] = Integer.parseInt(line[j]);
				if (cleaner == -1 && a[i][j] == -1) cleaner = i; // 2행 연속이므로 윗칸만 저장
			}
		}
		
		while (T-- > 0) {
			checkDust();
			spread();
			clean();
		}
		System.out.print(getSum());
	}
}
