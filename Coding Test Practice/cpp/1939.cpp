#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <queue>
#define MAX 10010
using namespace std;

int N, M, start, dest, ans;
bool visited[MAX];
vector<pair<int, int>> graph[MAX];


// void dfs(int x, int weight) {
//     visited[x] = true;
//     if (x == dest) {
//         ans = max(ans, weight);
//         return;
//     }

//     for (int i = 1; i <= N; i++) {
//         if (graph[x][i] != 0 && !visited[i]) {
//             dfs(i, min(weight, graph[x][i]));
//         }
//     }
// }

bool bfs(int cost) {
    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int x = q.front();
        q.pop();

        if (x == dest) return true;

        for (int i = 0; i < graph[x].size(); i++) {
            int nx = graph[x][i].first;
            int nc = graph[x][i].second;

            if (!visited[nx] && cost <= nc) {
                q.push(nx);
                visited[nx] = true;
            }
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M;
    int low = 0, high = 0;
    for (int i = 0; i < M; i++) {
        int a, b, c; cin >> a >> b >> c;
        graph[a].push_back({b, c});
        graph[b].push_back({a, c});
        high = max(high, c);
    }
    cin >> start >> dest;

    int mid;
    while (low <= high) {
        mid = (low + high) / 2;
        memset(visited, false, sizeof(visited));

        if (bfs(mid)) low = mid + 1;
        else high = mid - 1;
    }

    cout << high;
    return 0;
}