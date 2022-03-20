#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

const int MAX = 21;
const double MMAX = 0x3f3f3f3f;
int T, N, sum_x, sum_y;
int a[MAX], x[MAX], y[MAX];
double ans;

void nCr(int N, int R, int q) {
    if (R == 0) {
        int sum_x_temp = sum_x, sum_y_temp = sum_y;
        for (int i = 0; i < q; i++) {
            sum_x_temp -= 2 * x[a[i]];
            sum_y_temp -= 2 * y[a[i]];
        }
        ans = min(ans, sqrt(pow(sum_x_temp, 2) + pow(sum_y_temp, 2)));
    }
    else if (N < R) return;
    else {
        a[R - 1] = N - 1;
        nCr(N - 1, R - 1, q);
        nCr(N - 1, R, q);
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cout << fixed;
    cout.precision(12);
    cin >> T;
    while (T--) {
        cin >> N;
        sum_x = 0, sum_y = 0;
        ans = MMAX;
        for (int i = 0; i < N; i++) {
            cin >> x[i] >> y[i];
            sum_x += x[i], sum_y += y[i];
        }
        nCr(N, N/2, N/2);
        cout << ans << "\n";
    }
    return 0;
}
