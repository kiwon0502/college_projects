#include <iostream>
using namespace std;

int N, white, blue;
int map[129][129];

void divMap(int xs, int ys, int xe, int ye) {
    int temp = map[xs][ys];
    for (int i = xs; i <= xe; i++) {
        for (int j = ys; j <= ye; j++) {
            if (temp == 0 && map[i][j] == 1) {
                temp = 2;
            }
            else if (temp == 1 && map[i][j] == 0) {
                temp = 2;
            }

            if (temp == 2) {
                divMap(xs, ys, (xs + xe)/2, (ys + ye)/2);
                divMap(xs, (ys + ye)/2 + 1, (xs + xe)/2, ye);
                divMap((xs + xe)/2 + 1, ys, xe, (ys + ye)/2);
                divMap((xs + xe)/2 + 1, (ys + ye)/2 + 1, xe, ye);
                return;
            }
        }
    }
    if (temp == 1) blue++;
    else if (temp == 0) white++;
    return;
}

int main() {
    cin>>N;
    for (int i=1; i<=N; i++) {
        for (int j=1; j<=N; j++) {
            cin>>map[i][j];
        }
    }
    divMap(1, 1, N, N);
    cout<<white<<endl<<blue;
    return 0;
}
