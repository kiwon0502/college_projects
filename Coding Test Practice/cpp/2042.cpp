#include <iostream>
#define MAX 1000001
typedef long long ll;
using namespace std;

ll N, M, K;
ll X[MAX], tree[20 * MAX];

ll init(int start, int end, int node) {
    if (start == end) return tree[node] = X[start];
    int mid = (start + end) / 2;
    return tree[node] = init(start, mid, node * 2) + init(mid + 1, end, node * 2 + 1);
}

ll sum(int start, int end, int node, int left, int right) {
    if (left > end || right < start) return 0;

    if (left <= start && end <= right) return tree[node];
    int mid = (start + end) / 2;
    return sum(start, mid, node * 2, left, right) + sum(mid + 1, end, node * 2 + 1, left, right);
}

void update(int start, int end, int node, int index, ll diff) {
    if (index < start || index > end) return;

    tree[node] += diff;
    if (start == end) return;

    int mid = (start + end) / 2;
    update(start, mid, node * 2, index, diff);
    update(mid + 1, end, node * 2 + 1, index, diff);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>N>>M>>K;
    for (ll i = 1; i <= N; i++) cin>>X[i];
    init(1, N, 1);

    for (ll i = 0; i < M + K; i++) {
        ll cmd, b, c; cin>>cmd>>b>>c;
        if (cmd == 1) {
            update(1, N, 1, b, c - X[b]);
            X[b] = c;
        }
        else cout<<sum(1, N, 1, b, c)<<"\n";
    }
    return 0;
}