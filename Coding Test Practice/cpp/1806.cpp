#include <iostream>
#include <algorithm>
using namespace std;

int seq[100001];
int N, S, ans;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>N>>S;
    for (int i = 0; i < N; i++) cin>>seq[i];

    int left = 0, right = 0, sum = 0; ans = 6974892;
    while (left <= right) {
        if (sum >= S) {
            ans = min(ans, right - left);
            sum -= seq[left++];
        }
        else if (right == N) break;
        else sum += seq[right++];
    }

    if (ans == 6974892) cout<<"0";
    else cout<<ans;
    return 0;
}