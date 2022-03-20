#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int MAX = 1010;
int n, m, k;
vector<pair<int, int>> graph[MAX];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> m >> k;
    for (int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w;
        graph[u].push_back({w, v});
    }


    return 0;
}
