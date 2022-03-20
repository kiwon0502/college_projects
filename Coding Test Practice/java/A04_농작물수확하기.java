
import java.util.Scanner;

public class A04_농작물수확하기_서기원 {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int T;
		T = sc.nextInt();
		
		for(int test_case = 1; test_case <= T; test_case++) {
			int N = sc.nextInt();
			int[][] farm = new int[N][N];
			for (int i = 0; i < N; i++) {
				String temp = sc.next();
				for (int j = 0; j < N; j++) {
					farm[i][j] = temp.charAt(j) - '0';
				}
			}
			
			int ans = 0;
			int base = N / 2;
			// 위쪽 삼각형
			for (int i = 0; i < base; i++) {
				for (int j = base - i; j <= base + i; j++) {
					ans += farm[i][j];
				}
			}
			
			// 아래쪽 삼각형
			for (int i = base; i >= 0; i--) {
				for (int j = base - i; j <= base + i; j++) {
					ans += farm[N - i - 1][j];
				}
			}
			
			System.out.println("#" + test_case + " " + ans);
		}
		sc.close();
	}

}
