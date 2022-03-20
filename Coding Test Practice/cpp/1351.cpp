#include <iostream>
#include <map>
using namespace std;

long long N, P, Q;
map<long long, long long> dp;

long long findans(long long n) {
    if (dp.count(n)) {
        return dp[n];
    }
    else {
        return dp[n] = findans(n/P) + findans(n/Q);
    }
}

int main() {
    cin>>N>>P>>Q;
    dp[0] = 1;
    cout<<findans(N)<<endl;
    return 0;
}