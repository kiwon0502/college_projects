#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#define ll long long int
using namespace std;

ll N, M, K;
ll x, y, w;
ll graph[301][301];



int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>N>>M>>K;
    for (ll i=0; i<K; i++) {
        cin>>x>>y>>w;
        if (x > y) graph[x][y] = 0;
        else graph[x][y] = (-1) * w;
    }

    return 0;
}