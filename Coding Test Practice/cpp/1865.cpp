#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
#define MAX 505
const int INF = 0x3f3f3f3f;
vector<pair<int, int>> graph[MAX];
int dist[MAX];

int main() {
  ios::sync_with_stdio(0); cout.tie(0); cin.tie(0);
  int TC; cin >> TC;
  while (TC--) {
    memset(dist, INF, sizeof(dist));
    int N, M, W, s, e, t; cin >> N >> M >> W;
    for (int i = 1; i <= N; i++) graph[i].clear();
    for (int i = 0; i < M; i++) {
      cin >> s >> e >> t;
      graph[s].push_back({e, t});
      graph[e].push_back({s, t});
    }
    for (int i = 0; i < W; i++) {
      cin >> s >> e >> t;
      graph[s].push_back({e, -t});
    }

    dist[1] = 0;
    bool cycle = false;

    for (int k = 1; k <= N; k++) {
      for (int i = 1; i <= N; i++) {
        for (auto it : graph[i]) {
          int next = it.first;
          int cost = it.second;
          if (dist[next] > dist[i] + cost) {
            dist[next] = dist[i] + cost;
            if (k == N) cycle = true;
          }
        }
      }
    }

    if (cycle) cout << "YES\n";
    else cout << "NO\n";
  }
  return 0;
}