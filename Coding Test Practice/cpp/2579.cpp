#include <iostream>
#define MAX 10000
using namespace std;

int N;
int score[301];
int dp[301];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>N;
    for (int i=1; i<=N; i++) {
        cin>>score[i];
    }

    dp[1] = score[1];
    dp[2] = dp[1] + score[2];
    dp[3] = max(score[1], score[2]) + score[3];

    for (int i=4; i<=N; i++) {
        dp[i] = max(dp[i-2] + score[i], dp[i-3] + score[i-1] + score[i]);
    }
    cout<<dp[N];
    return 0;
}