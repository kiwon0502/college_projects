#include <iostream>
#include <algorithm>
#define MAX 505
using namespace std;

int n, ans;
int tri[MAX][MAX], dp[MAX][MAX];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++)
    for (int j = 1; j <= i; j++)
        cin >> tri[i][j];

    dp[1][1] = tri[1][1];
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            if (j == 1) dp[i][j] += dp[i - 1][j] + tri[i][j];
            else if (1 < j && j < i) {
                dp[i][j] += max(dp[i - 1][j - 1], dp[i - 1][j]) + tri[i][j];
            }
            else if (j == i) {
                dp[i][j] += dp[i - 1][j - 1] + tri[i][j];
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        ans = max(ans, dp[n][i]);
    }

    cout << ans;
    return 0;
}