#include <iostream>
#include <algorithm>
#include <vector>
#define ll long long int
using namespace std;

int N, ans, l, r;
vector<ll> v;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>N;
    for (int i = 0; i < N; i++) {
        ll num; cin>>num;
        v.push_back(num);
    }
    sort(v.begin(), v.end());

    for (int i = 0; i < N; i++) {
        l = 0, r = N - 1;
        while (l < r){
            if (v[l] + v[r] == v[i]) {
                if (l != i && r != i) {
                    ans++;
                    break;
                }
                else if (l == i) l++;
                else if (r == i) r--;
            }
            else if (v[l] + v[r] < v[i]) l++;
            else r--;
        }
    }
    cout<<ans;

    return 0;
}