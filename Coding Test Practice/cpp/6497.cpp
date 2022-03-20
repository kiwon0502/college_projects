#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define MAX 200001

int m, n;
int total, part;
vector<pair<int, pair<int, int>>> Edge;
int check[MAX];

void init() {
    Edge.clear();
    for (int i = 0; i < MAX; i++) check[i] = i;
    total = part = 0;
}

int getParent(int x) {
    if (check[x] == x) return x;
    return check[x] = getParent(check[x]);
}

void unionParent(int x, int y) {
    x = getParent(x);
    y = getParent(y);
    if (x < y) check[y] = x;
    else check[x] = y;
}

bool checkParent(int x, int y) {
    x = getParent(x);
    y = getParent(y);
    if (x == y) return true;
    return false;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    while (1) {
        cin >> m >> n;
        if (m == 0 && n == 0) return 0;
        init();

        for (int i = 0; i < n; i++) {
            int x, y, z; cin >> x >> y >> z;
            Edge.push_back({z, {x, y}});
            total += z;
        }

        sort(Edge.begin(), Edge.end());
        for (int i = 0; i < Edge.size(); i++) {
            int cost = Edge[i].first;
            int node1 = Edge[i].second.first;
            int node2 = Edge[i].second.second;

            if (!checkParent(node1, node2)) {
                unionParent(node1, node2);
                part += cost;
            }
        }

        cout << total - part << "\n";
    }
}
