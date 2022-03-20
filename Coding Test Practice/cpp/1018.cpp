#include <iostream>
#include <string>
using namespace std;

int N, M;
int shift;
int counts[4000];
int map[50][50];

int findBW(int xs, int ys) {
    int ans = 0;
    int world[8][8];
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            world[i][j] = map[xs + i][ys + j];
        }
    }

    int temp = 1;
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            if (i == 0 && j == 0) {
                if (temp == world[i][j]) continue;
                else {
                    ans++;
                    world[i][j] = temp;
                }
            }
            else {
                if (temp != world[i][j]) {
                    temp = world[i][j];
                }
                else {
                    ans++;
                    if (temp == 1) {
                        world[i][j] = 0;
                        temp = 0;
                    }
                    else {
                        world[i][j] = 1;
                        temp = 1;
                    }
                }
            }
        }
        temp = world[i][0];
    }
    return ans;
}

int findWB(int xs, int ys) {
    int ans = 0;
    int world[8][8];
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            world[i][j] = map[xs + i][ys + j];
        }
    }

    int temp = 0;
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            if (i == 0 && j == 0)  {
                if (temp == world[i][j]) continue;
                else {
                    ans++;
                    world[i][j] = temp;
                }
            }
            else {
                if (temp != world[i][j]) {
                    temp = world[i][j];
                }
                else {
                    ans++;
                    if (temp == 1) {
                        world[i][j] = 0;
                        temp = 0;
                    }
                    else {
                        world[i][j] = 1;
                        temp = 1;
                    }
                }
            }
        }
        temp = world[i][0];
    }
    return ans;    
}

int main() {
    cin>>N>>M;
    for (int i=0; i<N; i++) {
        string s;
        cin>>s;
        for (int j=0; j<M; j++) {
            if (s[j] == 'W') map[i][j] = 0;
            else if (s[j] == 'B') map[i][j] = 1;
        }
    }

    for (int i=0; i<=N-8; i++) {
        for (int j=0; j<=M-8; j++) {
            counts[shift++] = findWB(i, j);
            counts[shift++] = findBW(i, j);
        }
    }

    int temp = counts[0];
    for (int i=1; i<shift; i++) {
        if (temp > counts[i]) {
            temp = counts[i];
        }
    }
    cout<<temp<<endl;
    return 0;
}