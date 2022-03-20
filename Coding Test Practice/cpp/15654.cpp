#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define MAX 9
int N, M, arr[MAX];
vector<int> v;
bool visited[MAX];

void solve(int idx) {
    if (idx == M) {
        for (int i = 0; i < M; i++) cout << arr[i] << " ";
        cout << "\n";
        return;
    }

    for (int i = 0; i < v.size(); i++) {
        if (visited[i]) continue;
        visited[i] = true;
        arr[idx] = v[i];
        solve(idx + 1);
        visited[i] = false;
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        int in; cin >> in;
        v.push_back(in);
    }
    sort(v.begin(), v.end());
    solve(0);
    return 0;
}
