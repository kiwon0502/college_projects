#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
#define MAX 100005

int V;
int maxDist, curNode;
vector<pair<int, int>> graph[MAX];
bool visited[MAX];

void dfs(int node, int dist) {
  if (visited[node]) return;
  visited[node] = true;

  if (maxDist < dist) {
    maxDist = dist;
    curNode = node;
  }

  for (int i = 0; i < graph[node].size(); i++) {
    int nextNode = graph[node][i].first;
    int nextDist = graph[node][i].second;
    dfs(nextNode, nextDist + dist);
  }
}

int main() {
  ios::sync_with_stdio(0); cout.tie(0); cin.tie(0);
  cin >> V;
  for (int i = 0; i < V; i++) {
    int from, to, d; cin >> from;
    while (1) {
      cin >> to;
      if (to == -1) break;
      cin >> d;
      graph[from].push_back({to, d});
    }
  }
  dfs(1, 0);
  memset(visited, false, sizeof(visited));
  dfs(curNode, 0);
  cout << maxDist;
  return 0;
}