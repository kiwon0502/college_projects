#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

const int MAX = 11;
int N, M;
char board[MAX][MAX];
bool visited[MAX][MAX][MAX][MAX];

int Rx, Ry, Bx, By;
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

int BFS() {
    queue<pair<pair<int, int>, pair<int, int>>> q;
    q.push({{Rx, Ry}, {Bx, By}});
    visited[Rx][Ry][Bx][By] = true;
    int ret = 0;

    while (!q.empty()) {
        int size = q.size();
        while (size--) {
            int red_x = q.front().first.first;
            int red_y = q.front().first.second;
            int blue_x = q.front().second.first;
            int blue_y = q.front().second.second;
            q.pop();

            if (board[red_x][red_y] == 'O' && board[red_x][red_y] != board[blue_x][blue_y]) return ret;
            for (int i = 0; i < 4; i++) {
                int red_nx = red_x, red_ny = red_y, blue_nx = blue_x, blue_ny = blue_y;
                while (board[red_nx + dx[i]][red_ny + dy[i]] != '#' && board[red_nx][red_ny] != 'O') {
                    red_nx += dx[i];
                    red_ny += dy[i];
                }

                while (board[blue_nx + dx[i]][blue_ny + dy[i]] != '#' && board[blue_nx][blue_ny] != 'O') {
                    blue_nx += dx[i];
                    blue_ny += dy[i];
                }

                if (red_nx == blue_nx && red_ny == blue_ny) {
                    if (board[red_nx][red_ny] == 'O') continue;
                    if (abs(red_nx - red_x) + abs(red_ny - red_y) < abs(blue_nx - blue_x) + abs(blue_ny - blue_y)) {
                        blue_nx -= dx[i];
                        blue_ny -= dy[i];
                    }
                    else {
                        red_nx -= dx[i];
                        red_ny -= dy[i];
                    }
                }

                if (visited[red_nx][red_ny][blue_nx][blue_ny]) continue;
                q.push({{red_nx, red_ny}, {blue_nx, blue_ny}});
                visited[red_nx][red_ny][blue_nx][blue_ny] = true;
            }
        }

        if (ret == 10) return -1;
        ret++;
    }
    return -1;
}


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            cin >> board[i][j];
            if (board[i][j] == 'R') Rx = i, Ry = j;
            else if (board[i][j] == 'B') Bx = i, By = j;
        }
    }
    cout << BFS();    
    return 0;
}
