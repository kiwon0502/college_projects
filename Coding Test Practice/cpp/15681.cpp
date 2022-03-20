#include <iostream>
#include <vector>
using namespace std;

int N, R, Q;
vector<int> adj[100001];
bool visit[100001];
int dp[100001];

int dfs(int n) {
    if (dp[n] != 0) return dp[n];
    visit[n] = true;
    int vertex = 1;
    for (int i=0; i<adj[n].size(); i++) {
        int next = adj[n][i];
        if (visit[next]) continue;
        vertex += dfs(next);
    }
    dp[n] = vertex;
    return vertex;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>N>>R>>Q;
    int start, end;
    for (int i=0; i<N-1; i++) {
        cin>>start>>end;
        adj[start].push_back(end);
        adj[end].push_back(start);
    }
    dp[R] = dfs(R);
    int query;
    for (int i=0; i<Q; i++) {
        cin>>query;
        cout<<dp[query]<<'\n';
    }
    return 0;
}