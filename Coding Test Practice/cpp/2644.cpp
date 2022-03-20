#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
#define MAX 101

int dist[MAX];
vector<int> family[MAX];

int BFS(int start, int end) {
    queue<int> q;
    q.push(start);

    while(!q.empty()) {
        int cur = q.front();
        q.pop();

        if (cur == end) return dist[end];
        for (int i = 0; i < family[cur].size(); i++) {
            int next = family[cur][i];
            if (dist[next] == 0) {
                q.push(next);
                dist[next] = dist[cur] + 1;
            }
        }
    }
    return -1;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n, start, end, m; cin >> n >> start >> end >> m;
    for (int i = 0; i < m; i++) {
        int parent, child; cin >> parent >> child;
        family[parent].push_back(child);
        family[child].push_back(parent);        
    }
    cout << BFS(start, end);
    return 0;
}
