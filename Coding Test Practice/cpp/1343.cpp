#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
typedef long long ll;
using namespace std;

string board;
vector<pair<int, int>> X;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>board;
    int board_size = board.size();
    bool is_X = false; int start, end;
    for (int i = 0; i < board_size; i++) {
        if (board[i] == 'X' && !is_X) {
            start = i;
            is_X = true;
        }
        else if (board[i] == '.' && is_X) {
            end = i - 1;
            X.push_back({start, end});
            is_X = false;
        }
        
        if (i == (board_size - 1) && is_X) {
            end = i;
            X.push_back({start, end});
        }
    }

    string ans = ""; int X_idx = 0;
    for (int i = 0; i < board_size;) {
        if (board[i] == '.') {
            ans += ".";
            i++;
        }
        else {
            start = X[X_idx].first;
            end = X[X_idx++].second;
            int l = end - start + 1;
            if (l%4 == 0) {
                for (int j = 0; j < l; j++) ans += "A";
            }
            else if (l%2 == 0) {
                int q = l / 4;
                for (int j = 0; j < q; j++) ans += "AAAA";
                ans += "BB";
            }
            else {
                cout<<"-1";
                return 0;
            }
            i += l;
        }
    }
    cout<<ans;
    return 0;
}