
import java.util.Arrays;
import java.util.Scanner;

public class C01_콘테스트_서기원 {

	// W, K대학 각 점수 입력
	// 오름차순 정렬 이후 뒤에서부터 3개 값 더하기
	// 출력
	
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int[] W = new int[10];
		int[] K = new int[10];
		
		for (int i = 0; i < 10; i++) W[i] = sc.nextInt();
		for (int i = 0; i < 10; i++) K[i] = sc.nextInt();
		
		Arrays.sort(W);
		Arrays.sort(K);
		
		int w_score = W[9] + W[8] + W[7];
		int k_score = K[9] + K[8] + K[7];
		
		System.out.println(w_score + " " + k_score);
		
		sc.close();
	}

}
