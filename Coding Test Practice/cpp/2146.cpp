#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

const int MAX = 101;
int N, world[MAX][MAX];
bool visited[MAX][MAX];
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

void DFS(int x, int y, int label) {
    visited[x][y] = true;
    world[x][y] = label;

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        if (nx < 1 || ny < 1 || nx > N || ny > N) continue;
        if (!visited[nx][ny] && world[nx][ny] == 1) DFS(nx, ny, label);
    }
}

int BFS(int label) {
    queue<pair<int, int>> q;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (world[i][j] == label) {
                visited[i][j] = true;
                q.push({i, j});
            }
        }
    }

    int ret = 0;
    while (!q.empty()) {
        int curSize = q.size();
        for (int i = 0; i < curSize; i++) {
            int x = q.front().first;
            int y = q.front().second;
            q.pop();

            for (int i = 0; i < 4; i++) {
                int nx = x + dx[i], ny = y + dy[i];
                if (nx < 1 || ny < 1 || nx > N || ny > N) continue;
                if (world[nx][ny] && world[nx][ny] != label) return ret;
                else if (!world[nx][ny] && !visited[nx][ny]) {
                    visited[nx][ny] = true;
                    q.push({nx, ny});
                }
            }
        }
        ret++;
    }
    return -1;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    for (int i = 1; i <= N; i++)
    for (int j = 1; j <= N; j++)
        cin >> world[i][j];

    int idx = 2;
    for (int i = 1; i <= N; i++)
    for (int j = 1; j <= N; j++)
        if (!visited[i][j] && world[i][j] == 1) DFS(i, j, idx++);

    int ans = 6974892;
    for (int i = 2; i < idx; i++) {
        memset(visited, false, sizeof(visited));
        ans = min(ans, BFS(i));
    }
    cout << ans;
    return 0;
}
