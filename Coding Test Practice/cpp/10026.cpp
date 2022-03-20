#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
#define ll long long int
using namespace std;

int N;
int map[101][101];
int ans[2];
bool visited[101][101];
int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

void dfs1(int sr, int sc) {
    visited[sr][sc] = true;
    int temp = map[sr][sc];

    for (int i = 0; i < 4; i++) {
        int nr = sr + dr[i];
        int nc = sc + dc[i];
        if (nr > 0 && nr <= N && nc > 0 && nc <= N && !visited[nr][nc] && map[nr][nc] == temp) {
            dfs1(nr, nc);
        }
    }
}

void dfs2(int sr, int sc) {
    visited[sr][sc] = true;
    int temp = map[sr][sc];

    for (int i = 0; i < 4; i++) {
        int nr = sr + dr[i];
        int nc = sc + dc[i];
        if (nr > 0 && nr <= N && nc > 0 && nc <= N && !visited[nr][nc]) {
            if (temp == 1 || temp == 2) {
                if (map[nr][nc] == 1 || map[nr][nc] == 2) dfs2(nr, nc);
            }
            else if (map[nr][nc] == temp) dfs2(nr, nc);
        }
    }
}


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>N;
    for (int i = 1; i <= N; i++) {
        string s; cin>>s;
        for (int j = 0; j < N; j++) {
            switch(s[j]) {
                case 'R':
                    map[i][j + 1] = 1;
                    break;
                case 'G':
                    map[i][j + 1] = 2;
                    break;
                case 'B':
                    map[i][j + 1] = 3;
                    break;
            }
        }
    }
    memset(ans, 0, sizeof(ans));
    // 적록 색맹 아닌 경우
    memset(visited, false, sizeof(visited));
    for (int r = 1; r <= N; r++) {
        for (int c = 1; c <= N; c++) {
            if (visited[r][c]) continue;
            else {
                dfs1(r, c);
                ans[0]++;
            }
        }
    }
    // 적록 색맹인 경우
    memset(visited, false, sizeof(visited));
    for (int r = 1; r <= N; r++) {
        for (int c = 1; c <= N; c++) {
            if (visited[r][c]) continue;
            else {
                dfs2(r, c);
                ans[1]++;
            }
        }
    }    
    cout<<ans[0]<<" "<<ans[1];
    return 0;
}