#include <iostream>
#include <algorithm>
using namespace std;
#define MAX 4001
string S, T;
int dp[MAX][MAX];

int main() {
  ios::sync_with_stdio(0); cout.tie(0); cin.tie(0);
  cin >> S >> T;
  int ans = 0;
  for (int i = 0; i < S.size(); i++) {
    for (int j = 0; j < T.size(); j++) {
      if (S[i] == T[j]) {
        if (i == 0 || j == 0) dp[i][j] = 1;
        else dp[i][j] = dp[i-1][j-1]+1;
        ans = max(ans, dp[i][j]);
      }
    }
  }
  cout << ans;
  return 0;
}