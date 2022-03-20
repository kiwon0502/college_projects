import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Stack;

public class A10_계산기2_서기원 {
	
	static int l;
	static String infix;
	static String postfix;
	static Stack<Character> op;
	static Stack<Integer> nums;
	static int ans;

	static void conversion(char c) {
		// '(' push
		if (c == '(') op.push(c);
		else if (c == ')') {
			while (!op.isEmpty()) {
				if (op.peek() == '(') {
					op.pop();
					break;
				}
				postfix += op.pop();
			}
		}
	}
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		for (int tc = 1; tc <= 10; tc++) {
			// 초기화
			op = new Stack<>();
			nums = new Stack<>();
			postfix = "";
			ans = 0;
						
			l = Integer.parseInt(br.readLine());
			infix = br.readLine();
			
			
			
			

			System.out.println("#" + tc + " " + nums.pop());
		}
	}

}
