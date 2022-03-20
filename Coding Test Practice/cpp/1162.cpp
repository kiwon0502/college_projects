#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <climits>
using namespace std;
#define MAX 10005
#define INF LLONG_MAX
using ll = long long;

int N, M, K;
ll dist[MAX][21];   // 1번 노드에서 i번째 노드까지 j번 포장했을 때 거리
vector<pair<int, int>> graph[MAX];

void dijkstra() {
  for (int i = 1; i <= N; i++) {
    for (int j = 0; j <= K; j++) {
      dist[i][j] = INF;
    }
  }

  priority_queue<pair<ll, pair<int, int>>> pq;
  pq.push({0, {1, 0}});
  dist[1][0] = 0;

  while (!pq.empty()) {
    int cur = pq.top().second.first;
    int cnt = pq.top().second.second;
    ll cost = -pq.top().first;
    pq.pop();

    if (dist[cur][cnt] < cost) continue;

    for (auto node : graph[cur]) {
      int next = node.second;
      ll next_cost = cost + node.first;

      // 포장하지 않는 경우
      if (dist[next][cnt] > next_cost) {
        dist[next][cnt] = next_cost;
        pq.push({-next_cost, {next, cnt}});
      }

      // 포장할 경우
      if (cnt < K && dist[next][cnt+1] > cost) {
        dist[next][cnt+1] = cost;
        pq.push({-cost, {next, cnt+1}});
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(0); cout.tie(0); cin.tie(0);
  cin >> N >> M >> K;
  for (int i = 0; i < M; i++) {
    int u, v, w; cin >> u >> v >> w;
    graph[u].push_back({w, v});
    graph[v].push_back({w, u});
  }
  dijkstra();

  ll ans = dist[N][0];
  for (int i = 1; i <= K; i++) ans = min(ans, dist[N][i]);
  cout << ans;
  return 0;
}