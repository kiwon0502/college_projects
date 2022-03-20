
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.StringTokenizer;

public class B04_한빈이와SpotMart_서기원 {

	// N개의 과자 봉지 중 2 개를 골라 합이 M보다 작게 하는 풀이
	// 단순 완전 탐색을 활용하여 해결
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int T = Integer.parseInt(br.readLine());
		for (int tc = 1; tc <= T; tc++) {
			String line = br.readLine();
			int N = Integer.parseInt(line.split(" ")[0]);
			int M = Integer.parseInt(line.split(" ")[1]);
			StringTokenizer st = new StringTokenizer(br.readLine());
			ArrayList<Integer> chips = new ArrayList<>();
			for (int i = 0; i < N; i++) {
				chips.add(Integer.parseInt(st.nextToken()));
			}
			
			int ans = -1;
			for (int i = 0; i < N - 1; i++) {
				for (int j = i + 1; j < N; j++) { // 겹치지 않게 2개를 뽑는 경우의 수 모두 생각
					int temp = chips.get(i) + chips.get(j);
					if (temp <= M) {
						ans = Math.max(ans, temp);
					}
				}
			}
			System.out.println("#" + tc + " " + ans);
		}
	}
	
}
