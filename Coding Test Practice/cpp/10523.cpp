#include <iostream>
#include <algorithm>
#include <vector>
#define ll long long int
using namespace std;

ll n, p, px, py;
vector<pair<ll, ll>> points;

bool if_same_line(ll x1, ll y1, ll x2, ll y2, ll x3, ll y3) {
    double a = (y2 - y1) / (x2 - x1);
    double b = a * (x3 - x1) + y1;
    if (b == y3) return true;
    return false;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>p;
    for (int i=0; i<n; i++) {
        cin>>px>>py;
        points.push_back(make_pair(px, py));
    }
    if (if_same_line(points[0].first, points[0].second, points[1].first, points[1].second, points[2].first, points[2].second)) {
        cout<<"fuck"<<endl;
    }
    else {
        cout<<"shit"<<endl;
    }
    return 0;
}