#include <iostream>
using namespace std;
typedef long long ll;
const ll MAX = 101;
ll T, dp[MAX];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    dp[1] = 1, dp[2] = 1, dp[3] = 1;
    for (ll i = 4; i <= MAX; i++) {
        dp[i] = dp[i-2] + dp[i-3];
    }
    cin >> T;   
    while (T--) {
        ll n; cin >> n;
        cout << dp[n] << "\n";
    }
    return 0;
}
