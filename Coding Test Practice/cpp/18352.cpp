#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
#define MAX 300005
const int INF = 0x3f3f3f3f;
int N, M, K, X;
int dist[MAX];
vector<int> graph[MAX];

void dijkstra() {
  memset(dist, INF, sizeof(dist));
  priority_queue<pair<int, int>> pq;
  pq.push({0, X});
  dist[X] = 0;
  while(!pq.empty()) {
    int cost = -pq.top().first;
    int cur = pq.top().second;
    pq.pop();

    if (dist[cur] < cost) continue;
    for (int next : graph[cur]) {
      if (dist[next] > cost + 1) {
        dist[next] = cost + 1;
        pq.push({-dist[next], next});
      }
    }
  }

  vector<int> ans;
  for (int i = 1; i <= N; i++) {
    if(dist[i] == K) ans.push_back(i);
  }

  if (ans.size() == 0) cout << -1;
  else {
    for (int i : ans) {
      cout << i << "\n";
    }
  }
}

int main() {
  ios::sync_with_stdio(0); cout.tie(0); cin.tie(0);
  cin >> N >> M >> K >> X;
  for (int i = 0; i < M; i++) {
    int u , v; cin >> u >> v;
    graph[u].push_back(v);
  }
  dijkstra();
  return 0;
}