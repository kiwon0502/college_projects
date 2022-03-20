#include <iostream>
#include <algorithm>
using namespace std;

int N;
int dp[101][10][1<<10];
const int MOD = 1e9;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;

    dp[1][0][0] = 0;
    for (int i = 1; i < 10; i++) dp[1][i][1<<i] = 1;
    for (int i = 2; i <= N; i++) {
        for (int cur = 0; cur <= 9; cur++) {
            for (int state = 0; state < (1<<10); state++) {
                if (cur == 0)
                    dp[i][cur][state | (1<<cur)] = (dp[i][cur][state | (1<<cur)] + dp[i - 1][cur + 1][state])%MOD;
                else if (cur == 9) 
                    dp[i][cur][state | (1<<cur)] = (dp[i][cur][state | (1<<cur)] + dp[i - 1][cur - 1][state])%MOD;
                else {
                    dp[i][cur][state | (1<<cur)] = (dp[i][cur][state | (1<<cur)] + dp[i - 1][cur + 1][state])%MOD;
                    dp[i][cur][state | (1<<cur)] = (dp[i][cur][state | (1<<cur)] + dp[i - 1][cur - 1][state])%MOD;
                }
            }
        }
    }

    int ans = 0;
    for (int cur = 0; cur < 10; cur++) {
        ans = (ans + dp[N][cur][1023])%MOD;
    }
    cout << ans;
    return 0;
}
