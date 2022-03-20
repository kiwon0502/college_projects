#include <iostream>
#include <algorithm>
using namespace std;
#define MAX 1000001

int T, N, M, arr[MAX];

bool BS(int x) {
    int left = 0, right = N - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (arr[mid] == x) return true;
        if (arr[mid] < x) left = mid + 1;
        else right = mid - 1;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> T;
    while (T--) {
        cin >> N;
        for (int i = 0; i < N; i++) cin >> arr[i];
        sort(arr, arr + N);

        cin >> M;
        for (int i = 0; i < M; i++) {
            int input; cin >> input;
            if (BS(input)) cout << "1\n";
            else cout << "0\n";
        }
    }    
    return 0;
}
