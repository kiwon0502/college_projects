#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
#define MAX 1010
using namespace std;

const int INF = 0x3f3f3f3f;
int V, E, X, dist[MAX], res[MAX];
vector<pair<int, int>> dgraph[MAX];

void solution1() {
    int graph[MAX][MAX];
    cin >> V >> E >> X;

    for (int i = 0; i < MAX; i++) for (int j = 0; j < MAX; j++) if (i != j) graph[i][j] = INF;
    while (E--) {
        int u, v, w; cin >> u >> v >> w;
        graph[u][v] = w;
    }
    for (int i = 0; i <= V; i++) for (int j = 0; j <= V; j++) for (int k = 0; k <= V; k++)
        graph[j][k] = min(graph[j][k], graph[j][i] + graph[i][k]);
    int ans = 0;
    for (int i = 1; i <= V; i++) {
        ans = max(ans, graph[i][X] + graph[X][i]);
    }
    cout << ans;
}

void dijkstra(int start) {
    memset(dist, INF, sizeof(dist));
    priority_queue<pair<int, int>> pq;
    pq.push({0, start});
    dist[start] = 0;

    while (!pq.empty()) {
        int cur_cost = -pq.top().first;
        int cur = pq.top().second;
        pq.pop();

        if (cur_cost > dist[cur]) continue;
        for (int i = 0; i < dgraph[cur].size(); i++) {
            int next_cost = dgraph[cur][i].first;
            int next = dgraph[cur][i].second;

            if (dist[next] > dist[cur] + next_cost) {
                dist[next] = dist[cur] + next_cost;
                pq.push({-dist[next], next});
            }
        }
    }
}

void solution2() {
    cin >> V >> E >> X;
    while (E--) {
        int u, v, w; cin >> u >> v >> w;
        dgraph[u].push_back({w, v});
    }

    for (int i = 1; i <= V; i++) {
        dijkstra(i);
        res[i] = dist[X];
    }
    memset(dist, INF, sizeof(dist));
    dijkstra(X);
    for (int i = 1; i <= V; i++) res[i] += dist[i];
    sort(res + 1, res + V + 1);
    cout << res[V];
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    solution2();
    return 0;
}