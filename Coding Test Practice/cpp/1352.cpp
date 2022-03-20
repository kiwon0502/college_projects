#include <iostream>
#include <cstring>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

bool dp[101][101];
stack<int> v;
stack<int> s;
queue<char> q;
int N;

bool solve(int n, int k) {
    if (k > N) return false;
    if (k == N) return true;
    if (dp[n][k]) return false;
    dp[n][k] = true;
    for (int i = k + 1; i >= n; i--) {
        s.push(i);
        if (solve(i + 1, k + i)) return true;
        s.pop();
    }
    return false;
}

int main() {
    cin>>N;
    if (!N) {cout<<-1; return 0;}
    solve(1, 0);
    string ans = "";
    while(!s.empty()) {
        int n = s.top();
        s.pop();
        v.push(n);
    }
    if (v.empty()) {cout<<-1; return 0;}
    char c = 'A';
    for (int i = 1; i <= N; i++) {
        if (!v.empty() && v.top() == i) {
            for (int j = 0; j < i - 1; j++) q.push(c);
            ans += c;
            c++;
            v.pop();
        }
        else {
            ans += q.front();
            q.pop();
        }
    }
    cout<<ans;
    return 0;
}