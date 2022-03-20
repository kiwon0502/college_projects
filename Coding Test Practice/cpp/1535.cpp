#include <iostream>
#include <algorithm>
using namespace std;
#define MAX 21
int N, L[MAX], J[MAX], ans;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    for (int i = 0; i < N; i++) cin >> L[i];
    for (int i = 0; i < N; i++) cin >> J[i];

    for (int i = 0; i < (1L << N); i++) {
        int exp = 0, hp = 100;
        for (int j = 0; j < N; j++) {if (i & (1 << j)) { exp += J[j], hp -= L[j]; }}
        if (hp > 0) ans = max(ans, exp);
    }
    cout << ans;
    return 0;
}
