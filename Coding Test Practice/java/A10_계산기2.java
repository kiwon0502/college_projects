
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Stack;

public class A10_계산기2_서기원 {
	
	static int get_priority(char c) {
		if (c == '*') return 1;
		if (c == '+') return 2;
		else return -1;
	}
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		for (int tc = 1; tc <= 10; tc++) {
			int N = Integer.parseInt(br.readLine());
			String line = br.readLine();
			
			Stack<Character> op = new Stack<>();
			StringBuilder sb = new StringBuilder();
			for (int i = 0; i < N; i++) {
				char c = line.charAt(i);
				if ('0' <= c && c <= '9') sb.append(c);
				else {
					if (op.isEmpty()) op.push(c);
					else {
						if (get_priority(op.peek()) <= get_priority(c)) {
							sb.append(op.pop());
							op.push(c);
						}
						else op.push(c);
					}
				}
			}
			while (!op.isEmpty()) {
				sb.append(op.pop());
			}
			String post = sb.toString();
			
			Stack<Integer> nums = new Stack<>();
			for (int i = 0; i < post.length(); i++) {
				char c = post.charAt(i);
				if ('0' <= c && c <= '9') nums.push(c - '0');
				else {
					int one = nums.pop();
					int two = nums.pop();
					if (c == '*') nums.push(one * two);
					else nums.push(one + two);
				}
			}

			System.out.println("#" + tc + " " + nums.pop());
		}
	}

}
