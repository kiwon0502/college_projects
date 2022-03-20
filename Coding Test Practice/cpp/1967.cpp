#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
#define MAX 10001

int n, ans, end_point;
bool visited[MAX];
vector<pair<int, int>> tree[MAX];

void DFS(int node, int length) {
    if (visited[node]) return;
    visited[node] = true;
    
    if (ans < length) {
        ans = length;
        end_point = node;
    }
    for (int i = 0; i < tree[node].size(); i++) DFS(tree[node][i].first, length + tree[node][i].second);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n;
    for (int i = 1; i < n; i++) {
        int parent, child, weight; cin >> parent >> child >> weight;
        tree[parent].push_back({child, weight});
        tree[child].push_back({parent, weight});
    }
    DFS(1, 0);
    ans = 0;
    memset(visited, false, sizeof(visited));
    DFS(end_point, 0);
    cout << ans;
    return 0;
}
