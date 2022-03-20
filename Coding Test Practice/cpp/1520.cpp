#include <iostream>
#define ll long long
using namespace std;

ll M, N, ans;
ll map[501][501];
ll dp[501][501];
bool visited[501][501];
ll dx[4] = {-1, 0, 1, 0};
ll dy[4] = {0, -1, 0, 1};

ll dfs(ll r, ll c) {
    if (r == 1 && c == 1) return 1;
    if (!visited[r][c]) {
        visited[r][c] = true;

        for (ll i=0; i<4; i++) {
            ll nx = dx[i] + c;
            ll ny = dy[i] + r;

            if (0<nx && nx<=N && 0<ny && ny<=M) {
                if (map[ny][nx] > map[r][c]) {
                    dp[r][c] += dfs(ny, nx);
                }
            }
        }
    }
    return dp[r][c];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>M>>N;
    for (ll i=1; i<=M; i++) {
        for (ll j=1; j<=N; j++) {
            cin>>map[i][j];
        }
    }
    cout<<dfs(M, N);

    return 0;
}