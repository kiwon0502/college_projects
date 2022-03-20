#include <iostream>
#include <cmath>
using namespace std;

int N;
int white, blue;
int map[129][129];

bool checksame(int r, int c, int length) {
    for (int i=0; i<length; i++) {
        for (int j=0; j<length; j++) {
            if (i == 0 && j == 0) continue;
            else if (map[r][c] != map[r + i][c + j]) return false;
        }
    }
    return true;
}

void checkblue(int r, int c) {
    if (map[r][c]) blue++;
    else white++;
}

int findpow() {
    int m = N;
    int ans = 0;
    while (m != 1) {
        ans++;
        m /= 2;
    }
    return ans;
}

int main() {
    cin>>N;
    for (int i=1; i<=N; i++) {
        for (int j=1; j<=N; j++) {
            cin>>map[i][j];
        }
    }

    int time = findpow();
    for (int i=0; i<time; i++) {
        int length = N / pow(2, i);
        
    }
    cout<<white<<endl<<blue;
    return 0;
}
