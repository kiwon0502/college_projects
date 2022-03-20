
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Stack;
import java.util.StringTokenizer;

public class B03_탑_서기원 {
	
	// stack이 비어있을 경우 0을 출력하고 해당 값을 push
	// stack의 top값이 최근 값보다 작을 경우 0을 출력하고 top값을 pop 이후 push
	// stack의 top값이 최근 값보다 클 경우 top의 위치를 출력하고 최근 값을 push
	// 모든 탑을 검사할 때까지 위 과정을 반복
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int N = Integer.parseInt(br.readLine());
		StringTokenizer st = new StringTokenizer(br.readLine());
		Stack<int[]> stack = new Stack<>();
		for (int i = 1; i <= N; i++) {
			int cur = Integer.parseInt(st.nextToken());
			while(!stack.isEmpty()) {
				if (stack.peek()[1] >= cur) {
					System.out.print(stack.peek()[0] + " ");
					break;
				}
				stack.pop();
			}
			if (stack.isEmpty()) System.out.print("0 ");
			stack.push(new int[] {i, cur});
		}
	}

}
