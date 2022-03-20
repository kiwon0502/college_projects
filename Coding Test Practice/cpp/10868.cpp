#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int MAX = 1e5 + 5;
const int INF = 1e9 + 5;

int arr[MAX], tree[MAX * 4];
int N, M;

int init(int node, int start, int end) {
    if (start == end) return tree[node] = arr[start];

    int mid = (start + end) / 2;
    int left_result = init(node * 2, start, mid);
    int right_result = init(node * 2 + 1, mid + 1, end);

    return tree[node] = min(left_result, right_result);
}

int getMin(int node, int start, int end, int left, int right) {
    if (left > end || right < start) return INF;
    if (left <= start && end <= right) return tree[node];

    int mid = (left + right) / 2;
    int left_result = getMin(node * 2, start, mid, left, right);
    int right_result = getMin(node * 2 + 1, mid + 1, end, left, right);

    return min(left_result, right_result);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> N >> M;
    for (int i = 1; i <= N; i++) cin >> arr[i];
    init(1, 1, N);
    cout << getMin(1, 1, N, 3, 5);
    // while (M--) {
    //     int a, b; cin >> a >> b;
    //     cout << getMin(1, 1, N, a, b) << "\n";
    // }
    return 0;
}
