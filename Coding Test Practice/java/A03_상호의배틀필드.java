
import java.util.Scanner;

public class A03_상호의배틀필드_서기원 {

	static int[] dr = {-1, 1, 0, 0};
	static int[] dc = {0, 0, -1, 1};
	static char[] icon = {'^', 'v', '<', '>'};
	static int T, H, W, tR, tC, dir, N;
	static char[][] map = new char[21][21];
	
	static void init() {
		for (int i = 0; i < 21; i++) {
			for (int j = 0; j < 21; j++) {
				map[i][j] = 0;
			}
		}
	}
	
	static void move(int d) {
		// Up, Down, Left, Right를 d에 맞춰서 구현
		dir = d;
		map[tR][tC] = icon[dir];
		int nr = tR + dr[dir], nc = tC + dc[dir];
		if (nr < 0 || nc < 0 || nr >= H || nc >= W || map[nr][nc] != '.') return;
		map[nr][nc] = map[tR][tC];
		map[tR][tC] = '.';
		tR = nr;
		tC = nc;
	}
	
	static void shoot() {
		// 전차가 보고 있는 방향으로 발사
		int nr = tR, nc = tC;
		while (true) {
			nr += dr[dir];
			nc += dc[dir];
			if (nr < 0 || nc < 0 || nr >= H || nc >= W || map[nr][nc] == '#') break;
			if (map[nr][nc] == '*') {
				map[nr][nc] = '.';
				break;
			}
		}
	}
	
	static void print() {
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				System.out.print(map[i][j]);
			}
			System.out.println();
		}
	}
	
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		T = sc.nextInt();
		for(int test_case = 1; test_case <= T; test_case++) {
			init();
			// 입력부
			H = sc.nextInt();
			W = sc.nextInt();			
			for (int i = 0; i < H; i++) {
				String temp = sc.next();
				for (int j = 0; j < W; j++) {
					map[i][j] = temp.charAt(j);
					
					// 전차 현재 위치 파악
					if (map[i][j] == '^') {
						tR = i;
						tC = j;
						dir = 0;
					}
					else if (map[i][j] == 'v') {
						tR = i;
						tC = j;
						dir = 1;
					}
					else if (map[i][j] == '<') {
						tR = i;
						tC = j;
						dir = 2;
					}
					else if (map[i][j] == '>') {
						tR = i;
						tC = j;
						dir = 3;
					}
					
				}
			}
			N = sc.nextInt();
			String cmd = sc.next();

			for (int i = 0; i < N; i++) {
				switch(cmd.charAt(i)) {
				case 'U':
					move(0);
					break;
				case 'D':
					move(1);
					break;
				case 'L':
					move(2);
					break;
				case 'R':
					move(3);
					break;
				case 'S':
					shoot();
					break;
				}
			}

			// 출력부
			System.out.print("#" + test_case + " ");
			print();
		}
		sc.close();
	}

}
