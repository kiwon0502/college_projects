import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class A20_도영이가만든맛있는음식_서기원 {

	static int ans;
	static int[][] flavor;
	static boolean[] visited;
	
	// 음식을 iteration 돌면서
	// 포함할 지 안할 지를 결정하면서 dfs
	// 끝까지 갔을 때 신맛, 쓴맛 계산 후 정답 도출
	static void comb(int cur) {
		if (cur == flavor.length) {
			int s = 1;
			int b = 0;
			int cnt = 0;
			for (int i = 0; i < visited.length; i++) {
				if (visited[i]) {
					cnt++;
					s *= flavor[i][0];
					b += flavor[i][1];
				}
			}
			if (cnt == 0) return;
			ans = Math.min(ans, Math.abs(s - b));
			return;
		}
		
		visited[cur] = true;
		comb(cur + 1);
		visited[cur] = false;
		comb(cur + 1);
	}
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;
		
		int N = Integer.parseInt(br.readLine());
		flavor = new int[N][2];
		visited = new boolean[N];
		
		for (int i = 0; i < N; i++) {
			st = new StringTokenizer(br.readLine());
			flavor[i][0] = Integer.parseInt(st.nextToken());
			flavor[i][1] = Integer.parseInt(st.nextToken());
		}
		ans = Integer.MAX_VALUE;
		comb(0);
		System.out.println(ans);
	}

}
