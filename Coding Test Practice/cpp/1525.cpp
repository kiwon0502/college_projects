#include <iostream>
#include <algorithm>
#include <map>
#include <queue>
#include <string>
using namespace std;

int dx[] = {-1, 0, 1, 0};
int dy[] = {0, -1, 0, 1};
int num;
map<int, int> mov;
queue<int> q;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int a; cin>>a;
            if (a == 0) a = 9;
            num = num * 10 + a;
        }
    }
    q.push(num);
    mov[num] = 0;

    while (!q.empty()) {
        int now = q.front();
        string now_str = to_string(now);
        q.pop();

        int zero = (int)now_str.find('9');
        int row = zero / 3;
        int col = zero % 3;
        for (int i = 0; i < 4; i++) {
            int nrow = row + dx[i];
            int ncol = col + dy[i];
            if (nrow < 0 || nrow > 2 || ncol < 0 || ncol > 2) continue;
            string next_str = now_str;
            swap(next_str[row * 3 + col], next_str[nrow * 3 + ncol]);
            int next = stoi(next_str);

            if (mov.count(next) == 0) {
                mov[next] = mov[now] + 1;
                q.push(next);
            }
        }
    }
    if (mov.count(123456789) == 0) cout<<-1;
    else cout<<mov[123456789];
    return 0;
}