import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class A19_규영이와인영이의카드게임_서기원 {

	static boolean[] card;
	static boolean[] visited;
	static int[] kyu = new int[9];
	static int[] in = new int[9];
	static int win, lose;
	
	// 인영이가 내는 카드의 경우의 수 9! 완전탐색
	static void per(int r, int sum1, int sum2) {
		if (r == 9) {
			// 이긴 경우의 수
			// 진 경우의 수 구하기
			if (sum1 > sum2) win++;
			else if (sum1 < sum2) lose++;
			return;
		}
		
		for (int i = 0; i < 9; i++) {
			if (!visited[i]) {
				visited[i] = true;
				if (kyu[r] > in[i]) per(r + 1, sum1 + kyu[r] + in[i], sum2);
				else per(r + 1, sum1, sum2 + kyu[r] + in[i]);
				visited[i] = false;
			}
		}
	}
	
	public static void main(String[] args) throws Exception {
		StringBuilder sb = new StringBuilder();
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;
		
		int T = Integer.parseInt(br.readLine());
		for (int tc = 1; tc <= T; tc++) {
			win = lose = 0;
			visited = new boolean[9];
			card = new boolean[19];
			st = new StringTokenizer(br.readLine());
			for (int i = 0; i < 9; i++) {
				kyu[i] = Integer.parseInt(st.nextToken());
				card[kyu[i]] = true;
			}
			
			for (int i = 1, idx = 0; i <= 18; i++) {
				if (!card[i]) in[idx++] = i;
			}
			
			per(0, 0, 0);
			sb.append("#"+tc+" "+win+" "+lose+"\n");
		}
		System.out.println(sb.toString());
	}

}
