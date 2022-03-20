#include <iostream>
#include <algorithm>
using namespace std;

int N;
int dp[3], input[3];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    cin >> dp[0] >> dp[1] >> dp[2];
    for (int i = 1; i < N; i++) {
        cin >> input[0] >> input[1] >> input[2];
        input[0] += min(dp[1], dp[2]);
        input[1] += min(dp[0], dp[2]);
        input[2] += min(dp[0], dp[1]);
        for (int i = 0; i < 3; i++) dp[i] = input[i];
    }
    cout << min({dp[0], dp[1], dp[2]});
    return 0;
}
