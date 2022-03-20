#include <iostream>
#include <algorithm>
#define ll long long int
using namespace std;

ll N;
ll dp[1000001];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>N;
    dp[1] = 0;
    dp[2] = 1;

    for (ll i=3; i<=N; i++) {
        dp[i] = ((i-1) * (dp[i-1] + dp[i-2])) % 1000000000;
    }

    cout<<dp[N];
    return 0;
}
