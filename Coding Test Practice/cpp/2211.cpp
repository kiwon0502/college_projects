#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
#define MAX 1000 + 1
const int INF = 0x3f3f3f3f;

int N, M;
vector<pair<int, int>> graph[MAX];
int dist[MAX], trace[MAX];
bool check[MAX];
vector<pair<int, int>> ans;

void dijkstra(int start) {
    memset(dist, INF, sizeof(dist));
    priority_queue<pair<int, int>> pq;
    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int cost = -pq.top().first;
        int here = pq.top().second;
        pq.pop();

        if (dist[here] < cost) continue;
        for (int i = 0; i < graph[here].size(); i++) {
            int d = graph[here][i].first;
            int next = graph[here][i].second;
            if (dist[next] > cost + d) {
                dist[next] = cost + d;
                pq.push({-dist[next], next});
                trace[next] = here;
            }
        }
    }
}

void backtrack(int cur) {
    while (!check[cur]) {
        check[cur] = true;
        int next = trace[cur];
        if (cur == 1) break;
        
        ans.push_back({next, cur});
        cur = next;
    }
}

void solve() {
    int cur = N;
    while (cur) {
        if (!check[cur]) backtrack(cur);
        cur--;
    }
    cout << ans.size() << "\n";
    for (int i = 0; i < ans.size(); i++) cout << ans[i].first << " " << ans[i].second << "\n";
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        int u, v, w; cin >> u >> v >> w;
        graph[u].push_back({w, v});
        graph[v].push_back({w, u});
    }
    dijkstra(1);
    solve();
    return 0;
}
