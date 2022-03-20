#include <iostream>
#include <algorithm>
#include <vector>
#define ll long long int
using namespace std;

ll N, K;
ll arr1[1001];
ll arr2[1001];
vector<ll> ans;
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>N>>K;
    ll count = N;
    ll temp = K;
    for (ll i=1; i<=N; i++) {
        arr1[i] = i;
    }
    while (count > 0) {
        if (count < K) {
            K = K%count;
            if (K == 0) {
                K = count;
            }
        }
        ans.push_back(arr1[K]);
        for (ll i = K+1; i <= count; i++) {
            arr2[i-K] = arr1[i];
        }
        for (ll i = 1; i < K; i++) {
            arr2[count - K + i] = arr1[i];
        }
        for (ll i = 1; i < count; i++) {
            arr1[i] = arr2[i];
        }
        K = temp;
        count--;
    }
    cout<<"<";
    for (ll i = 0; i < N-1; i++) {
        cout<<ans[i]<<", ";
    }
    cout<<ans[N-1]<<">";
    return 0;
}