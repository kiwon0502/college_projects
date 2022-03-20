#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAX = 810;
const int INF = 0x3f3f3f3f;
int N, E, v1, v2;
vector<pair<int, int>> graph[MAX];
int dist[MAX];

void dijkstra(int start) {
    memset(dist, INF, sizeof(dist));
    priority_queue<pair<int, int>> pq;
    pq.push({0, start});
    dist[start] = 0;

    while(!pq.empty()) {
        int cur_cost = pq.top().first;
        int cur = pq.top().second;
        pq.pop();

        if (cur_cost > dist[cur]) continue;
        for (int i = 0; i < graph[cur].size(); i++) {
            int next_cost = cur_cost + graph[cur][i].first;
            int next = graph[cur][i].second;

            if (dist[next] > next_cost) {
                dist[next] = next_cost;
                pq.push({dist[next], next});
            }
        }
    }
}


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> E;
    for (int i = 0; i < E; i++) {
        int u, v, w; cin >> u >> v >> w;
        graph[u].push_back({w, v});
        graph[v].push_back({w, u});
    }

    cin >> v1 >> v2;
    dijkstra(1);
    int one2v1 = dist[v1];
    int one2v2 = dist[v2];
    dijkstra(N);
    int N2v1 = dist[v1];
    int N2v2 = dist[v2];

    int choice1 = one2v1 + N2v2;
    int choice2 = one2v2 + N2v1;

    dijkstra(v1);
    int mid = dist[v2];
    
    if ((one2v1 == INF || N2v2 == INF) || (one2v2 == INF || N2v1 == INF) || (mid == INF)) cout << "-1";
    else cout << mid + min(choice1, choice2);
    return 0;
}
