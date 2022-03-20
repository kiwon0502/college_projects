#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

#define MAX 1010
const int INF = 0x3f3f3f3f;
int N, M;
vector<pair<int, int>> graph[MAX];

int dijkstra(int start, int dest) {
    int dist[MAX];
    memset(dist, INF, sizeof(dist));
    priority_queue<pair<int, int>> pq;
    pq.push({0, start});
    dist[start] = 0;

    while (!pq.empty()) {
        int cost = -pq.top().first;
        int cur = pq.top().second;
        pq.pop();

        if (dist[cur] < cost) continue;
        for (int i = 0; i < graph[cur].size(); i++) {
            int next = graph[cur][i].first;
            int next_cost = graph[cur][i].second;
            if (dist[next] > dist[cur] + next_cost) {
                dist[next] = dist[cur] + next_cost;
                pq.push({-dist[next], next});
            }
        }
    }
    return dist[dest];
}


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        int u, v, w; cin >> u >> v >> w;
        graph[u].push_back({v, w});
    }
    int start, dest; cin >> start >> dest;
    cout << dijkstra(start, dest);
    return 0;
}
