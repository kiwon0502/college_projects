#include <iostream>
#include <algorithm>
using namespace std;

const int MAX = 1001;
int N, ans, arr[MAX], dp[MAX];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    for (int i = 0; i < N; i++) { cin >> arr[i]; dp[i] = arr[i]; }
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[i] > arr[j]) dp[i] = max(dp[i], dp[j] + arr[i]);
        }
        ans = max(ans, dp[i]);
    }
    cout << ans;
    return 0;
}
