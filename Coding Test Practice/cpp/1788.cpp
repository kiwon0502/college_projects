#include <iostream>
using namespace std;
int n;
int dp[1000001] = {0, 1, 0};

int main() {
    cin>>n;
    int index = n > 0 ? n : n * (-1);
    if (index == 0) {
        cout<<"0\n0";
        return 0;
    }
    for (int i = 2; i <= index; i++) {
        dp[i] = (dp[i-1] + dp[i-2])%1000000000;
    }
    dp[index] = dp[index]%1000000000;
    if (n < 0) {
        if (index % 2 == 0) {
            cout<<"-1\n";
        }
        else {
            cout<<"1\n";
        }
    }
    else {
        cout<<"1\n";
    }
    cout<<dp[index];
    return 0;
}