#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;

const int MAX = 1001;
int T, prime[MAX];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    for (int i = 2; i <= 1000; i++) {
        if (prime[i] == 1) continue;
        for (int j = i + i; j <= 1000; j += i) prime[j] = 1;
    }

    cin >> T;
    while (T--) {
        int K; cin >> K;
        bool flag = false;
        for (int i = 2; i <= K; i++) {
            if (prime[i] == 1) continue;
            for (int j = 2; j <= K; j++) {
                if (prime[j] == 1) continue;
                for (int k = 2; k <= K; k++) {
                    if (prime[k] == 1) continue;

                    if ((i + j + k ) == K) {
                        cout << i << " " << j << " " << k << "\n";
                        flag = true;
                        break;
                    }
                }
                if (flag) break;
            }
            if (flag) break;
        }

        if (!flag) cout << "0\n";
    }
    return 0;
}
