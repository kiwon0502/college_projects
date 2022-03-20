#include <iostream>
#include <algorithm>
#include <vector>
#include <string.h>
#include <map>
#define ll long long int
using namespace std;

ll N, M;
ll a, b, c, temp;
ll ans;
map<ll, vector<ll>> m;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>N>>M;
    for (int i = 0; i < M; i++) {
        cin>>a>>b;
        if (a > b) {
            temp = a;
            a = b;
            b = temp;
        }
        if ( m.find(a) == m.end() ) {
            vector<ll> v;
            v.push_back(b);
            m.insert(make_pair(a, v));
        } else {
            (m.find(a)->second).push_back(b);
        }
    }

    if (N < 3) {
        ans = 0;
    }
    else {
        for (int i = 1; i <= (N-2); i++) {
            c = 0;
            auto it = m.find(i);
            if ( it == m.end() ) {
                for (int j = i+1; j <= (N-1); j++) {
                    if ( m.find(j) == m.end()) {
                        c += (N - j);
                    } else {
                        c += (N - j - (m.find(j)->second).size());
                    }
                }
            } else {
                for (int j = i+1; j <= (N-1); j++) {
                    auto it2 = find((it->second).begin(), (it->second).end(), j);
                    if (it2 == (it->second).end()) {
                        if ( m.find(j) == m.end()) {
                            c += (N - j);
                        } else {
                            c += (N - j - (m.find(j)->second).size());
                        }
                    }
                    else {
                        continue;
                    }
                }
            }
            ans += c;
        }
    }
    cout<<ans;
    return 0;
}