#include <iostream>
#include <string.h>
using namespace std;

int dp[12];
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int T; cin>>T;
    while (T-- > 0) {
        int n; cin>>n;
        memset(dp, 0, sizeof(dp));
        dp[1] = 1;
        dp[2] = 2;
        dp[3] = 4;
        for (int i = 4; i <= n; i++) {
            dp[i] = dp[i - 1] + dp[i - 2] + dp[i - 3];
        }
        cout<<dp[n]<<"\n";
    }
    return 0;
}