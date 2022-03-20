#include <iostream>
#include <map>
#define INF 6974
using namespace std;

int tk, u = INF, v = INF;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    while (1) {
        map<int, int> M, indegree;
        int edgeCnt = 0, nodeCnt = 0;
        bool if_tree = true;
        while ((cin>> u >> v), (u || v)) {
            if (u == -1 && v == -1) return 0;
            edgeCnt++;
            if (M.find(u) == M.end()) M.insert({u, nodeCnt++});
            if (M.find(v) == M.end()) M.insert({v, nodeCnt++});
            if (indegree.find(v) == indegree.end()) indegree.insert({v, 0});
            else if_tree = false;
        }

        if (edgeCnt > 0 && M.size() != edgeCnt + 1) if_tree = false;
        if (if_tree) cout<<"Case "<<(++tk)<<" is a tree.\n";
        else cout<<"Case "<<(++tk)<<" is not a tree.\n";
    }
    return 0;
}