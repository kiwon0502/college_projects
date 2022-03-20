#include <iostream>
#include <string.h>
#include <cmath>
using namespace std;

int N, M;
int ans;
bool broke[10];

int possible(int c) {
    if (c == 0) {
        if (broke[0]) {
            return 0;
        } else {
            return 1;
        }
    }
    int len = 0;
    while (c > 0) {
        if (broke[c % 10]) {
            return 0;
        }
        len += 1;
        c /= 10;
    }
    return len;
}

int main() {
    // 0 ~ 9 모두 사용 가능
    memset(broke, false, 10);
    cin>>N;
    cin>>M;
    // 사용 불가능 번호 확인
    int bd;
    for (int i=0; i<M; i++) {
        cin>>bd;
        broke[bd] = true;
    }
    // 초기 설정 : + - 로만 이동
    ans = abs(N-100);

    for (int i=0; i<=1000000; i++) {
        int len = possible(i);
        if (len > 0) {
            int press = abs(i - N);
            if (ans > len + press) {
                ans = len + press;
            }
        }
    }
    cout<<ans;
    return 0;
}