#include <iostream>
#include <algorithm>
#include <vector>
#define MAX 50001
using namespace std;

vector<int> adj[MAX];
int N, M, parent[MAX], level[MAX];
bool check[MAX];


void buildTree(int node) {
    check[node] = true;
    int edge_num = adj[node].size();
    for (int i = 0; i < edge_num; i++) {
        int x = adj[node][i];
        if (!check[x]) {                            // check가 안되어 있다면 parent가 아니라 child이다
            parent[x] = node;
            level[x] = level[node] + 1;
            buildTree(x);
        }
    }
}

int getLCA(int n1, int n2) {
    while (level[n1] > level[n2]) n1 = parent[n1];
    while (level[n2] > level[n1]) n2 = parent[n2];

    while (n1 != n2) {
        n1 = parent[n1];
        n2 = parent[n2];
    }
    return n1;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>N;
    for (int i = 0; i < N-1; i++) {
        int from, to; cin>>from>>to;
        adj[from].push_back(to);
        adj[to].push_back(from);
    }
    buildTree(1);           // root가 1번

    cin>>M;
    for (int i = 0; i < M; i++) {
        int a, b; cin>>a>>b;
        cout<<getLCA(a, b)<<"\n";
    }
    return 0;
}