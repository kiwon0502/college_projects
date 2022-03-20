#include <iostream>
#define MAX 1050
using namespace std;

int N, M;
int Sum[MAX][MAX];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        cin >> Sum[i][1];
        for (int j = 2; j <= N; j++) {
            int x; cin >> x;
            Sum[i][j] = Sum[i][j - 1] + x;
        }
    }

    while (M--) {
        int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
        int ans = 0;
        for (int i = x1; i <= x2; i++) {
            ans += Sum[i][y2] - Sum[i][y1 - 1];
        }
        cout << ans << "\n";
    }
    return 0;
}