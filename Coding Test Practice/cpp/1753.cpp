#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#define MAX 20010
using namespace std;

const int INF = 0x3f3f3f3f;
int V, E, start;
int dist[MAX];
vector<pair<int, int>> dgraph[MAX];         // {가중치, 도착 노드}

void dijkstra(int start) {
    memset(dist, 0x3f, sizeof(dist));
    priority_queue<pair<int, int>> pq;

    pq.push({0, start});
    dist[start] = 0;

    while (!pq.empty()) {
        int cost = -pq.top().first;
        int cur = pq.top().second;
        pq.pop();

        for (int i = 0; i < dgraph[cur].size(); i++) {
            int next_cost = dgraph[cur][i].first;
            int next = dgraph[cur][i].second;

            if (dist[next] > dist[cur] + next_cost) {
                dist[next] = dist[cur] + next_cost;
                pq.push({-dist[next], next});
            }

        }
    }
    for (int i = 1; i <= V; i++) {
        if (dist[i] != INF) cout << dist[i] << "\n";
        else cout << "INF\n";
    }
}


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> V >> E >> start;
    for (int i = 0; i < E; i++) {
        int u, v, w; cin >> u >> v >> w;
        dgraph[u].push_back({w, v});
    }
    dijkstra(start);
    return 0;
}