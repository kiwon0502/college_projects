#include <iostream>
#define mod 10007
using namespace std;

int N, K;
int dp[1001][1001];

int nCr(int n, int r) {
    if (dp[n][r] != 0) return dp[n][r];
    if (n == r || r == 0) return 1;
    return dp[n][r] = (nCr(n - 1, r - 1) + nCr(n - 1, r))%mod;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> K;
    cout << nCr(N, K);
    return 0;
}