#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
#define MAX 101

string dp[MAX][MAX];

string ADD(string num1, string num2) {
    long long sum = 0;
    string result;

    while (!num1.empty() || !num2.empty() || sum) {
        if (!num1.empty()) {
            sum += num1.back() - '0';
            num1.pop_back();
        }
        if (!num2.empty()) {
            sum += num2.back() - '0';
            num2.pop_back();
        }
        result.push_back((sum % 10) + '0');
        sum /= 10;
    }
    reverse(result.begin(), result.end());
    return result;
}

string nCr(int n, int r) {
    if (n == r || r == 0) return "1";
    string &ret = dp[n][r];
    if (ret != "") return ret;
    return ret = ADD(nCr(n - 1, r), nCr(n - 1, r - 1));
}   

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int N, M; cin >> N >> M;
    cout << nCr(N, M);
    return 0;
}
