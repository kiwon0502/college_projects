#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#define ST_MAX 100000
#define TUBE_NUM_MAX 1000
using namespace std;

int N, K, M, dest;
int ans = 6974892;
const int node_num = 1 + ST_MAX + TUBE_NUM_MAX;
vector<int> graph[node_num];
int dist[node_num];

int dfs(int x) {
    if (x == dest) return dist[x];
    for (int i = 0; i < graph[x].size(); i++) {
        int next = graph[x][i];
        if (dist[next] == 0) {
            if (next > ST_MAX) {
                dist[next] = dist[x];
                dfs(next);
            }
            else {
                dist[next] = dist[x] + 1;
                dfs(next);
            }
        }
    }
    return -1;
}

int BFS() {
    queue<int> q;
    q.push(1);
    while (!q.empty()) {
        int cur = q.front();
        q.pop();

        if (cur == dest) return dist[cur];
        for (int i = 0; i < graph[cur].size(); i++) {
            int next = graph[cur][i];
            if (dist[next] == 0) {
                q.push(next);
                if (next > ST_MAX) dist[next] = dist[cur];
                else dist[next] = dist[cur] + 1;
            }
        }
    }
    return -1;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>N>>K>>M;
    for (int i = 1; i <= M; i++) {
        for (int j = 0; j < K; j++) {
            int station; cin>>station; dest = max(dest, station);
            graph[ST_MAX + i].push_back(station);
            graph[station].push_back(ST_MAX + i);
        }
    }
    dist[1] = 1;
    // cout<<dfs(1);
    cout<<BFS();
    return 0;
}