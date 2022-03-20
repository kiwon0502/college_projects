#include <iostream>
#include <stack>
#include <cstring>
#define ll long long int
using namespace std;

ll N;
ll ans[1000001];
stack<pair<ll, ll>> s;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    memset(ans, -1, sizeof(ans));
    cin>>N;
    for (ll i = 1; i <= N; i++) {
        ll cur; cin>>cur;
        if (s.empty()) s.push({cur, i});
        else {
            while (cur > s.top().first) {
                ans[s.top().second] = cur;
                s.pop();
                if (s.empty()) break;
            }
            s.push({cur, i});
        }
    }
    for (ll i = 1; i <= N; i++) {
        cout<<ans[i]<<" ";
    }
    return 0;
}