#include <iostream>
using namespace std;

int N, M;
int map[101][101];


int main() {
    cin>>N>>M;
    for (int i=1; i<=N; i++) {
        for (int j=1; j<=M; j++) {
            cin>>map[i][j];
        }
    }

    for (int i=1; i<=N; i++) {
        for (int j=1; j<=M; j++) {
            cout<<map[i][j]<<" ";
        }
        cout<<endl;
    }

    return 0;
}