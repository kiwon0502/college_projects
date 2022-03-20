#include <iostream>
#include <string>
using namespace std;

int N, M, diff, ans;
int A[50][50];
bool C[50][50];

void flip(int sx, int sy) {
    for (int i=sx; i<sx+3; i++) {
        for (int j=sy; j<sy+3; j++) {
            C[i][j] = !C[i][j];
        }
    }
}

int main() {
    string s;
    cin>>N>>M;
    for (int i=0; i<N; i++) {
        cin>>s;
        for (int j=0; j<M; j++) {
            A[i][j] = s[j];
        }
    }

    for (int i=0; i<N; i++) {
        cin>>s;
        for (int j=0; j<M; j++) {
            if (A[i][j] == s[j]) C[i][j] = false;
            else {
                C[i][j] = true;
                diff++;
            }
        }
    }

    if (diff == 0) {
        cout<<"0";
    }
    else {
        if (N<3 || M <3) {
            cout<<"-1";
            return 0;
        }

        for (int i=0; i<=N-3; i++) {
            for (int j=0; j<=M-3; j++) {
                if (i == N-3 && !(C[i][j] == C[i+1][j] && C[i][j] == C[i+2][j])) {
                    cout<<"-1";
                    return 0;
                }
                if (j == M-3 && !(C[i][j] == C[i][j+1] && C[i][j] == C[i][j+2])) {
                    cout<<"-1";
                    return 0;
                }
                if (C[i][j]) {
                    flip(i, j);
                    ans++;
                }
            }
        }

        for (int i=N-1; i>N-3; i--) {
            for (int j=M-1; j>M-3; j--) {
                if (C[N-3][M-3] != C[i][j]) {
                    cout<<"-1";
                    return 0;
                }
            }
        }
        
        cout<<ans;
    }
    return 0;
}