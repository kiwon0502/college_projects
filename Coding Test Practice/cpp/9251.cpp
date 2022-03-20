#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
#define MAX 1010

string str1, str2;
int dp[MAX][MAX];

int LCS(int x, int y) {
    if (x == str1.size() || y == str2.size()) return 0;
    int& ret = dp[x][y];
    if (ret != -1) return ret;
    return ret = max({LCS(x + 1, y), LCS(x, y + 1), (str1[x] == str2[y]) + LCS(x + 1, y + 1)});
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> str1 >> str2;
    memset(dp, -1, sizeof(dp));
    cout << LCS(0, 0);
    return 0;
}
