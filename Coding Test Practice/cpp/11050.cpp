#include <iostream>
using namespace std;

int n, k;
int dp[11][11];

int johab(int N, int K) {
    if (dp[N][K] != 0) return dp[N][K];
    if (N == K || K == 0) return 1;
    return dp[N][K] = johab(N - 1, K - 1) + johab(N - 1, K);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> k;
    cout << johab(n, k);
    return 0;
}