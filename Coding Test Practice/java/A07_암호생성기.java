
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

public class A07_암호생성기_서기원 {
	
	// 암호의 숫자를 앞에서 빼 뒤에다 넣는 방식으로 진행
	// Queue 자료구조를 활용하여 위 방식을 풀어나감
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String line = "";
		while ((line = br.readLine()) != null) {
			int tc = Integer.parseInt(line);
			StringTokenizer st = new StringTokenizer(br.readLine());
			Queue<Integer> q = new LinkedList<>();
			
			for (int i = 0; i < 8; i++) {
				q.add(Integer.parseInt(st.nextToken()));
			} // Queue에 처음 숫자 집어넣기
			
			int val = 1;
			while (val != 0) { // 앞의 숫자가 0이 나오기 전까지 계속 진행
				for (int i = 1; i < 6; i++) { // 5 번의 동작이 1 사이클
					val = q.poll();
					val -= i;
					if (val <= 0) val = 0;
					q.offer(val);
					if (val == 0) break; // 0이 나올 경우 멈춤
				}
			}
			
			System.out.print("#" + tc + " ");
			while (!q.isEmpty()) {
				System.out.print(q.peek() + " ");
				q.poll();
			}
			System.out.println();
		}		
	}

}
