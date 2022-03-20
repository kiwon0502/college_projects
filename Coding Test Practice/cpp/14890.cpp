#include <iostream>
#include <vector>
using namespace std;

const int MAX = 110;
int N, L;

int solve(vector<vector<int>> &world) {
    int temp, error = 1, res = 0;
    for (int i = 0; i < N; i++) {
        temp = world[i][0];
        error = 0;

        for (int j = 1; j < N; j++) {
            if (temp == world[i][j]) continue;
            else if (temp == world[i][j] + 1) {
                temp--;
                for (int k = j; k < j + L; k++) {
                    if (k >= N || temp != world[i][k]) {
                        error = 1;
                        break;
                    }
                    world[i][k] = -1;
                }
                if (error) break;
                else j += L - 1;
            }
            else if (temp == world[i][j] - 1) {
                temp++;
                for (int k = j - 1; k > j - L - 1; k--) {
                    if (k < 0 || temp != world[i][k] + 1) {
                        error = 1;
                        break;
                    }
                    world[i][k] = -1;
                }
                if (error) break;
            }
            else {
                error = 1;
                break;
            }
        }
        if (error == 0) res++;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> L;
    vector<vector<int>> rc(N, vector<int>(N, 0));
    vector<vector<int>> cr(N, vector<int>(N, 0));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> rc[i][j], 
            cr[j][i] = rc[i][j];
        }
    }
    cout << solve(rc) + solve(cr);
    return 0;
}
