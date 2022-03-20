#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>
using namespace std;

int T, click;
bool map[3][3];
bool ans[3][3];

int dr[] = {-1, 1, 0, 0, 0};
int dc[] = {0, 0, -1, 1, 0};

void click_box(int r, int c) {
    for (int i = 0; i < 5; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if (nr >= 0 && nc >= 0 && nr < 3 && nc < 3) {
            map[nr][nc] = !map[nr][nc];
        }
    }
}

bool if_end() {
    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            if (map[i][j] != ans[i][j]) return false;
        }
    }
    return true;
}


void bfs(int r, int c, int move, int count) {
    if (move == 1) click_box(r, c);

    if (if_end()) {
        click = min(click, count);
    }

    if(!(r == 2 && c == 2)) {
        if (c == 2) {
            for (int i=0; i<2; i++) {
                bfs(r+1, 0, i, count + i);
            }
        }
        else {
            for (int i=0; i<2; i++) {
                bfs(r, c+1, i, count + i);
            }
        }
    }

    if (move == 1) click_box(r, c);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>T;

    for (int i = 0; i < T; i++) {
        click = 9999;
        for (int j =0; j<3; j++) {
            string s;
            cin>>s;
            for (int k =0; k<3; k++) {
                if (s[k] == '*') {
                    ans[j][k] = true;
                }
                else {
                    ans[j][k] = false;
                }
            }
        }
        for (int j = 0; j < 2; j++) {
            bfs(0, 0, j, j);
        }
        cout<<click<<endl;
    }
    return 0;
}