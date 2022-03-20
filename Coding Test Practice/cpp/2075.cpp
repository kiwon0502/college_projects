#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int N;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    priority_queue<int, vector<int>, greater<int>> pq;

    for (int i = 0; i < N; i++) {
        int x; cin >> x;
        pq.push(x);
    }

    for (int i = 1; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int x; cin >> x;
            pq.push(x);
        }
        for (int i = 0; i < N; i++) pq.pop();
    }

    cout << pq.top();
    return 0;
}
