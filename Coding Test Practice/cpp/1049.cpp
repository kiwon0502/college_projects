#include <iostream>
#include <algorithm>
#define ll long long int
using namespace std;

ll N, M;
ll bundle[50];
ll unit[50];
ll money = 88888888;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>N>>M;

    for (ll i=0; i<M; i++) {
        cin>>bundle[i]>>unit[i];
    }

    sort(bundle, bundle + M);
    sort(unit, unit + M);

    ll bun = N / 6;
    ll un;
    for (ll i = 0; i <= (bun + 1); i++) {
        if (i != bun + 1) {
            un = N - 6 * i;
        }
        else {
            un = 0;
        }
        money = min(money, i * bundle[0] + un * unit[0]);
    }
    cout<<money;
    return 0;
}