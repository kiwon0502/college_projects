#include <iostream>
#include <algorithm>
using namespace std;

int N, ans;
int ptime[1001];
int sum[1001];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>N;
    for (int i = 1; i <= N; i++) cin>>ptime[i];
    sort(ptime + 1, ptime + (N + 1));
    sum[1] = ptime[1];
    for (int i = 2; i <= N; i++) {
        sum[i] = sum[i - 1] + ptime[i];
    }
    for (int i = 1; i <= N; i++) ans += sum[i];
    cout<<ans;
    return 0;
}