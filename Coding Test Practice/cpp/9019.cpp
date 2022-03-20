#include <iostream>
#include <queue>
#include <string>
#include <cstring>
using namespace std;

bool visited[10000];
int A, B;

void bfs() {
    queue<pair<int, string>> q;
    q.push({A, ""});
    visited[A] = true;

    while(!q.empty()) {
        int cur_num = q.front().first;
        string cur_op = q.front().second;
        q.pop();

        if (cur_num == B) {
            cout<<cur_op<<endl;
            return;
        }

        int D, S, L, R;
        D = (cur_num * 2) % 10000;
        if (!visited[D]) {
            visited[D] = true;
            q.push({D, cur_op + "D"});
        }
        
        S = cur_num - 1 < 0 ? 9999 : cur_num - 1;
        if (!visited[S]) {
            visited[S] = true;
            q.push({S, cur_op + "S"});
        }

        L = (cur_num % 1000) * 10 + (cur_num / 1000);
        if (!visited[L]) {
            visited[S] = true;
            q.push({L, cur_op + "L"});
        }

        R = cur_num / 10 + (cur_num % 10) * 1000;
        if (!visited[R]) {
            visited[R] = true;
            q.push({R, cur_op + "R"});
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int T; cin>>T;
    while (T--) {
        cin>>A>>B;
        memset(visited, false, sizeof(visited));
        bfs();
    }
    return 0;
}