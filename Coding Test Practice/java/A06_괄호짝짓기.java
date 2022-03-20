
import java.util.Scanner;
import java.util.Stack;

public class A06_괄호짝짓기_서기원 {

	// 왼쪽 괄호일 경우 stack에 넣기
	// 오른쪽 괄호일 경우 stack 맨 위가 자기와 짝인지 확인
	// 비어있거나 짝이 아닐 경우 매칭 불가능
	
	static char[] left = {'(', '<', '{', '['};
	static char[] right = {')', '>', '}', ']'};

	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		for (int tc = 1; tc <= 10; tc++) {
			int ans = 1;
			int N = in.nextInt();
			String s = in.next();
			Stack<Character> st = new Stack<>();
			
			outer:
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < 4; j++) {
					if (left[j] == s.charAt(i)) {
						st.push(left[j]);
						break;
					}
					else if (right[j] == s.charAt(i)) {
						if (!st.isEmpty() && st.peek() == left[j]) {
							st.pop();
							break;
						}
						ans = 0;
						break outer;
					}
				}
			}
			if (!st.empty()) ans = 0;
			System.out.printf("#%d %d\n", tc, ans);
		}
		in.close();
	}

}
