#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <cstring>
using namespace std;
#define MAX 105

typedef struct p {
  int x, y;
} Point;

int n;
vector<Point> v(MAX);
int dist[MAX][MAX];
bool visited[MAX];

int getDist(Point p1, Point p2) {
  return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}

void init() {
  cin >> n;
  for (int i = 0; i < n+2; i++) cin >> v[i].x >> v[i].y;
  for (int i = 0; i < n+2; i++) {
    for (int j = 0; j < n+2; j++) {
      if (i == j) continue;
      if (j < i) {
        dist[i][j] = dist[j][i];
        continue;
      }
      dist[i][j] = getDist(v[i], v[j]);
    }
  }
  memset(visited, false, sizeof(visited));
}

bool bfs() {
  if (dist[0][n+1] <= 1000) return true;
  queue<int> q;
  q.push(0);
  while (!q.empty()) {
    int cur = q.front();
    q.pop();

    if (cur == n+1) return true;
    for (int i = 1; i < n+2; i++) {
      if (!visited[i] && dist[cur][i] <= 1000) {
        visited[i] = true;
        q.push(i);
      }
    }
  }
  return false;
}

int main() {
  ios::sync_with_stdio(0); cout.tie(0); cin.tie(0);
  int t; cin >> t;
  while(t--) {
    init();
    if (bfs()) cout << "happy\n";
    else cout <<"sad\n";
  }
  return 0;
}