#include <iostream>
typedef long long ll;
using namespace std;

ll n, F[100];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>n;
    F[0] = 0;
    F[1] = 1;
    for (ll i = 2; i <= n; i++) {
        F[i] = F[i - 1] + F[i - 2];
    }
    cout<<F[n];
    return 0;
}