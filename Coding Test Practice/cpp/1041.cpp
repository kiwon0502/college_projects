#include <iostream>
#include <algorithm>
#define A 0
#define B 1
#define C 2
#define D 3
#define E 4
#define F 5
using namespace std;

unsigned long long N, ans;
int num[6];
int group2[12];
int group3[8];

void set2() {
    group2[0] = num[A] + num[B];
    group2[1] = num[A] + num[C];
    group2[2] = num[A] + num[D];
    group2[3] = num[A] + num[E];
    group2[4] = num[B] + num[C];
    group2[5] = num[B] + num[D];
    group2[6] = num[B] + num[F];
    group2[7] = num[C] + num[E];
    group2[8] = num[C] + num[F];
    group2[9] = num[D] + num[E];
    group2[10] = num[D] + num[F];
    group2[11] = num[E] + num[F];
}

void set3() {
    group3[0] = num[A] + num[B] + num[C];
    group3[1] = num[A] + num[B] + num[D];
    group3[2] = num[A] + num[C] + num[E];
    group3[3] = num[A] + num[D] + num[E];
    group3[4] = num[B] + num[C] + num[F];
    group3[5] = num[B] + num[D] + num[F];
    group3[6] = num[C] + num[E] + num[F];
    group3[7] = num[D] + num[E] + num[F];
}

int main() {
    cin>>N;
    for (int i=A; i<=F; i++) {
        cin>>num[i];
    }
    set2();
    set3();
    sort(group2, group2 + 12);
    sort(group3, group3 + 8);
    sort(num, num + 6);

    if (N == 1) {
        ans = num[0] + num[1] + num[2] + num[3] + num[4];
    }
    else {
        ans = group3[0] * 4 + group2[0] * (8 * N - 12) + num[0] * (5 * N * N - 16 * N + 12);
    }
    cout<<ans;
    return 0;
}