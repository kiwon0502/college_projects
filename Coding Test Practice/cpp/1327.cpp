#include <iostream>
#include <algorithm>
#include <queue>
#include <map>
using namespace std;

int N, K;
string s;
map<string, bool> visited;

string reverse(string str) {
    int l = str.length();
    for (int i = 0; i < (l/2); i++) {
        char temp = str[i];
        str[i] = str[l - i - 1];
        str[l - i - 1] = temp;
    }
    return str;
}

int bfs() {
    string ans = s;
    sort(ans.begin(), ans.end());
    queue<pair<string, int>> q;
    q.push({s, 0});
    visited[s] = true;

    while (!q.empty()) {
        string x = q.front().first;
        int count = q.front().second;
        q.pop();

        if (x == ans) return count;
        for (int i = 0; i <= N - K; i++) {
            string temp = x.substr(i, K);
            string next = x.substr(0, i) + reverse(temp) + x.substr(i + K);
            if (!visited.count(next)) {
                q.push({next, count + 1});
                visited[next] = true;
            }
        }
    }
    return -1;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>N>>K;
    for (int i = 0; i < N; i++) {
        char a; cin>>a;
        s += a;
    }
    cout<<bfs();
    return 0;
}