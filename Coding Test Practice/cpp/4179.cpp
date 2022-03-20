#include <iostream>
#include <algorithm>
#include <string>
#include <queue>
#define MAX 1001
using namespace std;

int R, C, ans;
char mirro[MAX][MAX];
queue<pair<int, int>> start;
queue<pair<int, int>> fire;
bool visited[MAX][MAX];
bool imp;

int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};

void BFS() {
    int cnt = 0;
    while(!start.empty()) {
        cnt++;
        int fire_size = fire.size();
        // 불 번짐
        while (fire_size--) {
            int x = fire.front().first;
            int y = fire.front().second;
            fire.pop();

            for (int i = 0; i < 4; i++) {
                int nx = x + dx[i];
                int ny = y + dy[i];

                if (nx < 0 || nx >= R || ny <0 || ny >= C) continue;
                else if (mirro[nx][ny] == '#' || mirro[nx][ny] == 'F') continue;

                fire.push({nx, ny});
                mirro[nx][ny] = 'F';
            }
        }

        int start_size = start.size();
        while (start_size--) {
            int x = start.front().first;
            int y = start.front().second;
            start.pop();

            visited[x][y] = true;
            if (x == 0 || x == R - 1 || y == 0 || y == C - 1) {
                ans = min(ans, cnt); return;
            }

            for (int i = 0; i < 4; i++) {
                int nx = x + dx[i];
                int ny = y + dy[i];

                if (nx < 0 || nx >= R || ny <0 || ny >= C) continue;
                else if (mirro[nx][ny] == '#' || mirro[nx][ny] == 'F' || visited[nx][ny]) continue;

                visited[nx][ny] = true;
                start.push({nx, ny});
            }
        }
    }
    imp = true; return;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    ans = 987654321;
    cin>>R>>C;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            cin>>mirro[i][j];
            if (mirro[i][j] == 'J') start.push({i, j});
            else if (mirro[i][j] == 'F') fire.push({i, j});
        }
    }

    BFS();
    if (imp) cout<<"IMPOSSIBLE";
    else cout<<ans;
    return 0;
}