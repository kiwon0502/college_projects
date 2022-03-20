import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.Comparator;

public class B08_냉장고_서기원 {
	
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int N = Integer.parseInt(br.readLine());
		int[][] arr = new int[N][2]; // 최저 온도, 최고 온도 저장 배열
		int cnt = 1;	// 냉장고가 무조건 1개 이상 필요
		
		for (int i = 0; i < N; i++) { // 입력
			String s = br.readLine();
			arr[i][0] = Integer.parseInt(s.split(" ")[0]);
			arr[i][1] = Integer.parseInt(s.split(" ")[1]);
		}
		
		// 최고 온도를 오름차순으로 정렬
		Arrays.sort(arr, new Comparator<int[]>() {
			@Override
			public int compare(int[] o1, int[] o2) {
				return Integer.compare(o1[1], o2[1]);
			}
		});
		
		// 최고 온도 temp 설정
		int max_temp = arr[0][1];
		
		for (int i = 0; i < N; i++) {
			// i번째 화학 물질의 최저 온도가 max_temp보다 크다면 새로운 냉장고 필요
			// max_temp 새로 설정
			if (arr[i][0] <= max_temp) {
				if (arr[i][1] < max_temp) {
					max_temp = arr[i][1];
				}
				continue;
			}
			else {
				max_temp = arr[i][1];
				cnt++;
			}
		}
		
		System.out.println(cnt);

	}

}
