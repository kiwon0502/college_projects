
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Stack;

public class A11_계산기3_서기원 {

	static int l;
	static String infix;
	static String postfix = "";
	static Stack<Character> op = new Stack<>();
	static Stack<Integer> nums = new Stack<>();
	static int ans;

	public static void makeHu(CharSequence str) {
		for (int i = 0; i < str.length(); i++) conversion(str.charAt(i));
		while (!op.isEmpty()) {
			postfix += op.pop();
		}
		System.out.println(postfix);
	}
	
	public static int calculate() {
		for (int i = 0; i < postfix.length(); i++) calc(postfix.charAt(i));
		return nums.pop();
	}
	
	static void conversion(char c) {
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
		else if (c == '*') op.push(c);
		else if (c == '+') {
			if (op.isEmpty()) op.push(c);
			else {
				while (!op.isEmpty()) {
					if (op.peek() == '(') {
						op.push(c);
						break;
					}
					postfix += op.pop();
				}
			}
		}
		else postfix += c;
	}
	
	static void calc(char c) {
		if ('0' <= c && c <= '9') nums.push(c - '0');
		else {
			int one = nums.pop();
			int two = nums.pop();
			if (c == '*') nums.push(one * two);
			else nums.push(one + two);
		}
	}
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		for (int tc = 1; tc <= 1; tc++) {
			// 초기화
			op = new Stack<>();
			nums = new Stack<>();
			postfix = "";
						
			l = Integer.parseInt(br.readLine());
			infix = br.readLine();
			
			// for (int i = 0; i < l; i++) conversion(infix.charAt(i));
			makeHu(infix);
			// for (int i = 0; i < postfix.length(); i++) calc(postfix.charAt(i));
			// calculate();

			System.out.println("#" + tc + " " + calculate());
		}
	}

}
