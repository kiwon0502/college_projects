#include <iostream>
#include <algorithm>
#include <vector>
#define ll long long int
using namespace std;

ll N, score;
bool green[6][4];
bool blue[4][6];

void cleargreen() {
    if (green[0][0] && green[0][1] && green[0][2] && green[0][3]) {
        score++;
        for (int c=0; c<4; c++) {
            green[0][c] = false;
        }
    }
    for (int r=1; r<6; r++) {
        if (green[r][0] && green[r][1] && green[r][2] && green[r][3]) {
            score++;
            for (int c=0; c<4; c++) {
                green[r][c] = green[r-1][c];
            }
        }
    }
}

void overgreen() {
    for (int r=0; r<2; r++) {
        for (int c=0; c<4; c++) {
            if (green[r][c])
        }
    }
}

void actiong(ll t, ll x, ll y) {
    switch(t) {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
    }
    cleargreen();
}

void clearblue() {
    for (int c=2; c<6; c++) {
        if (blue[0][c] && blue[1][c] && blue[2][c] && blue[3][c]) {
            score++;
            for (int r=0; r<4; r++) {
                blue[r][c] = blue[r][c-1];
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>N;
    for (int T=0; T<N; T++) {
        ll t,x,y;
        cin>>t>>x>>y;
    }
    return 0;
}