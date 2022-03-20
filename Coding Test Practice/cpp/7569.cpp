#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

#define MAX 102
int M, N, H, day = 0;
int tomato[MAX][MAX][MAX];
int dist[MAX][MAX][MAX];

int dx[] = {1, -1, 0, 0, 0, 0};
int dy[] = {0, 0, 1, -1, 0, 0};
int dz[] = {0, 0, 0, 0, 1, -1};

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> M >> N >> H;

    queue<pair<pair<int, int>, int>> q;
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < M; k++) {
                cin >> tomato[i][j][k];
                if (tomato[i][j][k] == 1) q.push({{i, j}, k});
                if (tomato[i][j][k] == 0) dist[i][j][k] = -1;
            }
        }
    }

    while (!q.empty()) {
        pair<pair<int, int>, int> cur = q.front();
        q.pop();
        for (int i = 0; i < 6; i++) {
            int nz = cur.first.first + dz[i];
            int nx = cur.first.second + dx[i];
            int ny = cur.second + dy[i];

            if (nx < 0 || nx >= N || ny < 0 || ny >= M || nz < 0 || nz >= H) continue;
            if (dist[nz][nx][ny] >= 0) continue;
            dist[nz][nx][ny] = dist[cur.first.first][cur.first.second][cur.second] + 1;
            q.push({{nz, nx}, ny});
        }
    }

    for (int i = 0; i < H; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < M; k++) {
                if (dist[i][j][k] == -1) {
                    cout << -1;
                    return 0;
                }
                day = max(day, dist[i][j][k]);
            }
        }
    }
    cout << day;
    return 0;
}
