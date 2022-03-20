#include <iostream>
#include <algorithm>
using namespace std;
#define MAX 200010
typedef long long ll;
ll a_num, b_num, kyo, A[MAX], B[MAX];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> a_num >> b_num;
    for (ll i = 0; i < a_num; i++) cin >> A[i];
    sort(A, A + a_num);
    for (ll i = 0; i < b_num; i++) {
        ll b; cin >> b;
        ll left = 0, right = a_num - 1;
        while (left <= right) {
            ll mid = (left + right) / 2;
            if (A[mid] == b) {
                kyo++;
                break;
            }
            else if (A[mid] < b) left = mid + 1;
            else right = mid - 1;
        }
    }
    cout << (a_num + b_num - 2 * kyo);
    return 0;
}
