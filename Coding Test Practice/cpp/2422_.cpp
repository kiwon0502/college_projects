#include <iostream>
#include <algorithm>
#include <vector>
#include <string.h>
#define ll long long int
using namespace std;

int check[201][201];
int N, M, ans;

bool ch(int i, int j, int k) {
    if (check[i][j] != 1 && check[j][k] != 1 && check[i][k] != 1) return true;
    return false;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>N>>M;

    for (int i = 0; i < M; i++) {
        int a, b;
        cin>>a>>b;
        if (a < b) check[a][b] = 1;
        else check[b][a] = 1;
    }
    for (int i = 1; i <= (N-2); i++) {
        for (int j = i+1; j <= (N-1); j++) {
            for (int k = j+1; k <= N; k++) {
                if (ch(i, j, k)) ans++;
            }
        }
    }
    cout<<ans;
    return 0;
}