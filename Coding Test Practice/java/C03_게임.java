
import java.util.Scanner;

public class C03_게임_서기원 {

	// 바뀌는 A번째와 B번째 컵에 공이 존재할 경우
	// A -> B
	// B -> A 형태로 X값 갱신
	
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int N = sc.nextInt();
		int X = sc.nextInt();
		int K = sc.nextInt();
		
		for (int i = 0; i < K; i++) {
			int A = sc.nextInt();
			int B = sc.nextInt();
			
			if (X == A) X = B;
			else if (X == B) X = A;
		}
		
		System.out.println(X);		
		sc.close();
	}

}
