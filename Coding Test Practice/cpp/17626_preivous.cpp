#include <iostream>
#include <cmath>
#define max 87654321
using namespace std;

int n;
int* sq;

int main() {
    cin>>n;
    sq = new int[n+1];
    // sq[i] = 제곱수들의 합이 i가 되는 제곱수의 개수
    for (int i=1; i<=n; i++) {
        sq[i] = max;
    }

    int root = sqrt(n);
    for (int i=1; i<=root; i++) {
        sq[i*i] = 1;
        if(n>=2){
            sq[i*i + 1] = 2;
        }
    }

    for (int i=2; i<(n+1); i++) {
        int temp = i;
        if (sq[i] != max) {
            continue;
        }

        for (int j=1; j<=sqrt(i); j++) {
            if (temp > sq[j] + sq[i-j]) {
                temp = sq[j] + sq[i-j];
            }
        }

        sq[i] = temp;
    }
    cout<<sq[n];

    delete[] sq;
    return 0;
}