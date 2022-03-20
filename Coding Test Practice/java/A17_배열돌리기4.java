
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.StringTokenizer;

public class A17_배열돌리기4_서기원 {

	static int N, M, K, ans;
	static int[][] arr;
	static int[][] cmds;
	static int[] dr = {1, 0, -1, 0};
	static int[] dc = {0, 1, 0, -1};

	// 배열돌리기 1 응용
	// 순열을 활용하여 모든 경우의 수를 생각해 최솟값 구하기
	// 연산이 6개밖에 되지 않아 6! = 720가지 경우의 수만 존재.
	// 충분히 브루트포스 가능
	
	public static int[][] copy() {
		int[][] copy = new int[N][M];
		for (int i = 0; i < N; i++) {
			System.arraycopy(arr[i], 0, copy[i], 0, M);
		}
		return copy;
	}
	
	public static void rotate(int r, int c, int s, int[][] buff) {
		for (int box = 0; box < s; box++) {
			int sVal = buff[r-s+box][c-s+box];
			int row = r-s+box;
			int col = c-s+box;
			int dir = 0;
			while (dir < 4) {
				int nr = row + dr[dir];
				int nc = col + dc[dir];
				
				if (nr == (r-s+box) && nc == (c-s+box)) break;
				if (nr < (r-s+box) || nr > (r+s-box) || 
						nc < (c-s+box) || nc > (c+s-box)) {
					dir++;
					continue;
				}
				buff[row][col] = buff[nr][nc];
				row = nr;
				col = nc;
			}
			buff[r-s+box][c-s+box+1] = sVal;
		}
	}
	
	public static int getMin(int[][] buff) {
		int ret = Integer.MAX_VALUE;
		for (int i = 0; i < N; i++) {
			int sum = 0;
			for (int j = 0; j < M; j++) {
				sum += buff[i][j];
			}
			ret = Math.min(ret,  sum);
		}
		return ret;
	}
	
	public static void input() throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		K = Integer.parseInt(st.nextToken());
		arr = new int[N][M];
		cmds = new int[K][3];
		ans = Integer.MAX_VALUE;
		
		for (int i = 0; i < N; i++) {
			st = new StringTokenizer(br.readLine());
			for (int j = 0; j < M; j++) {
				arr[i][j] = Integer.parseInt(st.nextToken());
			}
		}
		
		for (int i = 0; i < K; i++) {
			st = new StringTokenizer(br.readLine());
			int r = Integer.parseInt(st.nextToken()) - 1;
			int c = Integer.parseInt(st.nextToken()) - 1;
			int s = Integer.parseInt(st.nextToken());
			
			cmds[i] = new int[] {r, c, s};
		}
	}
	
	static void permutation(boolean[] visited, LinkedList<Integer> perm) {
		if (perm.size() == K) {
			int[][] buff = copy();
			for (Integer idx : perm) {
				int r = cmds[idx][0];
				int c = cmds[idx][1];
				int s = cmds[idx][2];
				rotate(r, c, s, buff);
			}
			
			ans = Math.min(ans, getMin(buff));
			return;
		}
		
		for (int i = 0; i < K; i++) {
			if (!visited[i]) {
				visited[i] = true;
				perm.add(i);
				permutation(visited, perm);
				visited[i] = false;
				perm.removeLast();
			}
		}
	}
	
	public static void main(String[] args) throws Exception {
		input();
		permutation(new boolean[K], new LinkedList<Integer>());
		System.out.println(ans);
	}

}
