#include <iostream>
#include <algorithm>
using namespace std;
#define MAX 20

int N;
int T[MAX], P[MAX], dp[MAX];
int max_val;

void solve(int day, int now_sum, int added_num) {
  if (day == N + 1) {
    max_val = max(max_val, now_sum);
    return;
  }
  else if (day > N + 1) {
    max_val = max(max_val, now_sum - added_num);
    return;
  }

  for (int i = day + T[day]; i <= N + T[day]; i++) {
    solve(i, now_sum + P[day], P[day]);
  }

}

int main() {
  ios::sync_with_stdio(0); cout.tie(0); cin.tie(0);
  cin >> N;
  for (int i = 1; i <= N; i++) cin >> T[i] >> P[i];
  for (int i = 1; i <= N; i++) solve(i, 0, 0);
  cout << max_val;
  return 0;
}