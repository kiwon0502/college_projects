#include <iostream>
using namespace std;
#define MAX 9
#define square(x, y) ((x/3) * 3 + y/3)

int sudoku[MAX][MAX];
bool Row[MAX][MAX + 1];
bool Col[MAX][MAX + 1];
bool Square[MAX][MAX + 1];

void dfs(int n) {
    if (n == 81) {
        for (int i = 0; i < MAX; i++) {
            for (int j = 0; j < MAX; j++) {
                cout<<sudoku[i][j]<<" ";
            }
            cout<<"\n";
        }
        exit(0);
    }
    
    int x = n/MAX;
    int y = n%MAX;
    if (!sudoku[x][y]) {
        for (int i = 1; i < 10; i++) {
            if (!Row[x][i] && !Col[y][i] && !Square[square(x, y)][i]) {
                Row[x][i] = Col[y][i] = Square[square(x, y)][i] = true;
                sudoku[x][y] = i;
                dfs(n + 1);
                sudoku[x][y] = 0;
                Row[x][i] = Col[y][i] = Square[square(x, y)][i] = false;
            }
        }
    }
    else dfs(n + 1);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            cin>>sudoku[i][j];
            if (sudoku[i][j]) {
                Row[i][sudoku[i][j]] = true;
                Col[j][sudoku[i][j]] = true;
                Square[square(i, j)][sudoku[i][j]] = true;
            }
        }
    }
    dfs(0);
    return 0;
}