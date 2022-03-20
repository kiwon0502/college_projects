import java.util.ArrayList;
import java.util.Scanner;

public class A26_치킨배달_서기원 {

	static class Node {
		int r, c;
		Node(int r, int c) {
			this.r = r;
			this.c = c;
		}
	}
	
	// 치킨의 조합을 결정한 뒤
	// 각 집에서 가장 가까운 치킨 집을 완전탐색으로 확인하여
	// 총 거리의 최솟값을 구한다
	
	static int N, M, ans;
	static boolean[] select;
	static ArrayList<Node> chicks = new ArrayList<>();
	static ArrayList<Node> houses = new ArrayList<>();
	
	public static int getDist(Node house, Node chicken) {
		return Math.abs(house.r - chicken.r) + Math.abs(house.c - chicken.c); 
	}
	
	public static void dfs(int idx, int cnt) {
		if (cnt == M) {
			int city_dist = 0;
			for (int i = 0; i < houses.size(); i++) {
				int dist = Integer.MAX_VALUE;
				for (int j = 0; j < chicks.size(); j++) {
					if (!select[j]) continue;
					dist = Math.min(dist, getDist(houses.get(i), chicks.get(j)));
				}
				city_dist += dist;
			}
			ans = Math.min(ans, city_dist);
			return;
		}
		
		for (int i = idx; i < chicks.size(); i++) {
			select[i] = true;
			dfs(i + 1, cnt + 1);
			select[i] = false;			
		}
	}
	
	public static void main(String[] args) throws Exception {
		Scanner sc = new Scanner(System.in);
		N = sc.nextInt();
		M = sc.nextInt();
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				int x = sc.nextInt();
				if (x == 1) houses.add(new Node(i, j));
				else if (x == 2) chicks.add(new Node(i, j));
			}
		}
		
		ans = Integer.MAX_VALUE;
		select = new boolean[chicks.size()];
		dfs(0, 0);
		System.out.println(ans);
	}

}
