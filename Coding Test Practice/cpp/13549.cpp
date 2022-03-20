#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
#define MAX 100001

int N, K;
bool visited[MAX];

int BFS(int n, int k) {
    queue<pair<int, int>> q;
    visited[n] = true;
    q.push({0, n});
    int ans = 6974892;

    while (!q.empty()) {
        int cnt = q.front().first;
        int here = q.front().second;
        q.pop();
        visited[here] = true;

        if (here == k) {
            ans = min(ans, cnt);
            continue;
        }
        

        if (here + 1 < MAX && !visited[here + 1]) q.push({cnt + 1, here + 1});
        if (here - 1 >= 0 && !visited[here - 1]) q.push({cnt + 1, here - 1});
        if (here * 2 < MAX && !visited[here * 2]) q.push({cnt, here * 2});
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> K;
    cout << BFS(N, K);
    return 0;
}
