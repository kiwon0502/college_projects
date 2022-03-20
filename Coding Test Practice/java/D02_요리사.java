import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class D02_요리사_서기원 {

	static int T, N, ans;
	static int[][] syn;
	static boolean[] visited;
	
	// 각 그룹의 시너지 값의 합을 구하는 함수
	// 16 * 16 = 256 완전 탐색에서
	// 같은 그룹의 재료들의 시너지 값을 합산하여 return
	public static int sumSyn(boolean flag) {
		int ret = 0;
		for (int i = 1; i <= N; i++) {
			if (visited[i] == flag) {
				for (int j = 1; j <= N; j++) {
					if (visited[j] == flag) {
						ret += syn[i][j];
					}
				}
			}
		}
		return ret;
	}
	
	// N/2개 고르는 조합 함수 (재귀로 구성)
	// N의 최댓값이 16개이기 때문에 경우의 수가 작아 재귀로 구성
	public static void nCr(int depth, int k) {
		if (depth == N/2) {
			int temp = Math.abs(sumSyn(true) - sumSyn(false));
			ans = Math.min(ans, temp);
			return;
		}
		
		for (int i = k; i <= N; i++) {
			visited[i] = true;
			nCr(depth + 1, i + 1);
			visited[i] = false;
		}
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder sb = new StringBuilder();
		T = Integer.parseInt(br.readLine());
		for (int tc = 1; tc <= T; tc++) {
			ans = Integer.MAX_VALUE; // 최솟값 구하는 것이기 때문에 MAX_VALUE로 초기화
			N = Integer.parseInt(br.readLine());
			syn = new int[N + 1][N + 1];
			// 2개의 그룹으로 나누는 것이기 때문에
			// boolean으로 구성하여 편리함과 메모리 크기의 이점을 챙겼다.
			visited = new boolean[N + 1];
			
			for (int i = 1; i <= N; i++) {
				String[] line = br.readLine().split(" ");
				for (int j = 0; j < N; j++) {
					syn[i][j + 1] = Integer.parseInt(line[j]);
				}
			}
			nCr(0, 0);
			sb.append("#").append(tc).append(" ").append(ans).append("\n");
		}
		System.out.println(sb.toString());
	}

}
;