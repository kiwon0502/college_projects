#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;
typedef vector<vector<ll>> Matrix;
const int MOD = 1e9 + 7;

Matrix init = { {1, 1}, {1, 0}};
ll n;

Matrix matmul(Matrix a, Matrix b) {
    Matrix ret(2);
    for (int i = 0; i < 2; i++) {
        ret[i].resize(2);
        for (int j = 0; j < 2; j++) {
            ret[i][j] = 0;
            for (int k = 0; k < 2; k++) {
                ret[i][j] += a[i][k] * b[k][j];
                ret[i][j] %= MOD;
            }
        }
    }
    return ret;
}

Matrix solve(ll n) {
    if (n == 1) return init;
    Matrix temp;
    if (n%2) {
        temp = solve(n - 1);
        return matmul(init, temp);
    } else {
        temp = solve(n / 2);
        return matmul(temp, temp);
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n;
    if (!n) {cout << 0; return 0;}
    Matrix ret = solve(n);
    cout << ret[1][0];
}
