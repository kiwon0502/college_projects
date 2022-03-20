#include <iostream>
#include <algorithm>
using namespace std;

int n, ans;
int zoo[501][501];
int dp[501][501];
int dr[] = {1, -1, 0, 0};
int dc[] = {0, 0, 1, -1};

int dfs(int r, int c) {
    if (dp[r][c] != 0) return dp[r][c];
    dp[r][c] = 1;

    for (int i = 0; i < 4; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if (nr > 0 && nr <= n && nc > 0 && nc <= n) {
            if (zoo[nr][nc] > zoo[r][c]) {
                dp[r][c] = max(dp[r][c], dfs(nr, nc) + 1);
            }
        }
    }
    return dp[r][c];
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin>>zoo[i][j];
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            ans = max(ans, dfs(i, j));
        }
    }
    cout<<ans;
    return 0;
}