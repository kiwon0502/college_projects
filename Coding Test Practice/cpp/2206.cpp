#include <iostream>
#include <queue>
using namespace std;
#define MAX 1001

int N, M, map[MAX][MAX];
bool visited[MAX][MAX][2];
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};


int BFS() {
    queue<pair<pair<int, int>, pair<int, bool>>> q;
    q.push({{1, 1}, {1, false}});
    visited[1][1][0] = true;

    while (!q.empty()) {
        int x = q.front().first.first;
        int y = q.front().first.second;
        int dist = q.front().second.first;
        bool wall_break = q.front().second.second;
        q.pop();

        if (x == N && y == M) return dist;
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx < 1 || ny < 1 || nx > N || ny > M) continue;

            if (!wall_break && map[nx][ny] == 1) {
                if (visited[nx][ny][wall_break]) continue;
                visited[nx][ny][1] = true;
                q.push({{nx, ny}, {dist + 1, true}});
            } 

            if (map[nx][ny] == 0) {
                if (visited[nx][ny][wall_break]) continue;
                visited[nx][ny][wall_break] = true;
                q.push({{nx, ny}, {dist + 1, wall_break}});
            }
        }
    }
    return -1;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            char c; cin >> c;
            map[i][j] = c - '0';
        }
    }
    cout << BFS();
    return 0;
}
