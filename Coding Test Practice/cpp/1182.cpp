#include <iostream>
using namespace std;
#define MAX 25

int N, S, ans;
int arr[MAX];

void solve(int idx, int sum) {
  if (idx == N) return;
  if (sum + arr[idx] == S) ans++;

  solve(idx + 1, sum);
  solve(idx + 1, sum + arr[idx]);
}

int main() {
  ios::sync_with_stdio(0); cout.tie(0); cin.tie(0);
  cin >> N >> S;
  for (int i = 0; i < N; i++) cin >> arr[i];
  solve(0, 0);
  cout << ans;
  return 0;
}