#include <iostream>

typedef long long ll;
using namespace std;

int N, M, cnt;
int A[10001];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>N>>M;
    int i = 0, j = 0;
    for (int k = 0; k < N; k++) cin>>A[k];

    for (int i = 0; i < N; i++) {
        int sum = 0;
        for (int j = i; j < N; j++) {
            sum += A[j];
            if (sum == M) {
                cnt++;
                break;
            }
            else if (sum > M) break;
        }
    }
    cout<<cnt;
    return 0;
}