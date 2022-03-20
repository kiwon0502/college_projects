#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;
#define MAX 20001

int K, V, E;
vector<int> graph[MAX];
int visited[MAX];

void BFS(int start) {
    queue<int> q;
    int color = 1;

    visited[start] = color;
    q.push(start);

    while (!q.empty()) {
        int here = q.front();
        q.pop();

        if (visited[here] == 1) color = 2;
        else if (visited[here] == 2) color = 1;

        for (int i = 0; i < graph[here].size(); i++) {
            int next = graph[here][i];
            if (visited[next] == 0) {
                visited[next] = color;
                q.push(next);
            }
        }
    }
}

bool solve() {
    for (int i = 1; i <= V; i++) {
        for (int j = 0; j < graph[i].size(); j++) {
            int next = graph[i][j];
            if (visited[i] == visited[next]) return false;
        }
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> K;
    while (K--) {
        cin >> V >> E;
        for (int i = 0; i < E; i++) {
            int u, v; cin >> u >> v;
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        for (int i = 1; i <= V; i++) if(visited[i] == 0) BFS(i);
        if (solve()) cout << "YES\n";
        else cout << "NO\n";

        for (int i = 0; i <= V; i++) graph[i].clear();
        memset(visited, 0, sizeof(visited));
    }
    return 0;
}
