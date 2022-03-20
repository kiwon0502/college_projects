#include <iostream>
#include <string>
#include <cstring>
#define MAX 55
using namespace std;

int N;
int graph[MAX][MAX];
bool visited[MAX];
int friends[MAX];

void brute_force(int x) {
    for (int nx = 1; nx <= N; nx++) {
        // 자기 자신
        if (nx == x) continue;

        // 바로 친구
        else if (graph[x][nx] == 1) {
            friends[x]++;
            // visited[nx] = true;
        }

        // 다리 건너 친구
        else {
            // i와 친구이면서 X와 친구인 경우
            for (int j = 1; j <= N; j++) {
                if (graph[nx][j] == 1 && graph[j][x] == 1) {
                    friends[x]++;
                    // visited[j] = true;
                    break;
                }
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    for (int i = 1; i <= N; i++) {
        string s; cin >> s;
        for (int j = 1; j <= N; j++) {
            if (s[j - 1] == 'N') graph[i][j] = 0;
            else graph[i][j] = 1;

        }
    }

    for (int i = 1; i <= N; i++) {
        memset(visited, 0, sizeof(visited));
        brute_force(i);
    }

    // for (int i = 1; i <= N; i++) cout << friends[i];
    // cout<<endl;

    int mfamous = friends[1];
    for (int i = 1; i <= N; i++) {
        mfamous = max(mfamous, friends[i]);
    }
    cout << mfamous;
    return 0;
}