#include <iostream>
#include <algorithm>
#include <string>
#include <queue>
using namespace std;

#define MAX 51

int R, C;
int destR, destC;
char forest[MAX][MAX];
queue<pair<int, int>> water;
queue<pair<int, int>> start;
bool visited[MAX][MAX];

int dr[] = {0, 0, -1, 1};
int dc[] = {-1, 1, 0, 0};

void BFS() {
    int cnt = 0;
    while(!start.empty()) {
        cnt++;
        int water_size = water.size();
        // 물 번짐
        while (water_size--) {
            int r = water.front().first;
            int c = water.front().second;
            water.pop();

            for (int i = 0; i < 4; i++) {
                int nr = r + dr[i];
                int nc = c + dc[i];

                if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
                else if (forest[nr][nc] == 'X' || forest[nr][nc] == 'D' || forest[nr][nc] == '*') continue;

                water.push({nr, nc});
                forest[nr][nc] = '*';
            }
        }

        int start_size = start.size();
        while (start_size--) {
            int r = start.front().first;
            int c = start.front().second;
            start.pop();

            visited[r][c] = true;
            if (r == destR && c == destC) {
                cout<<cnt - 1<<endl; return;
            }

            for (int i = 0; i < 4; i++) {
                int nr = r + dr[i];
                int nc = c + dc[i];

                if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
                else if (forest[nr][nc] == 'X' || forest[nr][nc] == '*' || visited[nr][nc]) continue;

                visited[nr][nc] = true;
                start.push({nr, nc});
            }

        }
    }
    cout<<"KAKTUS"<<endl;
    return;
}


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>R>>C;
    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            cin>>forest[r][c];
            if (forest[r][c] == 'S') start.push({r, c});
            else if (forest[r][c] == 'D') {destR = r; destC = c;}
            else if (forest[r][c] == '*') water.push({r, c});
        }
    }
    BFS();
    return 0;
}