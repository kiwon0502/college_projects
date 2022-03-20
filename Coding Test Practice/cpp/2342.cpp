#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;
#define MAX 100005

int N, arr[MAX];
int dp[5][5][MAX];

int check(int from, int to) {
    if (from == 0) return 2;
    if (from == to) return 1;
    if (abs(from - to) == 2) return 4;
    return 3;
}

int solve(int y, int x, int target) {
    if (target == N) return 0;
    if (dp[y][x][target] != -1) return dp[y][x][target];

    int left = solve(arr[target], x, target + 1) + check(y, arr[target]);
    int right = solve(y, arr[target], target + 1) + check(x, arr[target]);
    return dp[y][x][target] = min(left, right);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    for (int i = 0; i < MAX; i++) {
        cin >> arr[i];
        if (arr[i] == 0) {N = i; break;}
    }
    memset(dp, -1, sizeof(dp));
    cout << solve(0, 0, 0);
    return 0;
}
