#include <iostream>
#include <vector>
using namespace std;
int N, grid[105][105];
int dx[] = {1, 0, -1, 0};
int dy[] = {0, -1, 0, 1};

typedef struct p {
  int x, y;
} Point;

Point rotate(Point p, Point base) {
  Point ret;
  ret.x = base.x - (p.y - base.y);
  ret.y = (p.x - base.x) + base.y;
  return ret;
}

void dragonCurve(int x, int y, int d, int g) {
  vector<Point> curve;
  Point p;
  p.x = x;
  p.y = y;
  curve.push_back(p); // 시작점
  p.x += dx[d];
  p.y += dy[d];
  curve.push_back(p); // 0세대 드래곤 커브

  for (int i = 1; i <= g; i++) {
    Point end = curve.back();
    for (int j = curve.size()-2; j >= 0; j--) {
      curve.push_back(rotate(curve[j], end));
    }
  }
  for (Point p : curve) {
    grid[p.x][p.y] = 1;
  }
}

int solve() {
  int ret = 0;
  for (int i = 0; i < 100; i++) {
    for (int j = 0; j < 100; j++) {
      if (grid[i][j] == 1 && grid[i+1][j] == 1 && grid[i][j+1] == 1 && grid[i+1][j+1] == 1) ret++;
    }
  }
  return ret;
}

int main() {
  ios::sync_with_stdio(0); cout.tie(0); cin.tie(0);
  cin >> N;
  for (int i = 1; i <= N; i++) {
    int x, y, d, g; cin >> x >> y >> d >> g;
    dragonCurve(x, y, d, g);
  }
  cout << solve();
  return 0;
}