#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
using namespace std;

string s1, s2, s3;
int dp[101][101][101];

int lcs(int x, int y, int z) {
    if (x == s1.size() || y == s2.size() || z == s3.size()) return 0;
    int &ans = dp[x][y][z];
    if (ans != -1) return ans;

    // s1의 인덱스 증가
    // s2의 인덱스 증가
    // s3의 인덱스 증가

    // s1, s2 인덱스 증가
    // s1, s3 인덱스 증가
    // s2, s3 인덱스 증가

    // s1, s2, s3 인덱스 증가
    ans = max({lcs(x + 1, y, z), lcs(x, y+1, z), lcs(x, y, z+1)});
    ans = max({ans, lcs(x + 1, y + 1, z), lcs(x + 1, y, z + 1), lcs(x, y + 1, z + 1)});
    ans = max(ans, (s1[x] == s2[y] && s1[x] == s3[z] && s2[y] == s3[z]) + lcs(x + 1, y + 1, z + 1));
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>s1>>s2>>s3;
    memset(dp, -1, sizeof(dp));
    cout<<lcs(0, 0, 0);
    return 0;
}