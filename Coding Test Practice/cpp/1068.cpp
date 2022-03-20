#include <iostream>
#include <vector>
using namespace std;
#define MAX 51

int N, root, target;
vector<int> tree[MAX];
bool visited[MAX];

int DFS(int cur) {
    visited[cur] = true;
    int ret = 0;
    for (int i = 0; i < tree[cur].size(); i++) {
        int next = tree[cur][i];
        if (visited[next] || next == target) continue;
        ret += DFS(next);
    }
    if (ret == 0) return 1;
    else return ret;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    for (int i = 0; i < N; i++) {
        int parent; cin >> parent;
        if (parent == -1) root = i;
        else tree[parent].push_back(i);
    }
    cin >> target;
    if (root == target) cout << "0";
    else cout << DFS(root);
    return 0;
}
