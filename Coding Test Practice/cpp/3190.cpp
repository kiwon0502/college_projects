#include <iostream>
#include <vector>
#include <queue>

using namespace std;
#define MAX 105

int board[MAX][MAX];
bool is_snake[MAX][MAX];

int dr[] = {0, 1,  0, -1};
int dc[] = {1, 0, -1,  0};
char change[10001];

int N, K, L;
int time, dir;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> K;
    for (int i = 0; i < K; i++) {
        int r, c; cin >> r >> c;
        board[r][c] = 1;
    }
    cin >> L;

    while (L--) {
        int x; char c; cin >> x >> c;
        change[x] = c;
    }

    queue<pair<int, int>> snake;
    snake.push({1, 1});
    is_snake[1][1] = true;

    while (1) {
        time++;
        int nr = snake.back().first + dr[dir];
        int nc = snake.back().second + dc[dir];

        if (nr < 1 || nc < 1 || nr > N || nc > N) break;
        snake.push({nr, nc});

        if (change[time] == 'D') {
            dir = (dir + 5)%4;
        }
        else if (change[time] == 'L') {
            dir = (dir + 3)%4;
        }

        if (board[nr][nc] == 1) {
            board[nr][nc] = 0;  
        }
        else {
            if (is_snake[nr][nc]) break;
            is_snake[snake.front().first][snake.front().second] = false;
            snake.pop();
        }

        if (is_snake[nr][nc]) break;
        else is_snake[nr][nc] = true;
    }
    cout << time;
    return 0;
}
