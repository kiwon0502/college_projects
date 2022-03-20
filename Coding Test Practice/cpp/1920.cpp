#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;
#define MAX 100001

ll M, N, A[MAX];

bool find(int target) {
    int left = 0;
    int right = N - 1;

    while (left <= right) {
        int mid = (left + right) / 2;
        if (A[mid] == target) return true;
        else if (A[mid] < target) {
            left = mid + 1; continue;
        }
        else if (A[mid] > target) {
            right = mid - 1; continue;
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>N;
    for (ll i = 0; i < N; i++) cin>>A[i];
    sort(A, A + N);

    cin>>M;
    for (ll i = 0; i < M; i++) {
        ll X; cin>>X;
        cout<<find(X)<<"\n";
    }
    return 0;
}