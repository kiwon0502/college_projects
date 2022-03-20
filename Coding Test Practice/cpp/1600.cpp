#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

int K, W, H;
int ans;
int world[201][201];
bool check[201][201][31];

int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};
int hdx[8] = {-1, -2, -2, -1, 1, 2, 2, 1};
int hdy[8] = {-2, -1, 1, 2, 2, 1, -1, -2};

int main() {
    cin>>K>>W>>H;
    for (int i=1; i<=H; i++) {
        for (int j=1; j<=W; j++) {
            cin>>world[i][j];
        }
    }

    queue<pair<pair<int, int>, pair<int, int>>> Q;
    Q.push(make_pair(make_pair(1,1), make_pair(0, 0)));
    check[1][1][0] = true;

    while(!Q.empty()) {
        int x = Q.front().first.first;
        int y = Q.front().first.second;
        int move = Q.front().second.first;
        int use = Q.front().second.second;

        Q.pop();

        if (x == H && y == W) {
            cout<<move;
            return 0;
        }
        else if (use < K) {
            for (int i=0; i<8; i++) {
                int next_x = x + hdx[i];
                int next_y = y + hdy[i];
                if (next_x > 0 && next_y > 0 && next_x <= H && next_y <= W) {
                    if (world[next_x][next_y] == 0 && !check[next_x][next_y][use + 1]) {
                        check[next_x][next_y][use + 1] = true;
                        Q.push(make_pair(make_pair(next_x, next_y), make_pair(move + 1, use + 1)));
                    }
                }
            }
        }

        for (int i=0; i<4; i++) {
            int next_x = x + dx[i];
            int next_y = y + dy[i];
            if (next_x > 0 && next_y > 0 && next_x <= H && next_y <= W) {
                if (world[next_x][next_y] == 0 && !check[next_x][next_y][use]) {
                    check[next_x][next_y][use] = true;
                    Q.push(make_pair(make_pair(next_x, next_y), make_pair(move + 1, use)));
                }
            }
        }
    }
    cout<<"-1";
    return 0;
}