#include <iostream>
#include <cstring>
using namespace std;

const int MAX = 55;
int w, h, ans, world[MAX][MAX];
bool visited[MAX][MAX];
int dx[] = {1, -1, 0, 0, 1, 1, -1, -1};
int dy[] = {0, 0, 1, -1, 1, -1, 1, -1};

void dfs(int x, int y, int land_num) {
    visited[x][y] = true;
    for (int i = 0; i < 8; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx < 0 || ny < 0 || nx > h || ny > w) continue;
        if (!visited[nx][ny] && world[nx][ny] != 0) dfs(nx, ny, land_num);
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    while(1) {
        memset(visited, false, sizeof(visited));
        ans = 0;
        cin >> w >> h;
        if (!w && !h) break;
        for (int i = 1; i <= h; i++)
        for (int j = 1; j <= w; j++)
            cin >> world[i][j];
        
        for (int i = 1; i <= h; i++)
        for (int j = 1; j <= w; j++)
            if (!visited[i][j] && world[i][j] != 0) dfs(i, j, ans++);
        
        cout << ans << "\n";
    }
    return 0;
}
