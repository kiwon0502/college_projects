#include <iostream>
#include <algorithm>
#include <climits>
typedef long long ll;
using namespace std;
#define MAX 100005

int N;
int water[MAX];
int first, second;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    for (int i = 0; i < N; i++)
        cin >> water[i];
    sort(water, water + N);

    int start = 0;
    int end = N - 1;
    int min = 2000000000;

    while (start < end) {
        int sum = water[start] + water[end];

        if (min > abs(sum)) {
            min = abs(sum);
            first = water[start];
            second = water[end];

            if (sum == 0) break;
        }

        if (sum < 0) start++;
        else end--;
    }
    cout << first << " " << second;
    return 0;
}
