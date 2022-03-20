#include <iostream>
#include <vector>
#include <algorithm>
#define ll long long int
#define pp pair<ll, ll>
using namespace std;

ll n;
vector<pp> v;

bool cmp(pp a, pp b) {
    if (a.second == b.second) return a.first < b.first;
    return a.second < b.second;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>n;
    for (ll i = 0; i < n; i++) {
        ll start, end; cin>>start>>end;
        v.push_back({start, end});
    }
    sort(v.begin(), v.end(), cmp);
    ll now = v[0].second;
    ll cnt = 1;
    for (ll i = 1; i < n; i++) {
        if (now <= v[i].first) {
            cnt++;
            now = v[i].second;
        }
    }
    cout<<cnt<<"\n";
    return 0;
}