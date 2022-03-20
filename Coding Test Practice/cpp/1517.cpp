#include <iostream>
typedef long long ll;
using namespace std;

const int MAX = 500010;
int N, a[MAX], tmp_arr[MAX];

ll solve(int start, int end) {
    if (start == end) return 0;
    int mid = (start + end) / 2;
    ll ans = solve(start, mid) + solve(mid + 1, end);

    int i = start;
    int j = mid + 1;
    int idx = start;
    while (i <= mid || j <= end) {
        if (i <= mid && (end < j || a[i] <= a[j])) tmp_arr[idx++] = a[i++];
        else {
            tmp_arr[idx++] = a[j++];
            ans += mid - i + 1;
        }
    }
    for (int i = start; i <= end; i++) a[i] = tmp_arr[i];
    return ans;
}


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    for (int i = 1; i <= N; i++) cin >> a[i];
    cout << solve(1, N);    
    return 0;
}
