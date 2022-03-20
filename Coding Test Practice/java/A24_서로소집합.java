import java.io.BufferedReader;
import java.io.InputStreamReader;

public class A24_서로소집합_서기원 {

	// union-find 알고리즘 활용
	
	static int N, M;
	static int[] parent; // 집합의 root를 확인하는 배열
	static StringBuilder sb; // 결과값 저장
	
	public static void init() { // 초기 root를 자기 자신으로 초기화
		for (int i = 1; i <= N; i++) parent[i] = i;
	}
	
	public static int find(int a) {
		if (parent[a] == a) return a; // 자기 자신이 root라면 return
		return parent[a] = find(parent[a]);  // root값을 갱신하면서 재귀 호출하여 path compression
	}
	
	public static void union(int a, int b) {
		a = find(a);
		b = find(b);
		if (a != b) parent[b] = a; // 같지 않을 경우 합친다
	}
	
	public static boolean isSameParent(int a, int b) {
		if (find(a) == find(b)) return true;
		return false;  // 같은 root를 가질 경우 true 리턴
	}
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		sb = new StringBuilder();
		int T = Integer.parseInt(br.readLine());
		for (int tc = 1; tc <= T; tc++) {
			sb.append("#").append(tc).append(" ");
			String[] line = br.readLine().split(" ");
			N = Integer.parseInt(line[0]);
			M = Integer.parseInt(line[1]);
			
			parent = new int[N+1];
			init();
			
			for (int i = 0; i < M; i++) {
				line = br.readLine().split(" ");
				int cmd = Integer.parseInt(line[0]);
				int a = Integer.parseInt(line[1]);
				int b = Integer.parseInt(line[2]);
				
				if (cmd == 0) union(a, b);
				else {
					if (isSameParent(a, b)) sb.append("1");
					else sb.append("0");
				}
			}
			
			sb.append("\n");
		}
		System.out.println(sb.toString());

	}

}
