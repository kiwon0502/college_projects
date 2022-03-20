import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class B09_쿼드트리_서기원 {
	
	static int img[][];
	static StringBuilder sb = new StringBuilder();
	
	// 해당 구역이 한 개의 색으로 이루어져 있다면 return true
	public static boolean isOneColor(int x, int y, int size) {
		int value = img[x][y];
		for (int i = x; i < x + size; i++) {
			for (int j = y; j < y + size; j++) {
				if (value != img[i][j]) return false;
			}
		}
		return true;
	}
	
	public static void solve(int x, int y, int size) {
		// 한 가지 색이라면 다른 작업 필요 없이 압축
		if (isOneColor(x, y, size)) {
			sb.append(img[x][y]);
			return;
		}
		
		// 4등분하는 작업
		int half = size / 2;
		sb.append("(");
		// 4개의 영역에 대해 재귀적으로 접근
		solve(x, y, half);
		solve(x, y + half, half);
		solve(x + half, y, half);
		solve(x + half, y + half, half);
		sb.append(")");
	}

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int N = Integer.parseInt(br.readLine());
		img = new int[N][N];
		
		// 입력부
		for (int i = 0; i < N; i++) {
			String temp = br.readLine();
			for (int j = 0; j < N; j++) {
				img[i][j] = temp.charAt(j) - '0'; 
			}
		}

		// 분할 정복
		solve(0, 0, N);
		System.out.println(sb.toString());
	}

}
