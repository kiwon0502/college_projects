#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <unordered_map>
typedef long long ll;
using namespace std;

ll A[4001], B[4001], C[4001], D[4001];
ll n, ans;

void solve_map() {                                          // 시간 초과
    map<ll, ll> AB;
    for (ll i = 1; i <= n; i++) {
        for (ll j = 1; j <= n; j++) {
            AB[A[i] + B[j]]++;
        }
    }
    for (ll i = 1; i <= n; i++) {
        for (ll j = 1; j <= n; j++) {
            ans += AB[(-1) * (C[i] + D[j])];
        }
    }
}

void solve2() {                                             // 메모리 초과
    unordered_map<ll, ll> AB;
    for (ll i = 1; i <= n; i++) {
        for (ll j = 1; j <= n; j++) {
            AB[A[i] + B[j]]++;
        }
    }
    for (ll i= 1; i <= n; i++) {
        for (ll j = 1; j <= n; j++) {
            ans += AB[(-1) * (C[i] + D[j])];
        }
    }
}

void solve3() {
    vector<ll> AB, CD;
    for (ll i = 1; i <= n; i++) {
        for (ll j = 1; j <= n; j++) {
            AB.push_back(A[i] + B[j]);
            CD.push_back(C[i] + D[j]);
        }
    }
    sort(AB.begin(), AB.end());
    sort(CD.begin(), CD.end());

    ll p_cd = CD.size() - 1, cnt = 0;
    for (ll p_ab = 0 ; p_ab < AB.size() ; p_ab++) {
        ll target = -AB[p_ab];
        if (0 < p_ab && AB[p_ab] == AB[p_ab - 1]) {
            ans += cnt;
        }
        else {
            while (0 <= p_cd && target < CD[p_cd]) {
                p_cd--;
            }
            cnt = 0;
            while (0 <= p_cd && target == CD[p_cd]) {
                cnt++;
                p_cd--;
            }
            ans += cnt;
        }
    }
}

ll solve4() {
    vector<ll> v1, v2;
    for(int i=0; i<n; i++) for(int j=0; j<n; j++) v1.push_back(A[i] + B[j]);
    for(int i=0; i<n; i++) for(int j=0; j<n; j++) v2.push_back(C[i] + D[j]);
    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end(), greater<int>());    
    int l=0, r=0;
    ll anw = 0;
    while(l < v1.size() && r < v2.size()){
        if(v1[l] == -v2[r]){
            ll ll = l, rr = r;
            while(ll < v1.size() && v1[ll] == v1[l]) ll++;
            while(rr < v2.size() && v2[rr] == v2[r]) rr++;
            anw += (ll-l)*(rr-r); 
            l = ll, r = rr;
        }
        else if(v1[l] < -v2[r]) l++;
        else if(v1[l] > -v2[r]) r++;
    }
    return anw;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>n;
    for (ll i = 1; i <= n; i++) cin>>A[i]>>B[i]>>C[i]>>D[i];
    // solve_map();
    // solve2();
    solve3();
    cout<<ans;
    return 0;
}