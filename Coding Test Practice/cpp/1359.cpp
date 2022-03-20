#include <iostream>
using namespace std;

int N, M, K;
int dp[9][9];

int com(int n, int r) {
    if (dp[n][r] != 0) return dp[n][r];
    if (n == r || r == 0) return 1;
    else {
        dp[n][r] = com(n - 1, r - 1) + com(n - 1, r);
        return dp[n][r];
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cout << fixed; cout.precision(16);
    cin>>N>>M>>K;
    long double total = com(N, M);
    long double sum = 0;
    for (int i = K; i <= M; i++) {
        if (M - i <= N - M) {
            sum += com(M, i) * com(N - M, M - i);
        }
    }
    cout<<(sum/total);
    return 0;
}


#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstring>

using namespace std;

int N, M, K;

int main(void){
    cin>>N>>M>>K;
int nCk[9][9] = {1};
    for(int n=0; n < 9; n++){
        nCk[n][0] = nCk[n][n] = 1;
        for(int k = 1; k <= n; k++)
            nCk[n][k] = nCk[n][n-k] = nCk[n-1][k-1] + nCk[n-1][k];
    }
    int a = 0;
    for(int i=K; i<= M; i++)  a += nCk[N][i] * nCk[N-M][M-i];
    printf("%.12lf", a/((double) nCk[N][M]  ));
}