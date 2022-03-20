#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
typedef long long ll;
using namespace std;

int T, n, m, A[1001], B[1001];
ll cnt;
vector<int> A_sum, B_sum;
map<ll, ll> partial_sum;

void solve1() {
    for (int i = 1; i<= n; i++) {
        int sum = 0;
        for (int j = i; j <= n; j++) {
            sum += A[j];
            A_sum.push_back(sum);
        }
    }

    for (int i = 1; i<= m; i++) {
        int sum = 0;
        for (int j = i; j <= m; j++) {
            sum += B[j];
            B_sum.push_back(sum);
        }
    }
    sort(B_sum.begin(), B_sum.end());

    for (int i = 0; i < A_sum.size(); i++) {
        int diff = T - A_sum[i];
        auto upper = upper_bound(B_sum.begin(), B_sum.end(), diff);
        auto lower = lower_bound(B_sum.begin(), B_sum.end(), diff);
        cnt += (upper - lower);
    } 
}

void solve2() {
    for (int i = 1; i <= n; i++) {
        int sum = 0;
        for (int j = i; j <= n; j++) {
            sum += A[j];
            partial_sum[sum]++;
        }
    }

    for (int i = 1; i<= m; i++) {
        int diff = T;
        for (int j = i; j <= m; j++) {
            diff -= B[j];
            cnt += partial_sum[diff];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>T;
    cin>>n;
    for (int i = 1; i <= n; i++) cin>>A[i];
    cin>>m;
    for (int i = 1; i <= m; i++) cin>>B[i];
    // solve1();
    solve2();
    cout<<cnt;
    return 0;
}