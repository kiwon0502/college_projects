#include <iostream>
#include <deque>
typedef long long ll;
using namespace std;
ll N, L, A;
deque<pair<ll, ll>> dq;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>N>>L;
    for (ll i = 1; i <= N; i++) {
        cin>>A;
        while (!dq.empty()) {
            pair<ll, ll> t = dq.back();
            if (t.second >= A) dq.pop_back();
            else break;
        }
        dq.push_back({i, A});
        pair<ll, ll> t = dq.front();
        if (t.first == i - L) dq.pop_front();
        t = dq.front();
        cout<<t.second<<" ";
    }
    return 0;
}