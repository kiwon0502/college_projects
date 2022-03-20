import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayDeque;
import java.util.Arrays;
import java.util.Deque;
import java.util.StringTokenizer;

public class algo_20304_2 {

	static int N, M, answer;
	static int[] arr;
	static Deque<Integer> dq = new ArrayDeque<Integer>();
	
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;
		N = Integer.parseInt(br.readLine()); // 패스워드 최댓값
    M = Integer.parseInt(br.readLine()); // 해커가 사용한 패스워드 갯수
    
    arr = new int[N + 1];
    Arrays.fill(arr, -1);
    st = new StringTokenizer(br.readLine());
        
    for (int i = 1; i <= M; i++) {
      int x = Integer.parseInt(st.nextToken());
      arr[x] = 0;
      dq.offerLast(x);
    }
    
    while (!dq.isEmpty()) {
      int cur = dq.pollFirst();
      for (int i = 0; i < 20; i++) {
        int next = cur ^ (1 << i);
        if (next > N || arr[next] != -1) continue;
        arr[next] = arr[cur] + 1;
        dq.offerLast(next);
        answer = Math.max(answer, arr[next]);
      }
    }
    System.out.println(answer);
	}

}
