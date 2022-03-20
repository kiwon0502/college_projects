#include <iostream>
using namespace std;
const int MAX = 100010;
int N, dp[MAX];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    for (int i = 1; i <= N; i++) dp[i] = i;
    for (int i = 4; i <= N; i++) {
        for (int j = 2; j <= i; j++) {
            int jj = j * j;
            if (jj > i) break;
            if (jj == N) {cout << "1"; return 0;}
            dp[i] = min(dp[i], dp[i -jj] + 1);
        }
    }
    cout << dp[N];
}
