import java.util.ArrayList;
import java.util.Collections;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;

public class A25_아기상어_서기원 {

	static class Node implements Comparable<Node> {
		int r, c, dist;
		Node(int r, int c, int dist) {
			this.r = r;
			this.c = c;
			this.dist = dist;
		}
		
		@Override
		public int compareTo(Node o) {
			if (o.dist < dist) return 1;
			else if (o.dist == dist) {
				if (o.r < r) return 1;
				else if (o.r == r) {
					if (o.c < c) return 1;
					else if (o.c ==  c) return 0;
				}
			}
			return -1;
		}
	}
	
	static int N;
	static int[][] area;
	static int[] dr = {1, -1, 0, 0};
	static int[] dc = {0, 0, 1, -1};
	static ArrayList<Node> fish;
	
	public static void main(String[] args) throws Exception {
		Scanner sc = new Scanner(System.in);
		N = sc.nextInt();
		area = new int[N+1][N+1];
		Queue<Node> q = new LinkedList<>();
		
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				area[i][j] = sc.nextInt();
				if (area[i][j] == 9) {
					q.add(new Node(i, j, 0));
					area[i][j] = 0;
				}
			}
		}
		
		int eat = 0, time = 0, size = 2;
		while (true) {
			LinkedList<Node> canEat = new LinkedList<>();
			int[][] dist = new int[N+1][N+1];
			
			while (!q.isEmpty()) {
				Node cur = q.poll();
				
				for (int i = 0; i < 4; i++) {
					int nr = cur.r + dr[i];
					int nc = cur.c + dc[i];
					
					if (nr < 1 || nc < 1 || nr > N || nc > N) continue;
					if (dist[nr][nc] != 0 || area[nr][nc] > size) continue;
					dist[nr][nc] = dist[cur.r][cur.c] + 1;
					q.add(new Node(nr, nc, dist[nr][nc]));
					if(1 <= area[nr][nc] && area[nr][nc] <= 6 && area[nr][nc] < size) {
						canEat.add(new Node(nr, nc, dist[nr][nc]));
					}
				}
			}
			
			if (canEat.size() == 0) {
				System.out.println(time);
				return;
			}
			
			Collections.sort(canEat);
			Node curFish = canEat.get(0);			
			time += curFish.dist;
			eat++;
			area[curFish.r][curFish.c]= 0;
			if (eat == size) {
				size++;
				eat = 0;
			}
			q.add(new Node(curFish.r, curFish.c, 0));
		}
	}

}






