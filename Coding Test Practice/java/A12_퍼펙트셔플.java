
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

public class A12_퍼펙트셔플_서기원 {

	static int T, N;
	static Queue<String> q1;
	static Queue<String> q2;
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		T = Integer.parseInt(br.readLine());
		
		for (int tc = 1; tc <= T; tc++) {
			q1 = new LinkedList<>();
			q2 = new LinkedList<>();
			
			N = Integer.parseInt(br.readLine());
			StringTokenizer st = new StringTokenizer(br.readLine());
			
			int idx = (N%2 == 0 ? N/2 : N/2 + 1);
			for (int i = 0; i < idx; i++) q1.add(st.nextToken());
			for (int i = idx; i < N; i++) q2.add(st.nextToken());
			
			StringBuilder sb = new StringBuilder();
			for (int i = 1; i < idx; i++) {
				sb.append(" " + q1.poll() + " " + q2.poll());
			}
			
			if (!q1.isEmpty()) sb.append(" " + q1.poll());
			if (!q2.isEmpty()) sb.append(" " + q2.poll());
			
			System.out.println("#" + tc + sb.toString());
		}

	}

}
