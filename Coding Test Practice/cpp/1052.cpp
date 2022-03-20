#include <iostream>
#include <algorithm>
#include <map>
#include <cmath>
#define ll long long int
using namespace std;

ll N, K;
map<ll, ll> power;

int find_label() {
    for (ll i=0; i<19; i++) {
        if (N >= power.find(i)->second && N < power.find(i+1)->second) {
            return i;
        }
    }
    return 0;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>N>>K;
    for (ll i=0; i<20; i++) {
        power.insert(make_pair(i, pow(2, i)));
    }
    ll label = find_label();
    if (N == power.find(label)->second) {
        cout<<"0";
    }
    else {
        
    }
    return 0;
}