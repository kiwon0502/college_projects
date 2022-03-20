#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#define MAX 300005
typedef long long ll;
using namespace std;

ll N, K, ans;
pair<ll, ll> jewel[MAX];
ll bag[MAX];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>> N >> K;
    for (ll i = 1; i <= N; i++) cin>> jewel[i].first >> jewel[i].second;
    for (ll i = 1; i <= K; i++) cin>> bag[i];
    sort(jewel + 1, jewel + N + 1);
    sort(bag + 1, bag + K + 1);

    ll posJ = 1;
    priority_queue<ll> pq;
    for (ll i = 1; i <= K; i++) {
        ll curbag = bag[i];
        while (posJ <= N && jewel[posJ].first <= curbag) {
            pq.push(jewel[posJ].second);
            posJ++;
        }

        if (!pq.empty()) {
            ans += pq.top(); pq.pop();
        }
    }
    cout<<ans;
    return 0;
}