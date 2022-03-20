#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

const int MAX = 1000010;
int N, dp[MAX][2];              // n번째 노드 , 0 / 1   => early adapter 개수
vector<int> friends[MAX];
vector<int> tree[MAX];
bool visited[MAX];

void to_tree(int here) {
    visited[here] = true;
    for (int i = 0; i < friends[here].size(); i++) {
        int next = friends[here][i];
        if (!visited[next]) {
            tree[here].push_back(next);
            to_tree(next);
        }
    }
}

int dfs(int node, int state) {
    if (dp[node][state] != -1) return dp[node][state];
    int& ret = dp[node][state];
    if (state == 1) {
        ret = 1;
        for (int i = 0; i < tree[node].size(); i++) {
            int next = tree[node][i];
            ret += min(dfs(next, 0), dfs(next, 1));
        }
    }
    else {
        ret = 0;
        for (int i = 0; i < tree[node].size(); i++) {
            int next = tree[node][i];
            ret += dfs(next, 1);
        }
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    for (int i = 1; i < N; i++) {
        int u, v; cin >> u >> v;
        friends[u].push_back(v);
        friends[v].push_back(u);
    }
    to_tree(1);
    memset(dp, -1, sizeof(dp));
    cout << min(dfs(1, 0), dfs(1, 1));
    return 0;
}
