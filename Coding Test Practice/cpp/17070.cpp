#include <iostream>
using namespace std;
#define MAX 20
int N, home[MAX][MAX];
int visited[MAX][MAX][3]; // state : 가로 0 세로 1 대각선 2

int main() {
  ios::sync_with_stdio(0); cout.tie(0); cin.tie(0);
  cin >> N;
  for (int i = 1; i <= N; i++) for (int j = 1; j <= N; j++) cin >> home[i][j];

  // 첫째 줄 처리
  for (int c = 2; c <= N; c++) {
    if (home[1][c] == 0) visited[1][c][0] = 1;
    else break;
  }

  // 둘째 줄 처리
  for (int c = 2; c <= N; c++) {
    if (home[2][c] == 0) {
      visited[2][c][0] += (visited[2][c-1][0] + visited[2][c-1][2]);
      if (home[1][c] == 0 && home[2][c-1] == 0) {
        visited[2][c][2] += visited[1][c-1][0];
      }
    }
  }

  for (int r = 3; r <= N; r++) {
    for (int c = 2; c <= N; c++) {
      if (home[r][c] == 0) {
        visited[r][c][0] += (visited[r][c-1][2] + visited[r][c-1][0]);
        visited[r][c][1] += (visited[r-1][c][1] + visited[r-1][c][2]);

        if (home[r-1][c] == 0 && home[r][c-1] == 0) {
          visited[r][c][2] += (visited[r-1][c-1][0] + visited[r-1][c-1][1] + visited[r-1][c-1][2]);
        }
      }
    }
  }

  int ans = 0;
  for (int i = 0; i < 3; i++) ans += visited[N][N][i];
  cout << ans;
  return 0;
}