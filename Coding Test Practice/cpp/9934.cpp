#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

int K, building[1024];
vector<int> tree[11];

void find_root(int start, int end, int level) {
    int mid = (start + end) / 2;
    tree[level].push_back(building[mid]);
    if (start == end) return;

    find_root(start, mid - 1, level + 1);
    find_root(mid + 1, end, level + 1);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>K;
    int node_num = pow(2, K) - 1;
    for (int i = 1; i <= node_num; i++) cin>>building[i];
    find_root(1, node_num, 1);

    for (int i = 1; i <= K; i++) {
        for (int j = 0; j < tree[i].size(); j++) cout<<tree[i][j]<<" ";
        cout<<"\n";
    }
    return 0;
}