#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#define ll long long int
using namespace std;

int N, S, M;
int vol[101];
int volmax[101][1001];

int dp(int index, int volume) {
    if (volume < 0 || volume > M) return -6974892;
    if (index == N + 1) return volmax[index][volume] = volume;
    if (volmax[index][volume] != -1) return volmax[index][volume];

    volmax[index][volume] = max(dp(index + 1, volume + vol[index]), dp(index + 1, volume - vol[index]));
    return volmax[index][volume];
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>N>>S>>M;
    for (int i = 1; i <= N; i++) {
        cin>>vol[i];
    }
    memset(volmax, -1, sizeof(volmax));
    int ans = dp(1, S);
    if (ans == -6974892) cout<<-1;
    else cout<<ans;
    return 0;
}