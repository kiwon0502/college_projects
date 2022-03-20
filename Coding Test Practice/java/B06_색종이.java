
import java.util.Scanner;

public class B06_색종이_서기원 {
	
	// 100 * 100 흰 도화지를 초기화
	// 입력받은 색종이에 해당하는 부분에 1로 입력
	// 이후 1로 입력된 부분의 넓이 출력
	
	public static void main(String[] args) throws Exception {
		Scanner sc = new Scanner(System.in);
		int[][] white = new int[100][100];
		int ans = 0, N = sc.nextInt();
		for (int i = 0; i < N; i++) {
			int x = sc.nextInt(), y = sc.nextInt();
			for (int r = 0; r < 10; r++) {
				for (int c = 0; c < 10; c++) {
					white[x + r - 1][y + c - 1] = 1;
				}
			}
		}
		for (int i = 0; i < 100; i++) {
			for (int j = 0; j < 100; j++) {
				if (white[i][j] == 1) ans++;
			}
		}
		System.out.println(ans);
		sc.close();
	}

}
 