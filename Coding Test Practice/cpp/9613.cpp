#include <iostream>
#include <string.h>
using namespace std;

int n;
long long ans;
int* num;
int* gcdList;

int getGCD (int a, int b) {
    if (b == 0) return a;
    return getGCD (b, a % b);
}

int main() {
    int T;
    cin>>T;             // 테스트 케이스 수
    while (T-- > 0) {
        cin>>n;
        num = new int[n];
        for (int i=0; i<n; i++) {
            cin>>num[i];
        }
        int gcdNum = n * (n - 1) / 2;                   // n개의 수 중에서 쌍을 짓는 방법의 수
        gcdList = new int[gcdNum];                      // GCD의 리스트
        int count = 0;
        for (int i=0; i<n; i++) {
            for (int j=(i+1); j<n; j++) {
                gcdList[count++] = getGCD(num[i], num[j]);        // 2개씩 조지기
            }
        }

        ans = 0;
        for (int i=0; i<gcdNum; i++) {
            ans += gcdList[i];
        }
        cout<<ans<<endl;
        delete[] num;
        delete[] gcdList;
    }
    return 0;
}