#include <iostream>
using namespace std;
const int MAX = 1e6 + 5;
int N;
int dp[MAX];
int before[MAX];

int solve(int x) {
    dp[1] = 0, before[1] = -1;
    for (int i = 2; i <= x; i++) {
        dp[i] = dp[i - 1] + 1;
        before[i] = i - 1;

        if (i%2 == 0 && dp[i] > dp[i/2] + 1) {
            dp[i] = dp[i/2] + 1;
            before[i] = i/2;
        }
        if (i%3 == 0 && dp[i] > dp[i/3] + 1) {
            dp[i] = dp[i/3] + 1;
            before[i] = i/3;
        }
    }
    return dp[x];
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    cout << solve(N) << "\n";
    while (N != -1) {
        cout << N << " ";
        N = before[N];
    }
    return 0;
}
