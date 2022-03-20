#include <iostream>
using namespace std;
int N, M;

int gcd(int a, int b) {
    if (a%b == 0) return b;
    return gcd(b, a%b);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>N>>M;
    cout<<M - gcd(N, M);
    return 0;
}