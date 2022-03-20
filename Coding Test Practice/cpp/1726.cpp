#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

int M, N, ans;
int sr, sc, sdir, dr, dc, ddir;
// (행, 열, 방향)
queue<pair<pair<int, int>, int>> q;

int factory[101][101];
int dis[101][101][5];
int d_r[] = {0, 0, 1, -1};
int d_c[] = {1, -1, 0, 0};

int bfs() {
    dis[sr][sc][sdir] = 0;

    while (!q.empty()) {
        int r = q.front().first.first;
        int c = q.front().first.second;
        int dir = q.front().second;

        q.pop();

        if (r == dr && c == dc && dir == ddir) return dis[r][c][dir];

        // 3까지 이동 가능
        for (int i = 1; i <= 3; i++) {
            int nr = r + d_r[dir - 1] * i;
            int nc = c + d_c[dir - 1] * i;

            if (dis[nr][nc][dir] != -1) continue;
            if (nr > 0 && nc > 0 && nr <= M && nc <= N && factory[nr][nc] == 0) {
                dis[nr][nc][dir] = dis[r][c][dir] + 1;
				q.push({{nr, nc}, dir});
            }
            else break;
        }

        // 방향 전환
		if (dir == 1 || dir == 2) {
			int ndir = 3;
			if (dis[r][c][ndir] == -1) {
				dis[r][c][ndir] = dis[r][c][dir] + 1;
				q.push({{r, c}, ndir});
			}

			ndir = 4;
			if (dis[r][c][ndir] == -1) {
				dis[r][c][ndir] = dis[r][c][dir] + 1;
				q.push({{r, c}, ndir});
			}
		}
		if (dir == 3 || dir == 4) {
			int ndir = 2;
			if (dis[r][c][ndir] == -1) {
				dis[r][c][ndir] = dis[r][c][dir] + 1;
				q.push({{r, c}, ndir});
			}

			ndir = 1;
			if (dis[r][c][ndir] == -1) {
				dis[r][c][ndir] = dis[r][c][dir] + 1;
				q.push({{r, c}, ndir});
			}
		}
    }
    return -1;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    memset(dis, -1, sizeof(dis));

    cin>>M>>N;
    for (int r = 1; r <= M; r++)
        for (int c = 1; c <= N; c++)
            cin>>factory[r][c];
    cin>>sr>>sc>>sdir>>dr>>dc>>ddir;
    
    q.push({{sr, sc}, sdir});
    cout<<bfs();
    return 0;
}