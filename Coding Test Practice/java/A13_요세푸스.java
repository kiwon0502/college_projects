
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

public class A13_요세푸스_서기원 {

	// FIFO 방식을 활용하기 위해 Queue 사용
	// K-1개의 숫자를 poll한 후 뒤에 add
	// K번째 숫자를 출력
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		int N = Integer.parseInt(st.nextToken());
		int K = Integer.parseInt(st.nextToken());
		
		Queue<Integer> q = new LinkedList<>();
		for (int i = 1; i <= N; i++) q.add(i);
		
		StringBuilder sb = new StringBuilder();
		sb.append("<");
		
		while (!q.isEmpty()) {
			for (int i = 1; i < K; i++) {
				q.add(q.poll());
			}
			sb.append(q.poll() + ", ");
		}
		int l = sb.length();
		sb.delete(l - 2, l);
		sb.append(">");
		System.out.println(sb);
		
	}

}
