#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;

int N, M, ans, maxUse;
string name, song_num;
ll guitar[11];

int checknotused(ll use) {
    int sum = 0;
    while (use) {
        sum += (use & 1);
        use >>= 1;
    }
    return sum;
}

void sol(int idx, int cnt, ll use) {
    int canPlay = checknotused(use);
    if (maxUse < canPlay) {
        maxUse = canPlay;
        ans = cnt;
    }
    else if (maxUse == canPlay) {
        ans = min(ans, cnt);
    }
    if (idx == N+1) return;

    // 현재 기타 사용
    sol(idx + 1, cnt + 1, use | guitar[idx]);
    // 현재 기타 사용 안함
    sol(idx + 1, cnt, use);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>N>>M;
    for (int i = 1; i <= N; i++) {
        cin>>name>>song_num;
        for (int j = 0; j < M; j++) {
            if (song_num[j] == 'Y') {
                guitar[i] |= (1LL << (M - 1 - j));
            }
        }
    }
    sol(1, 0, 0);

    if (maxUse == 0) {
        cout<<-1;
    }
    else {
        cout<<ans;
    }
    return 0;
}