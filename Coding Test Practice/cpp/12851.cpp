#include <iostream>
#include <queue>
using namespace std;
#define MAX 100001

int cnt, ans;
bool visited[MAX];

int BFS(int N, int K) {
    queue<pair<int, int>> q;
    q.push({N, 0});
    visited[N] = true;

    while (!q.empty()) {
        int cur = q.front().first;
        int mov = q.front().second;
        q.pop();

        visited[cur] = true;
        if (ans && ans == mov && cur == K) cnt++;
        if (!ans && cur == K) ans = mov, cnt++;

        if (cur + 1 < MAX && !visited[cur + 1]) q.push({cur + 1, mov + 1});
        if (cur - 1 >= 0 && !visited[cur - 1]) q.push({cur - 1, mov + 1});
        if (cur * 2 < MAX && !visited[cur * 2]) q.push({cur * 2, mov + 1});
    }
    return ans;
}

int main() {
    int N, K;
    cin >> N >> K;
    cout << BFS(N, K) << "\n" << cnt;
    return 0;
}
