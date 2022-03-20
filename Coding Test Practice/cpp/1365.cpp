#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;

ll N, ans;
ll arr[100000];
ll dp[100000];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>N;
    for (ll i=0; i<N; i++) {
        cin>>arr[i];
    }

    dp[0] = arr[0];
    ll idx = 1;
    for (ll i=1; i<N; i++) {
        if (arr[i-1] <= arr[i]) {
            
        }
    }


    return 0;
}