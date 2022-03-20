#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;
#define MAX 101

int N, M, forces[2];
int krafton[MAX][MAX];
bool visited[MAX][MAX];
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

int DFS(int ally, int x, int y) {
    visited[x][y] = true;
    int ret = 1;
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        if (nx < 1 || ny < 1 || nx > M || ny > N || visited[nx][ny] || krafton[nx][ny] != ally) continue;
        ret += DFS(ally, nx, ny);
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M;
    for (int i = 1; i <= M; i++) {
        for (int j = 1; j <= N; j++) {
            char c; cin >> c;
            if (c == 'B') krafton[i][j] = 1;
        }
    }

    for (int i = 1; i <= M; i++)
    for (int j = 1; j <= N; j++)
        if (!visited[i][j]) forces[krafton[i][j]] += pow(DFS(krafton[i][j], i, j), 2);
    
    cout << forces[0] << " " << forces[1];
    return 0;
}
