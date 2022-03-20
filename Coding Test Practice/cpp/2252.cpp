#include <iostream>
#include <vector>
#include <stack>
using namespace std;
#define MAX 32001

int N, M;
bool visited[MAX];
stack<int> ans;
vector<vector<int>> graph(MAX);

void dfs(int node) {
  visited[node] = true;
  for (int next : graph[node]) if (!visited[next]) dfs(next);
  ans.push(node);
}

void tps() {
  for (int i = 1; i <= N; i++) if (!visited[i]) dfs(i);
}

int main() {
  ios::sync_with_stdio(0); cout.tie(0); cin.tie(0);
  cin >> N >> M;
  while(M--) {
    int a, b; cin >> a >> b;
    graph[a].push_back(b);
  }
  tps();
  while (!ans.empty()) {
    cout << ans.top()<< " ";
    ans.pop();
  }
  return 0;
}