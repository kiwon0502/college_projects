#include <iostream>
using namespace std;

void solve(int n) {
    // count[i][0] : fib(0)의 개수 // count[i][1] : fib(1)의 개수
    int** count = new int*[n];
    for (int i=0; i<n; i++) {
        count[i] = new int[2];
    }
    count[0][0] = 1;
    count[0][1] = 0;
    if ((n-1) > 0) {
        count[1][0] = 0;
        count[1][1] = 1;

        if ((n-1) > 1) {
            for (int i = 2; i<n; i++) {
                count[i][0] = count[i-1][0] + count[i-2][0];
                count[i][1] = count[i-1][1] + count[i-2][1];
            }
        }
    }
    // result
    cout<<count[n-1][0]<<" "<<count[n-1][1]<<endl;

    for (int i=0; i<n; i++) {
        delete[] count[i];
    }
    delete[] count;
}

int main() {
    int T, n;      // 테스트 케이스 개수 T, N 입력 : n
    cin>>T;
    int* N = new int[T];     // fibonacci(N)
    // input
    for (int i=0; i<T; i++) {
        cin>>n;
        N[i] = n;
    }

    for (int i=0; i<T; i++) {
        solve(N[i]+1);
    }

    delete[] N;
    return 0;
}