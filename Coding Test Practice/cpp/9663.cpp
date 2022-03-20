#include <iostream>
#include <algorithm>

typedef long long ll;
using namespace std;

#define MAX 15

int N, ans = 0;
int col[MAX];

// 퀸이 같은 행에 있지 않아야 함
// 퀸이 같은 대각선에 있지 않아야 함
bool check(int level) {
    for (int i = 0; i < level; i++) {
        if (col[i] == col[level] || abs(col[level] - col[i]) == level - i) return false;
    }
    return true;
}

void nqueen(int x) {
    if (x == N) ans++;
    else {
        for (int i = 0; i < N; i++) {
            col[x] = i;
            if (check(x)) nqueen(x + 1);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>N;
    nqueen(0);
    cout<<ans;
    return 0;
}