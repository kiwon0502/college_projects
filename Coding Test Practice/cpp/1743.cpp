#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
#define MAX 105

int N, M, K, ans;
int arr[MAX][MAX];
bool visited[MAX][MAX];
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

int DFS(int x, int y) {
    visited[x][y] = true;
    int ret = 1;
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        if (nx < 1 || ny < 1 || nx > N || ny > M) continue;
        if (!visited[nx][ny] && arr[nx][ny] == 1) ret += DFS(nx, ny);
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M >> K;
    for (int i = 0; i < K; i++) {
        int r, c; cin >> r >> c;
        arr[r][c] = 1;
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            if (arr[i][j] == 1 && !visited[i][j]) ans = max(ans, DFS(i, j));
        }
    }

    cout << ans;    
    return 0;
}
