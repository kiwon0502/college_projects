import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Arrays;

public class B11_암호만들기_서기원 {
	
	static int L, C;
	static char[] arr;
	static int[] comb;
	static StringBuilder ans = new StringBuilder();
	
	public static boolean ifMo(char c) {
		if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') return true;
		return false;
	} // 모음인지 확인해주는 함수
	
	// 일반적인 조합 함수
	// r개를 이미 뽑은 상태에서 start에서부터 시작
	// mo개의 모음
	// ja개의 자음
	public static void dfs(int start, int r, int mo, int ja) {
		if (r == L) {
			if (mo >= 1 && ja >= 2) ans.append(print()); // 조건을 만족하면 출력
			return;
		}
		
		for (int i = start; i < C; i++) {
			comb[i] = 1;
			dfs(i + 1, r + 1, mo + (ifMo(arr[i])? 1 : 0), ja + (ifMo(arr[i])? 0 : 1));
			comb[i] = 0;
		}
	}
	
	public static String print() {
		StringBuilder sb = new StringBuilder();
		for (int i = 0; i < C; i++) {
			if (comb[i] == 1) sb.append(arr[i]);
		}
		return sb.append("\n").toString();
	}
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String[] line = br.readLine().split(" ");
		L = Integer.parseInt(line[0]);
		C = Integer.parseInt(line[1]);
		arr = new char[C];
		comb = new int[C];
		
		line = br.readLine().split(" ");
		for (int i = 0; i < C; i++) arr[i] = line[i].charAt(0);
		Arrays.sort(arr); // 사전 순 배열을 위해 정렬을 진행
		
		dfs(0, 0, 0, 0);
		System.out.println(ans.toString());
	}

}
