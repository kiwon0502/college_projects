
import java.util.Scanner;

public class A05_백설공주_서기원 {

	static int n = 9;
	static int r = 7;
	static int[] nan = new int[9];
	static int[] sel = new int[7];
	
	static void nCr(int cnt, int start) {
		if (cnt == r) {
			int sum = 0;
			for (int num : sel) { sum += num; }
			if (sum == 100) {
				for (int num : sel) { System.out.println(num);}
			}
			return;
		}
		
		for (int i = start; i < n; i++) {
			sel[cnt] = nan[i];
			nCr(cnt + 1, i + 1);
		}
	}
	
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		for (int i = 0; i < 9; i++) { nan[i] = in.nextInt(); }
		nCr(0, 0);
		in.close();
	}
	
	// 9 개의 숫자 중 7 개의 숫자를 골라서 더하는 방법
	// 조합을 활용
	// 재귀를 활용한 조합 함수를 구현하여 해결

}
