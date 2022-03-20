#include <iostream>
#define MAX 105
typedef long long ll;
using namespace std;

int N, M, K;
ll dp[MAX][MAX];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M >> K;

    for (int i = 1; i <= 100; i++)
        dp[i][0] = 1, dp[0][i] = 1;
    
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            if (dp[i][j] > 1000000000) dp[i][j] = 1000000000;
        }
    }

    if (dp[N][M] < K) {
        cout<<"-1"; return 0;
    }

    while (N + M) {
        int a_start = dp[N - 1][M];
        int z_start = dp[N][M - 1];

        if (N == 0) {
            cout<<"z";
            M--;
            continue;
        }
        else if (M == 0) {
            cout<<"a";
            N--;
            continue;
        }

        if (K <= a_start) {
            cout<<"a";
            N--;
        }
        else {
            K = K - a_start;
            cout<<"z";
            M--;
        }
    }
    return 0;
}