
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class B05_Ladder1_서기원 {

	static int r, c;
	static int SIZE = 100;
	static int[][] ladder;
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		for (int tc = 1; tc <= 10; tc++) {
			tc = Integer.parseInt(br.readLine());
			ladder = new int[SIZE][SIZE];
			r = SIZE - 1;
			
			for (int i = 0; i < SIZE; i++) {
				StringTokenizer st = new StringTokenizer(br.readLine());
				for (int j = 0; j < SIZE; j++) {
					ladder[i][j] = Integer.parseInt(st.nextToken());
					if (ladder[i][j] == 2) c = j;
				}
			}
			
			while ((r--) != 0) {
				boolean check = false;
				while (c + 1 < SIZE && ladder[r][c + 1] == 1) {
					check = true;
					c++;
				}
				
				if (!check) {
					while (c - 1 >= 0 && ladder[r][c - 1] == 1) c--;
				}
			}
			
			System.out.println("#" + tc + " " + c);
		}

	}

}
