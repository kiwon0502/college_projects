#include <iostream>
#include <cmath>
#define ll long long int
using namespace std;

int main() {
    ll n;
    cin>>n;
    ll q = sqrt(n);
    if (q * q < n) q++;
    cout<<q;
    return 0;
}