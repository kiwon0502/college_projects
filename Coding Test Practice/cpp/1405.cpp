#include <iostream>
#include <cstdio>
using namespace std;

int n;
double p[4];
bool visited[30][30];
int dr[] = {0, 0, 1, -1};
int dc[] = {1, -1, 0, 0};       // 동서남북

double dfs(int r, int c, int cnt) {
    if (cnt == 0) return 1.0;
    double ret = 0.0;
    visited[r][c] = true;

    for (int i = 0; i < 4; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if (visited[nr][nc]) continue;
        ret += dfs(nr, nc, cnt - 1) * p[i];
    }
    visited[r][c] = false;
    return ret;
}

int main() {
    cin>>n;
    for (int i = 0; i < 4; i++) {cin>>p[i]; p[i]/=100.0;}
    printf("%.9lf\n", dfs(15, 15, n));
    return 0;
}