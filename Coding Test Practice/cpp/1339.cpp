#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;

ll N, ans, alpha[27];
vector<ll> V;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>N;
    for (int i = 0; i < N; i++) {
        string s; cin>>s;
        int idx = 1;
        for (int j = s.length() - 1; j >= 0; j--) {
            alpha[s[j] - 'A'] += idx;
            idx *= 10;
        }
    }

    for (int i = 0; i < 27; i++) {
        if (alpha[i] != 0) V.push_back(alpha[i]);
    }
    sort(V.begin(), V.end());

    int max_int = 9;
    for (int i = V.size() - 1; i >= 0; i--) {
        ans += max_int * V[i];
        max_int--;
    }
    cout<<ans;
    return 0;
}