
import java.io.BufferedReader;
import java.io.InputStreamReader;

public class A01_원재의메모리복구하기_서기원 {
	
	public static void main(String[] args) throws Exception {
		BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
		int T = Integer.parseInt(bf.readLine());
		
		for (int t = 1; t <= T; t++) {
			String target = bf.readLine();
			int ans = 0;
			if (target.charAt(0) == '1') ans++;
			for (int i = 1; i < target.length(); i++) {
				if (target.charAt(i - 1) == target.charAt(i)) continue;
				else ans++;
			}
			System.out.printf("#%d %d\n", t, ans);
		}

	}

}
