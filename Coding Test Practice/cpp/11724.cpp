#include <iostream>
using namespace std;

int N, M, cnt;
int graph[1001][1001];
bool visited[1001];

void dfs(int x) {
    visited[x] = true;
    for (int i = 1; i <= N; i++) {
        if (graph[x][i] && !visited[i]) dfs(i);
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>N>>M;
    for (int i = 1; i <= M; i++) {
        int s, e; cin>>s>>e;
        graph[s][e] = 1;
        graph[e][s] = 1;
    }
    for (int i = 1; i <= N; i++) {
        if (!visited[i]) {
            dfs(i);
            cnt++;
        }
    }
    cout<<cnt;
    return 0;
}