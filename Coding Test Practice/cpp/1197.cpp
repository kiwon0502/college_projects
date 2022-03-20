#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX = 10010;
int V, E, ans, parent[MAX];
vector<pair<int, pair<int, int>>> edge;

void union_find_init() {
    for (int i = 1; i <= V; i++) parent[i] = i;
}

int Find(int x) {
    if (parent[x] == x) return x;
    else return parent[x] = Find(parent[x]);
}

void Union(int x, int y) {
    x = Find(x);
    y = Find(y);
    if (x != y) parent[y] = x;
}

bool ifSameparent(int x, int y) {
    x = Find(x);
    y = Find(y);

    if (x == y) return true;
    return false;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> V >> E;
    for (int i = 0; i < E; i++) {
        int u, v, w; cin >> u >> v >> w;
        edge.push_back({w, {u, v}});
    }
    sort(edge.begin(), edge.end());
    union_find_init();
    for (int i = 0; i < E; i++) {
        int cost = edge[i].first;
        int u = edge[i].second.first;
        int v = edge[i].second.second;

        if (!ifSameparent(u, v)) {
            Union(u, v);
            ans += cost;
        }
    }

    cout << ans;
    return 0;
}
