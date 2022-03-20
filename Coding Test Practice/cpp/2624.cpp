#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int T, k;
pair<int, int> coin[101];
int dp[101][10001];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>T>>k;
    for (int i = 1; i <= k; i++) {
        cin>>coin[i].first>>coin[i].second;
    }

    sort(coin + 1, coin + 1 + k);
    dp[0][0] = 1;
    for (int i = 1; i <= k; i++) {
        for (int j = 0; j <= T; j++) {
            for (int l = 0; l <= coin[i].second; l++) {
                if (j - l * coin[i].first >= 0) dp[i][j] += dp[i - 1][j - l * coin[i].first];
            }
        }
    }
    cout<<dp[k][T];
    return 0;
}