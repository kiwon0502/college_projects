#include <iostream>
#define MAX 1000010
typedef long long ll;
using namespace std;

int n, m;
int parent[MAX];

int Find(int x) {
    if (x == parent[x]) return x;
    return parent[x] = Find(parent[x]);
}

void Union(int x, int y) {
    x = Find(x);
    y = Find(y);

    if (x != y) {
        if (x < y) parent[y] = x;
        else parent[x] = y;
    }
}

bool isSameParent(int x, int y) {
    x = Find(x);
    y = Find(y);

    if (x == y) return true;
    return false;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    for (int i = 0; i <= n; i++) parent[i] = i;
    while (m--) {
        int cmd, a, b; cin >> cmd >> a >> b;
        if (cmd == 0) Union(a, b);
        else {
            if (isSameParent(a, b)) cout << "yes\n";
            else cout << "no\n";
        }
    }
    return 0;
}