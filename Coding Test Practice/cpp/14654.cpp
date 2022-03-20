#include <iostream>
#include <algorithm>
using namespace std;

int N;
int A[301];
int B[301];

int maxWin() {
    int teamA = 0, teamB = 0;
    int ans = 0;
    for (int i = 1; i <= N; i++) {
        if (A[i] == B[i]) {
            if (teamA == 0) {
                teamA++;
                ans = max(ans, teamB);
                teamB = 0;
            }
            else {
                teamB++;
                ans = max(ans, teamA);
                teamA = 0;
            }
        }

        switch(A[i]) {
            case 1:
                switch(B[i]) {
                    case 2:
                        teamB++;
                        ans = max(ans, teamA);
                        teamA = 0;
                        break;
                    case 3:
                        teamA++;
                        ans = max(ans, teamB);
                        teamB = 0;
                        break;
                }
                break;
            case 2:
                switch(B[i]) {
                    case 1:
                        teamA++;
                        ans = max(ans, teamB);
                        teamB = 0;
                        break;
                    case 3:
                        teamB++;
                        ans = max(ans, teamA);
                        teamA = 0;
                        break;
                }
                break;
            case 3:
                switch(B[i]) {
                    case 1:
                        teamB++;
                        ans = max(ans, teamA);
                        teamA = 0;
                        break;
                    case 2:
                        teamA++;
                        ans = max(ans, teamB);
                        teamB = 0;
                        break;
                }
                break;
        }
    }
    return max({ans, teamA, teamB});
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>N;
    for (int i = 1; i <= N; i++)
        cin>>A[i];
    for (int i = 1; i <= N; i++)
        cin>>B[i];

    cout<<maxWin();
    return 0;
}