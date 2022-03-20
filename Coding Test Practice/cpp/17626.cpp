#include <iostream>
#include <cmath>
#include <cstring>
#define MAX 87654321
using namespace std;

int n;
int dp[50010];

int main() {
    cin>>n;
    for (int i=0; i<50010; i++) {
        dp[i] = MAX;
    }
    // sq[i] = 제곱수들의 합이 i가 되는 제곱수의 개수
    dp[0] = 0;
    dp[1] = 1;

    for (int i=1; i<=n; i++) {
        for (int j=0; j<=sqrt(i); j++) {
            int store = i - (j*j);
            dp[i] = min(dp[i], dp[store] + 1);
        }
    }

    cout<<dp[n];
    return 0;
}