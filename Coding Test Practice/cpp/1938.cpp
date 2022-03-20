#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
#define MAX 51
#define T_SIZE 3

vector<pair<int, int>> B, E;
int N, arr[MAX][MAX];
int bx, by, ex, ey;
bool b_state, e_state, visited[MAX][MAX][2];
int dx[] = {1, -1, 0, 0, 1, 1, -1, -1};
int dy[] = {0, 0, -1, 1, 1, -1, 1, -1};

void getBstate() {
    int x = 0, y = 0;
    for (int i = 0; i < T_SIZE; i++) { x += B[i].first, y += B[i].second; }
    bx = x / T_SIZE, by = y / T_SIZE;
    for (int i = 0; i < T_SIZE; i++) {
        int x_diff = bx - B[i].first, y_diff = by - B[i].second;
        if (x_diff == 0 && y_diff == -1) b_state = false;
        else if (x_diff == -1 && y_diff == 0) b_state = true;
    }
}

void getEstate() {
    int x = 0, y = 0;
    for (int i = 0; i < T_SIZE; i++) { x += E[i].first, y += E[i].second; }
    ex = x / T_SIZE, ey = y / T_SIZE;
    for (int i = 0; i < T_SIZE; i++) {
        int x_diff = ex - E[i].first, y_diff = ey - E[i].second;
        if (x_diff == 0 && y_diff == -1) e_state = false;
        else if (x_diff == -1 && y_diff == 0) e_state = true;
    }
}

bool canturn(int x, int y) {
    for (int i = 0; i < 8; i++){
        int nx = x + dx[i], ny = y + dy[i];
        if (nx < 1 || ny < 1 || nx > N || ny > N) return false;
        if (arr[nx][ny] == 1) return false;
    }
    return true;
}

int BFS() {
    queue<pair<pair<int, int>, pair<int, int>>> q;
    q.push({{bx, by}, {b_state, 0}});
    visited[bx][by][b_state] = true;

    while (!q.empty()) {
        int cur_x = q.front().first.first;
        int cur_y = q.front().first.second;
        bool cur_state = q.front().second.first;
        int mov = q.front().second.second;
        q.pop();
        if (cur_x == ex && cur_y == ey && cur_state == e_state) return mov;

        for (int i = 0; i < 4; i++) {
            int nx = cur_x + dx[i], ny = cur_y + dy[i];
            if (cur_state && (nx < 2 || ny < 1 || nx > N - 1 || ny > N)) continue;
            if (!cur_state && (nx < 1 || ny < 2 || nx > N || ny > N - 1)) continue;
            if (cur_state && (arr[nx][ny] == 1 || arr[nx - 1][ny] == 1 || arr[nx + 1][ny] == 1)) continue;
            if (!cur_state && (arr[nx][ny] == 1 || arr[nx][ny - 1] == 1 || arr[nx][ny + 1] == 1)) continue;
            if (visited[nx][ny][cur_state]) continue;
            
            visited[nx][ny][cur_state] = true;
            q.push({{nx, ny}, {cur_state, mov + 1}});
        }

        if (!visited[cur_x][cur_y][!cur_state] && canturn(cur_x, cur_y)) {
            visited[cur_x][cur_y][!cur_state] = true;
            q.push({{cur_x, cur_y}, {!cur_state, mov + 1}});
        }
    }
    return 0;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            char c; cin >> c;
            if (c == 'B') { B.push_back({i, j}); c = '0'; }
            else if (c == 'E') { E.push_back({i, j}); c = '0'; }
            arr[i][j] = c - '0';
        }
    }
    getBstate(); getEstate();
    cout << BFS();
    return 0;
}
