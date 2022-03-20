#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#define N_MAX 100005
#define H_MAX 500005
using namespace std;

int N, H, breakWall[H_MAX];
int cnt, ans = 6974892;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    memset(breakWall, 0, sizeof(breakWall));
    cin>> N >> H;
    int jang_num = N / 2;
    for (int i = 1; i <= jang_num; i++) {
        int sucksoon, jongyoo; cin >> sucksoon >> jongyoo;
        breakWall[H - jongyoo + 1]++;
        breakWall[1]++;
        breakWall[sucksoon + 1]--;
    }

    for (int i = 1; i <= H; i++) {
        breakWall[i] += breakWall[i - 1];
        if (ans == -1 || breakWall[i] < ans) {
            ans = breakWall[i];
            cnt = 1;
        }
        else if (breakWall[i] == ans) cnt++;
    }
    cout<<ans<<" "<<cnt;    
    return 0;
}