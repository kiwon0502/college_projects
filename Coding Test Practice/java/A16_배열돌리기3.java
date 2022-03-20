
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class A16_배열돌리기3_서기원 {

	static int N, M, R;
	static int[] cmds = new int[1005];
	static int[][] arr;
	
	// 1번 연산 : 상하 반전
	// 2번 연산 : 90도 회전 -> 상하 반전 -> 270도 회전
	// 3번 연산 : 90도 회전
	// 4번 연산 : 90도 회전 * 3
	// 5번 연산 : 사분면 이동
	// 6번 연산 : 5번 연산 * 3
	
	public static void reverse() {	// 상하 반전(1번 연산)
		for (int i = 0; i < N/2; i++) {
			for (int j = 0; j < M; j++) {
				int tmp = arr[i][j];
				arr[i][j] = arr[N-1-i][j];
				arr[N-1-i][j] = tmp;
			}
		}
	}
	
	public static void rotate() { // 90도 회전(3번 연산)
		int[][] rotate = new int[M][N];
		for (int i = 0; i < M; i++) {
			for (int j = 0; j < N; j++) {
				rotate[i][j] = arr[N-1-j][i];
			}
		}
		arr = rotate;
		N = arr.length;
		M = arr[0].length;
	}
	
	public static void exchange() { // 5번 연산
		int[][] buffer = new int[N][M];
		for (int i = 0; i < N/2; i++) {
			for (int j = 0; j < M/2; j++) {
				buffer[i][j+M/2] = arr[i][j];
				buffer[i+N/2][j+M/2] = arr[i][j+M/2];
				buffer[i+N/2][j] = arr[i+N/2][j+M/2];
				buffer[i][j] = arr[i+N/2][j];
			}
		}
		arr = buffer;
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
		
		String[] line = br.readLine().split(" ");
		for (int i = 0; i < line.length; i++) {
			cmds[i] = Integer.parseInt(line[i]);
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
		for (int cmd : cmds) {
			switch(cmd) {
			case 1:
				reverse();
				break;
			case 2:
				rotate();
				reverse();
				for (int i = 0; i < 3; i++) rotate();
				break;
			case 3:
				rotate();
				break;
			case 4:
				for (int i = 0; i < 3; i++) rotate();
				break;
			case 5:
				exchange();
				break;
			case 6:
				for (int i = 0; i < 3; i++) exchange();
				break;
			}
		}
		print();
	}

}
