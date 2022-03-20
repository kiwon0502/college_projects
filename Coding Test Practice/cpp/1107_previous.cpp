#include <iostream>
#include <string.h>
#include <cmath>
using namespace std;

int target;
int M;
int ans = 0;
bool use[10];
bool big = false;
bool same = true;

int find_Closet(int tar) {
    int smaller, bigger;
    for (int i = tar-1; i>=0; i--) {
        if (use[i]) {
            smaller = i;
            break;
        }
    }

    for (int i = tar + 1; i<10; i++) {
        if (use[i]) {
            bigger = i;
            break;
        }
    }

    if (tar - smaller >= bigger - tar) {            // 목표 숫자보다 큰 수가 선택될 경우 다음 수부터는 무조건 작은 수 채택
        big = true;
        return bigger;
    }
    else return smaller;                            // 목표 숫자보다 작은 수가 선택될 경우 다음 수부터는 무조건 큰 수 채택
}

int find_Proper() {                                 // 적절한 수 채택
    if (big) {
        for (int i=0; i < 10; i++) {
            if (use[i]) return i;
        }
    }
    else {
        for (int i=9; i >= 0; i--) {
            if (use[i]) return i;
        }
    }
}

int main() {
    // 0 ~ 9 모두 사용 가능
    memset(use, true, 10);
    cin>>target;
    int count = 0;
    int temp = target;
    int first = 0;

    while (temp > 0) {
        temp = int(temp/10);
        count++;
    }

    cin>>M;
    // 사용 불가능 번호 확인
    int bd;
    for (int i=0; i<M; i++) {
        cin>>bd;
        use[bd] = false;
    }

    temp = target;
    int decimal = pow(10, count);
    for (int i=0; i<count; i++) {
        decimal /= 10;
        int num = temp/decimal;                     // 각 자리수마다 확인
        temp = temp%decimal;

        if (same) {                                 // 지금까지의 숫자가 다 정상 작동했을 경우
            if (use[num]) {                         // 현재 자리의 숫자 역시 정상 작동 가능
                first *= 10;
                first += num;
            }
            else {                                  // 현재 자리의 숫자 작동 불가능
                first *= 10;
                first += find_Closet(num);
                same = false;
                //cout<<i<<" : "<<find_Closet(num)<<endl;
            }
        }
        else {                                      // 앞서 큰 수를 선택했을 경우 무조건 작은 수 채택
            first *= 10;
            first += find_Proper();
            //cout<<i<<" : "<<find_Proper()<<endl;
        }
    }

    ans = count;
    ans += abs(target - first);
    cout<<ans;
    return 0;
}