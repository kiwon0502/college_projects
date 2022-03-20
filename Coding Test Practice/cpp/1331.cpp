#include <iostream>
using namespace std;

int dx[] = {-2, -2, -1, -1, 1, 1, 2, 2};
int dy[] = {-1, 1, -2, 2, -2, 2, -1, 1};
bool visited[6][6];
bool flag = false;
string start, in;
int srow, scol, nrow, ncol;

int main() {
    cin>>start;
    srow = 5 - (start[1] - '1');
    scol = start[0] - 'A';
    nrow = srow; ncol = scol;
    visited[srow][scol] = true;

    for (int i = 0; i < 35; i++) {
        cin>>in;
        int nnx = 5 - (in[1] - '1');
        int nny = in[0] - 'A';
        flag = false;
        
        for (int j=0; j<8; j++) {
            int mx = nrow + dx[j];
            int my = ncol + dy[j];
            if (mx < 0 || mx >= 6 || my < 0 || my >= 6) continue;
            if (mx == nnx && my == nny && !visited[mx][my]) {
                flag = true; visited[mx][my] = true; break;
            }
        }
        if (flag) {
            nrow = nnx;
            ncol = nny;
        }
        else {
            cout<<"Invalid";
            return 0;
        }
    }
    flag = false;
    for (int i=0; i<8; i++) {
        if (nrow + dx[i] == srow && ncol + dy[i] == scol) {
            flag = true;
            break;
        }
    }
    if (flag) cout<<"Valid";
    else cout<<"Invalid";
    return 0;
}