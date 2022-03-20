import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;

public class D01_무선충전_서기원 {
	
	static int T, M, A, ans;
	static ArrayList<Charge> arr;
	static int[] dr = {0, -1, 0, 1, 0};
	static int[] dc = {0, 0, 1, 0, -1};
	static int[] moveA, moveB;
	
	// 맨해튼(?) 거리 계산 함수 // 이름 맞는 지 정확히 기억 안남 
	static int getDist(int ra, int ca, int rb, int cb) {
		return Math.abs(ra - rb) + Math.abs(ca - cb);
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder sb = new StringBuilder();
		T = Integer.parseInt(br.readLine());
		
		for (int tc = 1; tc <= T; tc++) {
			ans = 0;
			arr = new ArrayList<>();
			String[] line = br.readLine().split(" ");
			M = Integer.parseInt(line[0]);
			A = Integer.parseInt(line[1]);
			moveA = new int[M+1];
			moveB = new int[M+1];
			
			// 초기 움직이지 않았을 경우에도 충전이 가능하므로
			// 0번째 index에 0을 넣어 1번째 index부터 움직임을 저장한다
			line = br.readLine().split(" "); // A 이동 정보
			for (int i = 1; i <= M; i++) moveA[i] = Integer.parseInt(line[i-1]);
			line = br.readLine().split(" "); // B 이동 정보
			for (int i = 1; i <= M; i++) moveB[i] = Integer.parseInt(line[i-1]);
			
			for (int i = 0; i < A; i++) {
				line = br.readLine().split(" "); // 배터리 정보
				arr.add(new Charge(Integer.parseInt(line[1]), Integer.parseInt(line[0]),
						Integer.parseInt(line[2]), Integer.parseInt(line[3])));
			}			
			
			// A, B 초기 위치
			Pos pA = new Pos(1, 1);
			Pos pB = new Pos(10, 10);
			for (int i = 0; i <= M; i++) {
				// A, B 이동
				pA = new Pos(pA.r + dr[moveA[i]], pA.c + dc[moveA[i]]);
				pB = new Pos(pB.r + dr[moveB[i]], pB.c + dc[moveB[i]]);

				int maxi = 0; // i번째 움직임에서 충전할 수 있는 최대치
				for (int j = 0; j < arr.size(); j++) {
					for (int k = 0; k < arr.size(); k++) { // 모든 충전소에 대해 완전 탐색
						int sum = 0, Acharge = 0, Bcharge = 0;
						
						// 각각 j번째, k번째 충전소에서 충전한다고 가정
						Charge forA = arr.get(j);
						Charge forB = arr.get(k);
						// 충전이 가능할 경우 performance만큼 충전
						if (getDist(pA.r, pA.c, forA.r, forA.c) <= forA.cov) Acharge = forA.per;
						if (getDist(pB.r, pB.c, forB.r, forB.c) <= forB.cov) Bcharge = forB.per;
						
						if (j != k) sum = Acharge + Bcharge; // 충전소가 다를 경우 단순 덧셈
						// 충전소가 같을 경우 어차피 더해도 자기 자신이고 
						// 0일 수 있으므로 max 연산
						else sum = Math.max(Acharge, Bcharge);
						
						// maxi 갱신
						maxi = Math.max(maxi, sum);
					}
				}
				// maxi들의 합
				ans += maxi;
			}
			// 출력
			sb.append("#").append(tc).append(" ").append(ans).append("\n");
		}
		System.out.println(sb.toString());
	}

}

class Pos {
	int r, c;
	public Pos(int r, int c) {
		this.r = r;
		this.c = c;
	}
	public void print() {
		System.out.printf("%d %d\n", r, c);
	}
}


class Charge {
	int r, c, cov, per;
	public Charge(int r, int c, int cov, int per) {
		this.r = r;
		this.c = c;
		this.cov = cov;
		this.per = per;
	}
	public void print() {
		System.out.printf("%d %d %d %d\n", r, c, cov, per);
	}
}





