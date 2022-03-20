#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;

int N, M, ans;
int map[1001][1001];
bool visited[1001][1001];
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};
vector<int> groupSize;

void bfs() {
    queue<pair<int, int>> q;
    memset(visited, false, sizeof(visited));

    q.push({1, 1});
    visited[1][1] = true;

    while(!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (!visited[nx][ny]) {
                q.push({nx, ny});
                visited[nx][ny] = true;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>N>>M;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            cin>>map[i][j];
        }
    }

    return 0;
}