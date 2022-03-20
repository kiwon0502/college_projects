#include <iostream>
#define MAX 100
using namespace std;

int computer[MAX + 1][MAX + 1];
bool visited[MAX + 1];
int N, M, ans;

void dfs(int n) {
    ans++;
    visited[n] = true;
    for (int i=1; i<=N; i++) {
        if (!visited[i] && computer[n][i]) {
            dfs(i);
        }
    }
    return;
}

int main() {
    cin>>N>>M;
    for (int i=1; i<=M; i++) {
        int a, b;
        cin>>a>>b;
        computer[a][b] = 1;
        computer[b][a] = 1;
    }
    dfs(1);
    cout<<(ans-1);
    return 0;
}