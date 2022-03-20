#include <iostream>
using namespace std;
int N, K, ans, arr[11];

int main() {
  ios::sync_with_stdio(0); cout.tie(0); cin.tie(0);
  cin >> N >> K;
  for (int i = 0; i < N; i++) cin >> arr[i];
  for (int i = N-1; i >= 0; i--) {
    if (K == 0) break;
    ans += (K/arr[i]);
    K %= arr[i];
  }
  cout << ans;
  return 0;
}