#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <queue>

#define MAX 1000001
using namespace std;

string N;
int K, ans;
queue<pair<string, int>> q;
bool visit[MAX][11];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>N>>K;
    memset(visit, false, sizeof(visit));

    q.push({N, 0});
    while(!q.empty()) {
        pair<string, int> cur = q.front(); q.pop();
        if (cur.second == K) {
            ans = max(ans, stoi(cur.first));
            continue;
        }

        string cur_str = cur.first;
        for (int i = 0; i < cur_str.size() - 1; i++) {
            for (int j = i + 1; j < cur_str.size(); j++) {
                swap(cur_str[i], cur_str[j]);
                if (cur_str[0] == '0' || visit[stoi(cur_str)][cur.second + 1]) {
                    swap(cur_str[i], cur_str[j]);
                    continue;
                }

                q.push({cur_str, cur.second + 1});
                visit[stoi(cur_str)][cur.second + 1] = true;
                swap(cur_str[i], cur_str[j]);
            }
        }
    }

    if (ans == 0) cout<<"-1";
    else cout<<ans;
    return 0;
}