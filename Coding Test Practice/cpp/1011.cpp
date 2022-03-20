#include <iostream>
#include <cmath>
#define ll long long int
using namespace std;
ll T, x, y, dis, n, ans, temp;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>T;
    for (ll i = 0; i < T; i++) {
        cin>>x>>y;
        dis = y - x;
        n = sqrt(dis);

        if (dis == n * n) {
            ans = 2*n - 1;
        }
        else {
            temp = n*n+n;
            if (dis <= temp) {
                ans = 2*n;
            }
            else {
                ans = 2*n+1;
            }
        }
        cout<<ans<<endl;

    }
    return 0;
}