
import java.util.Scanner;

public class B01_달팽이숫자_서기원 {
	
	static int dr[] = {0, 1, 0, -1};
	static int dc[] = {1, 0, -1, 0};						// 행, 열 이동 방향 설정
	
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int T = sc.nextInt();
		for (int tc = 1; tc <= T; tc++) {
			int N = sc.nextInt();
			int snail[][] = new int[N][N];					// N * N 달팽이 배열 초기화
			int dir = 0, r = 0, c = 0;						// 방향 및 현재 장소 변수
			snail[r][c] = 1;								// 1부터 시작
			for (int i = 2; i <= N * N; i++) {				// 2부터 N*N까지
				int nr = r + dr[dir], nc = c + dc[dir];		// 다음 장소를 물색
				if (nr < 0 || nc < 0 || nr >= N || nc >= N ||
						snail[nr][nc] != 0) {				// 가능한지 확인 (벗어나거나 이미 숫자가 있거나)
					dir = (dir + 1)%4;						// 방향 전환
				}
				r += dr[dir];
				c += dc[dir];
				snail[r][c] = i;							// 숫자 입력
			}

			System.out.printf("#%d\n", tc);					// 출력
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					System.out.print(snail[i][j] + " ");
				}
				System.out.println();
			}
		}
		sc.close();
	}

}
