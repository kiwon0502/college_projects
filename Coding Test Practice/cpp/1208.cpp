#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define MAX 41
int N, S;
int arr[MAX];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> S;
    for (int i = 0; i < N; i++) cin >> arr[i];
    int half = N / 2;

    vector<int> first(1 << (N - half));
    for (int i = 0; i < 1 << (N - half); i++) {
        for (int j = 0; j < N - half; j++) {
            if (i & (1 << j)) first[i] += arr[j];
        }
    }

    vector<int> second(1 << half);
    for (int i = 0; i < 1 << half; i++) {
        for (int j = 0; j < half; j++) {
            if (i & (1 << j)) second[i] += arr[j + (N - half)];
        }
    }

    sort(first.begin(), first.end());
    sort(second.begin(), second.end(), greater<int>());

    int idx = 0, idx2 = 0;
    long long res = 0;
    while (idx < (1 << (N - half)) && idx2 < (1 << half)) {
        if (first[idx] + second[idx2] == S) {
            long long cnt = 1, cnt2 = 1;
            idx++, idx2++;
            while (idx < 1 << (N - half) && first[idx] == first[idx - 1]) idx++, cnt++;
            while (idx2 <  1 << half && second[idx2] == second[idx2 - 1]) idx2++, cnt2++;
            res += cnt * cnt2;
        }
        else if (first[idx] + second[idx2] < S) idx++;
        else if (first[idx] + second[idx2] > S) idx2++;
    }

    if (S == 0) res--;
    cout << res;
    return 0;
}