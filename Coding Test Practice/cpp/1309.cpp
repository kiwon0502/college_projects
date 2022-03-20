#include <iostream>
#include <algorithm>
#define mod 9901
#define MAX 100010
using namespace std;

int N;
int dp[MAX][3];
    // state
    // [i][0] : i번째 칸에 o x
    // [i][1] : i번째 칸에 x o
    // [i][2] : i번째 칸에 x x


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;

    for (int i = 0; i < 3; i++) dp[1][i] = 1;
    for (int i = 2; i <= N; i++) {
        dp[i][0] = (dp[i - 1][1] + dp[i - 1][2])%mod;
        dp[i][1] = (dp[i - 1][0] + dp[i - 1][2])%mod;
        dp[i][2] = (dp[i - 1][0] + dp[i - 1][1] + dp[i - 1][2])%mod;
    }
    cout << (dp[N][0] + dp[N][1] + dp[N][2])%mod;
    return 0;
}