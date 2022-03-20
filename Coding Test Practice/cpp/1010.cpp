#include <iostream>
#include <algorithm>
#define ll long long int
using namespace std;

ll T, N, M;
ll dp[31][31];

ll combination(ll n, ll r) {
    if (dp[n][r] != 0) return dp[n][r];
    if (n == r || r == 0) return 1;
    else {
        dp[n][r] = combination(n-1, r-1) + combination(n-1, r);
        return dp[n][r];
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>T;
    for (ll i=0; i<T; i++) {
        cin>>N>>M;
        cout<<combination(M, N)<<endl;
    }
    return 0;
}