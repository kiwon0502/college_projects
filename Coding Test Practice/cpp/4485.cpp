#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

const int MAX = 130;
const int INF = 0x3f3f3f3f;
int N, cave[MAX][MAX], dist[MAX][MAX];
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

int dijkstra() {
    memset(dist, INF, sizeof(dist));
    dist[0][0] = cave[0][0];
    priority_queue<pair<int, pair<int, int>>> pq;
    pq.push({dist[0][0], {0, 0}});

    while (!pq.empty()) {
        int cost = -pq.top().first;
        int x = pq.top().second.first;
        int y = pq.top().second.second;
        pq.pop();

        if (dist[x][y] < cost) continue;
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
            if (dist[nx][ny] > dist[x][y] + cave[nx][ny]) {
                dist[nx][ny] = dist[x][y] + cave[nx][ny];
                pq.push({-dist[nx][ny], {nx, ny}});
            }
        }
    }
    return dist[N - 1][N - 1];
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int T = 1;
    while (1) {
        cin >> N;
        if (N == 0) break;
        for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) cin >> cave[i][j];
        cout << "Problem " << (T++) << ": " << dijkstra() << "\n";
    }
    return 0;
}
