
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class A14_사칙연산유효성검사_서기원 {

	// 연산자의 경우 2개의 자식 노드가 필요
	// 따라서 입력을 받으며 자식 노드가 있을 시 해당 노드가 연산자인지 확인
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;
		for (int tc = 1; tc <= 1; tc++) {
			int N = Integer.parseInt(br.readLine());
			int ans = 1;
			
			for (int i = 1; i <= N; i++) {
				st = new StringTokenizer(br.readLine());
				st.nextToken();
				char node = st.nextToken().charAt(0);
				if (st.hasMoreTokens()) { // 자식 노드가 있을 경우
					if (node >= '0' && node <= '9') ans = 0; // 연산자여야 한다
				}
				else { // 리프 노드일 경우
					if (node < '0' || node > '9') ans = 0; // 숫자여야 한다
				}
			}
			
			System.out.println("#" + tc + " " + ans);
		}
	}

}
