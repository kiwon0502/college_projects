#include <iostream>
typedef long long ll;
using namespace std;

ll N, input[105];
ll dp[105][25];

void solve(int idx) {
    if (idx == N) return;
    for (int i = 0; i <= 20; i++) {
        if (dp[idx - 1][i] != 0) {
            if (i + input[idx] <= 20) dp[idx][i + input[idx]] += dp[idx - 1][i];
            if (i - input[idx] >= 0) dp[idx][i - input[idx]] += dp[idx - 1][i];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N; 
    for (int i = 1; i <= N; i++) cin >> input[i];
    dp[1][input[1]] = 1;

    for (int i = 2; i < N; i++) solve(i);
    cout << dp[N - 1][input[N]];
    return 0;
}