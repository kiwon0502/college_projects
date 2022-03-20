#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define MAX 10001

int N, ans;
int Time[MAX], endTime[MAX];
vector<int> precede[MAX];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> Time[i];
        int preNum; cin >> preNum;
        for (int j = 0; j < preNum; j++) {
            int temp; cin >> temp;
            precede[i].push_back(temp);
        }
    }

    for (int i = 1; i <= N; i++) {
        int time_max = 0;
        for (int j = 0; j < precede[i].size(); j++) time_max = max(time_max, endTime[precede[i][j]]);
        endTime[i] = time_max + Time[i];
    }

    for (int i = 1; i <= N; i++) ans = max(ans, endTime[i]);
    cout << ans;
    return 0;
}
