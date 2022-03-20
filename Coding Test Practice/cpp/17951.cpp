#include <iostream>
#include <algorithm>
#include <vector>
#define ll long long int
using namespace std;

ll N, K;
vector<ll> o;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>N>>K;
    ll x;
    for (ll i = 0; i < N; i++) {
        cin>>x;
        o.push_back(x);
    }
    sort(o.begin(), o.end());

    return 0;
}