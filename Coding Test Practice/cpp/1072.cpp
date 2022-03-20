#include <iostream>
#include <algorithm>
#define MAX 1000000000
typedef long long ll;
using namespace std;
ll x, y, z, ans;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>x>>y;
    z = (y * 100) / x;
    if (z == 100 || z == 99) {
        cout<<"-1";
        return 0;
    }

    ll bottom = 1, top = MAX, mid, ans = MAX;
    while (bottom <= top) {
        mid = (bottom + top) / 2;
        ll nextZ = (y + mid) * 100 / (x + mid);
        if (z < nextZ) {ans = min(ans, mid); top = mid - 1;}
        else bottom = mid + 1;
    }
    cout<<ans;
}