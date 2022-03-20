#include <iostream>
#include <algorithm>
#include <string.h>
#include <vector>
using namespace std;

int N, M, sum;
int x, y;
int dist[10001];
bool visited[10001];
vector<int> graph[10001];

void dfs(int start) {
    visited[start] = true;
    sum++;
    for (int i = 0; i < graph[start].size(); i++) {
        int next = graph[start][i];
        if (!visited[next]) {
            dfs(next);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>N>>M;
    for (int i = 1; i <= M; i++) {
        cin>>x>>y;
        graph[y].push_back(x);
    }

    int maxVal = 0;
    for (int i = 1; i <= N; i++) {
        memset(visited, 0, sizeof(visited)/sizeof(bool));
        sum = 0;
        dfs(i);
        dist[i] = sum;
        maxVal = max(maxVal, sum);
    }

    for (int i = 1; i <= N; i++) {
        if (maxVal == dist[i]) cout<<i<<" ";
    }

    return 0;
}