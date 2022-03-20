#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

const int MAX = 1000010;
int N, dp[MAX];         // i번째를 포함하는 가장 긴 증가하는 부분수열의 마지막 숫자     // idx 길이
pair<int, int> ans[MAX];
stack<int> s;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;

    int idx = 0;
    int input; cin >> input;
    dp[idx] = input;
    ans[0] = {0, input};

    for (int i = 1; i < N; i++) {
        cin >> input;
        if (dp[idx] < input) {
            dp[++idx] = input;
            ans[i] = {idx, input};
        }
        else {
            int idx2 = lower_bound(dp, dp + idx, input) - dp;
            dp[idx2] = input;
            ans[i] = {idx2, input};
        }
    }
    cout << idx + 1 << "\n";

    for (int i = N - 1; i >= 0; i--) {
        if (ans[i].first == idx) {
            s.push(ans[i].second); idx--;
        }
    }

    while (!s.empty()) {
        cout << s.top() << " ";
        s.pop();
    }
    return 0;
}