#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int D, K, A, B;
vector<pair<int, int>> dp(31);

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>D>>K;
    dp[1] = {1, 0};
    dp[2] = {0, 1};
    for (int i = 3; i <= D; i++) {
        dp[i] = {dp[i - 1].first + dp[i - 2].first, dp[i - 1].second + dp[i - 2].second};
    }
    
    for (int i = 0; i <= 100000; i++) {
        for (int j = i; j <= 100000; j++) {
            if (dp[D].first * i + dp[D].second * j == K) {cout<<i<<endl<<j; return 0;}
        }
    }

    return 0;
}