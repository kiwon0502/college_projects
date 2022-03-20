#include <iostream>
#include <algorithm>
using namespace std;

int num;
long long ali[51];

int main() {
    cin>>num;
    for (int i=1; i<=num; i++) {
        cin>>ali[i];
    }
    long long temp = ali[1];
    for (int i=2; i<=num; i++) {
        if (temp < ali[i]) temp = ali[i];
    }
    long long int ans = temp;
    temp = ali[1];
    for (int i=2; i<=num; i++) {
        if (temp > ali[i]) temp = ali[i];
    }
    ans *= temp;
    cout<<ans;
    return 0;
}