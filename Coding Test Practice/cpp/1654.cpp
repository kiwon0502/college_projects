#include <iostream>
#include <algorithm>
#include <climits>
typedef long long ll;
using namespace std;

#define MAX 10001
int K, N;
ll ans, lan[MAX];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    ll left = 1, right = 0;
    cin >> K >> N;
    for (int i = 0; i < K; i++) {
        cin >> lan[i];
        right = max(right, lan[i]);
    }

    while (left <= right) {
        ll mid = (left + right) / 2;

        int cnt = 0;
        for (int i = 0; i < K; i++)
            cnt += (lan[i] / mid);

        if (cnt >= N) {
            ans = max(ans, mid);
            left = mid + 1;
        }
        else right = mid - 1;
    }
    cout << ans;
    return 0;
}
