#include <iostream>
#include <cstring>
using namespace std;

int N;
int dp[1001][1001][3][2];

int attendance(int days, int attend, int absent, int late) {
    if (absent == 3 || late == 2) return 0;
    if (days == N)  return 1;

    int &result = dp[days][attend][absent][late];
    if (result != -1) return result;

    result = attendance(days + 1, attend + 1, 0, late) + attendance(days + 1, attend, absent + 1, late) + attendance(days + 1, attend, 0, late + 1);
    result = result%1000000;
    return result;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>N;
    memset(dp, -1, sizeof(dp));
    cout<<attendance(0, 0, 0, 0)%1000000;
    return 0;
}