#include <iostream>
#include <algorithm>
#include <queue>
#include <string.h>
#define ll long long int
using namespace std;

int N, ans;
int arr[51][51];
int visit[51][51];
int dx[4] = {-1, 0, 0, 1};
int dy[4] = {0, -1, 1, 0};

void bfs() {
    queue<pair<int, int>> q;
    q.push(make_pair(1, 1));
    memset(visit, -1, sizeof(visit));
    visit[1][1] = 0;

    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx < 1 || ny < 1 || nx > N || ny > N) continue;
            if (arr[nx][ny] == 1) {
                if (visit[nx][ny] == -1 || visit[nx][ny] > visit[x][y]) {
                    visit[nx][ny] = visit[x][y];
                    q.push(make_pair(nx, ny));
                }
            }
            else {
                if (visit[nx][ny] == -1 || visit[nx][ny] > visit[x][y] + 1) {
                    visit[nx][ny] = visit[x][y] + 1;
                    q.push(make_pair(nx, ny));
                }
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>N;
    for (int i = 1; i <= N; i++) {
        string s;
        cin>>s;
        for (int j = 0; j < N; j++) {
            arr[i][j+1] = s[j] - 48;
        }
    }
    bfs();
    cout<<visit[N][N];    
    return 0;
}