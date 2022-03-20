#include <iostream>
using namespace std;
#define MAX 51

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int N, score, P, rank[MAX];
    cin >> N >> score >> P;
    for (int i = 1; i <= N; i++) cin >> rank[i];

    int cnt = 0, ans = 1;
    for (int i = 1; i <= N; i++) {
        if (rank[i] > score) ans++;
        else if (rank[i] == score) {}
        else break;
        cnt++;
    }
    if (cnt == P) ans = -1;
    else if (N == 0) ans = 1;
    
    cout << ans;
    return 0;
}
