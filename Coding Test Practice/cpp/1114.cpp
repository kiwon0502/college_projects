#include <iostream>
#include <algorithm>
using namespace std;
#define MAX 10005
#define N 1000000000

int L, K, C;
int d[MAX], e[MAX];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> L >> K >> C;
    for (int i = 0; i < K; i++) cin >> d[i];
    d[K] = L;
    sort(d, d + K);
    e[0] = d[0];
    for (int i = 1; i <= K; i++) e[i] = d[i] - d[i - 1];

    int left = 0, right = N;
    while (left <= right) {
        int mid = (left + right) / 2;

    }



    
    return 0;
}
