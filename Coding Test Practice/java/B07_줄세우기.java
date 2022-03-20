import java.util.Scanner;

public class B07_줄세우기_서기원 {

	static int[] num = new int[9];
	static int[] select = new int[7];
	
	// 9 명 중 7 명의 난쟁이를 뽑는 경우의 수 생각
	// cnt번째 난쟁이를 뽑을 때 start부터 생각하는 함수
	public static void dfs(int cnt, int start) {
		if (cnt == 7) {
			int sum = 0;
			for (int n : select) sum += n;
			if (sum == 100) {
				for (int n : select) System.out.println(n);
			}
			return;
		}
		
		for (int i = start; i < 9; i++) {
			select[cnt] = num[i];
			dfs(cnt + 1, i + 1);
		}
	}
	
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		for (int i = 0; i < 9; i++) num[i] = sc.nextInt();
		dfs(0, 0);		
		sc.close();
	}

}
