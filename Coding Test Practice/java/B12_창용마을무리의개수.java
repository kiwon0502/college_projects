import java.io.BufferedReader;
import java.io.InputStreamReader;

public class B12_창용마을무리의개수_서기원 {
	
	// union-find 알고리즘 활용
	static int T, N, M;
	static int[] root;
	static boolean[] check;
	
	public static void init() { // 초기 root 값 자기 자신으로 초기화
		for (int i = 1; i <= N; i++) root[i] = i;
	}
	
	public static int find(int x) { // root 값을 리턴
		if (root[x] == x) return x;
		return root[x] = find(root[x]); // path compression
	}
	
	public static void union(int x, int y) {
		x = find(x);
		y = find(y);
		if (x != y) root[y] = x; // root가 다를 시 union
	}
	
	public static int getNum() {
		int ret = 0;
		for (int i = 1; i <= N; i++) {
			int r = find(i);
			if (!check[r]) {
				ret++;
				check[r] = true;
			}
		}
		return ret;		// 다른 root를 가진 노드의 개수 구하기
	}
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder sb = new StringBuilder();
		T = Integer.parseInt(br.readLine());
		
		for (int tc = 1; tc <= T; tc++) {
			sb.append("#").append(tc).append(" ");
			String[] line = br.readLine().split(" ");
			N = Integer.parseInt(line[0]);
			M = Integer.parseInt(line[1]);
			root = new int[N+1];
			check = new boolean[N+1];
			init();
			for (int i = 0; i < M; i++) {
				line = br.readLine().split(" ");
				int x = Integer.parseInt(line[0]);
				int y = Integer.parseInt(line[1]);
				union(x, y);
			}
			sb.append(getNum()).append("\n");
		}
		System.out.println(sb.toString());		
	}
}
