
import java.util.Scanner;

public class C02_비밀번호_서기원 {
	// 2 ^ 64 = 1.846744e+19 (google 기준)
	// 따라서 10 ^ 18은 long 타입으로 비트마스킹 가능
	
	static long A;
	static int g0f, g0s;
	static int g1f, g1s;
	
	static long turnOn(long x, int k) { // k번째 비트를 켠다
		return x |= (1L<<k);
	}
	static long turnOff(long x, int k) { // k번째 비트를 끈다
		return x &= ~(1L<<k);
	}
	
	static void init() {
		int k;
		for (k = 0; k < 64; k++) { // 1이 처음으로 나오는 부분
			if ((A & (1L<<k)) > 0) { g1f = k; break; }
		}
		for (; k < 64; k++) { // 1 묶음이 끝나는 부분
			if ((A & (1L<<k)) == 0) { g1s = k - 1; break; }
		}
		for (k = 0; k < 64; k++) { // 0이 처음으로 나오는 부분
			if ((A & (1L<<k)) == 0) { g0f = k; break; }
		}
		for (; k < 64; k++) { // 0 묶음이 끝나는 부분
			if ((A & (1L<<k)) > 0) { g0s = k-1; break; }
		}
	}
	
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		A = sc.nextLong();
		init();
		long x1 = A, x2 = A;
		
		// A의 비트가 모두 1이라면
		// A보다 작은 수 중에서 1인 비트의 개수가 같은 수를 찾을 수 없다
		if ((A & (A+1)) == 0) x1 = 0;
		// 차례대로 비트를 키고 끄며
		// 가장 작고 가장 큰 수를 찾는다.		
		else {
			x1 = turnOn(x1, g0s);
			x1 = turnOff(x1, g0s+1);
			int k = g0s - 1;
			while (g0f-- > 0) x1 = turnOn(x1, k--);
			while (k >= 0) x1 = turnOff(x1, k--);
		}
		x2 = turnOff(x2, g1s);
		x2 = turnOn(x2, g1s+1);
		int k = g1s-1;
		while (g1f-- > 0) x2 = turnOff(x2, k--);
		while (k >= 0) x2 = turnOn(x2, k--);
		
		System.out.println(x1 + " " + x2);
	}

}
