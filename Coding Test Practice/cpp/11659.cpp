#include <iostream>
#define MAX 100010
using namespace std;

int N, M;
int Sum[MAX];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M;
    cin >> Sum[1];
    for (int i = 2; i<= N; i++) {
        int x; cin >> x;
        Sum[i] = Sum[i - 1] + x;
    }

    while (M--) {
        int i, j; cin >> i >> j;
        cout << Sum[j] - Sum[i - 1] << "\n";
    }
    return 0;
}