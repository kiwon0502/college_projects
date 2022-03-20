#include <iostream>
#include <algorithm>
#define MAX 1000000
#define treeMAX 1000000000
typedef long long ll;
using namespace std;

ll N, M, ans;
ll tree[MAX + 1];

bool cutok(ll h) {
    ll sum = 0;
    for (int i = 0; i < N; i++) {
        if (tree[i] > h) {
            sum += tree[i] - h;
        }
        if (sum >= M) return true;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>N>>M;
    for (ll i = 0; i < N; i++) cin>>tree[i];

    ll left = 0, right = treeMAX, mid;
    while (left <= right) {
        mid = (left + right)/2;
        if (cutok(mid)) {
            if (ans < mid) ans = mid;
            left = mid + 1;
        }
        else right = mid - 1;
    }
    cout<<ans;
    return 0;
}