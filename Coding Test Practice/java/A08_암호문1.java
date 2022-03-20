
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.StringTokenizer;

public class A08_암호문1_서기원 {

	// 암호문은 integer로 구성되어 있다.
	// 처리하는 방식이 임의의 위치에 삽입하는 방식밖에 존재하지 않는다.
	// 원소 삽입이 O(1)밖에 소요되지 않는 linked list를 활용하기 제격
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		for (int tc = 1; tc <= 10; tc++) {
			int N = Integer.parseInt(br.readLine()); // 원본 암호문의 길이
			StringTokenizer num = new StringTokenizer(br.readLine()); // 원본 암호문을 token화
			LinkedList<Integer> pwd = new LinkedList<>(); // 암호문을 저장하는 list
			
			for (int i = 1; i <= N; i++) {
				pwd.add(Integer.parseInt(num.nextToken()));
			} // 원본 암호문 저장
			
			int M = Integer.parseInt(br.readLine()); // 명령어의 개수
			StringTokenizer cmd = new StringTokenizer(br.readLine()); // 명령어를 token화
			for (int i = 0; i < M; i++) {
				String I = cmd.nextToken(); // "I"
				int x = Integer.parseInt(cmd.nextToken()); // x
				int y = Integer.parseInt(cmd.nextToken()); // y
				for (int j = 0; j < y; j++) { // s들을 입력받아 주어진 위치에 삽입
					pwd.add(x + j, Integer.parseInt(cmd.nextToken()));
				}
			}
			
			System.out.print("#"+tc+" ");
			for (int i = 0; i < 10; i++) {
				System.out.print(pwd.get(i) + " ");
			}
			System.out.println();			
		}
	}

}
