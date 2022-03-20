import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.HashMap;

public class A27_친구네트워크_서기원 {

	static int T, F;
	static StringBuilder sb;
	static HashMap<String, Integer> map;
	static int[] root;
	static int[] nodeCnt;
	
	// union-find 알고리즘을 활용하여 트리 형성
	
	public static void init() {
		for (int i = 0; i < root.length; i++) {
			root[i] = i;
			nodeCnt[i] = 1;
		}
	}
	
	public static int find(int x) {
		if (root[x] == x) return x; // 자기 자신이 root라면 return
		return root[x] = find(root[x]);  // root값을 갱신하면서 재귀 호출하여 path compression
	}
	
	public static int union2(int x, int y) {
		x = find(x);
		y = find(y);
		if (x != y) {
			root[y] = x;
			nodeCnt[x] += nodeCnt[y];
			nodeCnt[y] = 1;
		}
		return nodeCnt[x];
	}
	
	public static boolean isSameRoot(int x, int y) {
		if (find(x) == find(y)) return true;
		return false;
	}
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		T = Integer.parseInt(br.readLine());
		sb = new StringBuilder();
		while (T-- > 0) {
			F = Integer.parseInt(br.readLine());
			map = new HashMap<>();
			root = new int[2 * F + 1];
			nodeCnt = new int[2 * F + 1];
			int ppl = 0;
			init();
			
			for (int i = 0; i < F; i++) {
				String[] line = br.readLine().split(" ");
				if (!map.containsKey(line[0])) map.put(line[0], ++ppl);
				if (!map.containsKey(line[1])) map.put(line[1], ++ppl);
				
				int x = map.get(line[0]);
				int y = map.get(line[1]);
				sb.append(union2(x, y)).append("\n"); 
			}
		}
		System.out.print(sb.toString());
	}

}
