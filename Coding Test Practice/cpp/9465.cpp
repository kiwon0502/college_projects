#include <iostream>
#include <algorithm>
using namespace std;
#define MAX 100001

int T, n;
int arr[MAX][2], dp[MAX][3];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 0; i < 2; i++) for (int j = 1; j <= n; j++) cin >> arr[j][i];

        dp[1][0] = arr[1][0];
        dp[1][1] = arr[1][1];
        for (int i = 2; i <= n; i++) {
            dp[i][0] = max(dp[i - 1][1], dp[i - 1][2]) + arr[i][0];
            dp[i][1] = max(dp[i - 1][0], dp[i - 1][2]) + arr[i][1];
            dp[i][2] = max({dp[i - 1][0], dp[i - 1][1], dp[i - 1][2]});
        }
        cout << max({dp[n][0], dp[n][1], dp[n][2]}) << "\n";
    }
    return 0;
}
