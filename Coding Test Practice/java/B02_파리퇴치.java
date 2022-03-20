
import java.util.Scanner;

public class B02_파리퇴치_서기원 {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int T;
		T = sc.nextInt();

		for(int test_case = 1; test_case <= T; test_case++) {
			int N = sc.nextInt();
			int M = sc.nextInt();
			int[][] area = new int[N][N];
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					area[i][j] = sc.nextInt();
				}
			}
			
			// 완전 탐색
			int ans = 0;
			for (int i = 0; i <= N - M; i++) {
				for (int j = 0; j <= N - M; j++) {
					// M * M 영역에 있는 파리 잡는 횟수
					int kill = 0;
					for (int r = 0; r < M; r++) {
						for (int c = 0; c < M; c++) {
							kill += area[i + r][j + c];
						}
					}
					// 큰 값으로 갱신
					ans = Math.max(ans, kill);
				}
			}
			
			System.out.println("#" + test_case + " " + ans);
		}
		sc.close();
	}

}
