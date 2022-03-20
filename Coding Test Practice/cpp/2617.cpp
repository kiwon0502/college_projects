#include <iostream>
#include <algorithm>
#include <cstring>
#define MAX 110
using namespace std;

int N, M, ans;
int bigger[MAX], smaller[MAX], graph[MAX][MAX];
bool visited[MAX], bflag;

void dfs(int start, int x) {
    visited[x] = true;

    for (int i = 1; i <= N; i++) {
        if (bflag && graph[x][i] == 1 && !visited[i]) {
            bigger[start]++;
            dfs(start, i);
        }
        else if (!bflag && graph[x][i] == -1 && !visited[i]) {
            smaller[start]++;
            dfs(start, i);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M;
    for (int i = 1; i <= M; i++) {
        int heavy, light; cin >> heavy >> light;
        graph[light][heavy] = 1;
        graph[heavy][light] = -1;
        // light -> heavy 1 가중치
        // heavy -> light -1 가중치
    }

    // bigger 구하기
    bflag = true;
    for (int i = 1; i <= N; i++) {
        memset(visited, false, sizeof(visited));
        dfs(i, i);
    }

    // smaller 구하기
    bflag = false;
    for (int i = 1; i <= N; i++) {
        memset(visited, false, sizeof(visited));
        dfs(i, i);
    }
    
    // for (int i = 1; i <= N; i++) {
    //     cout << i << " : " << bigger[i] << ", " << smaller[i] <<"\n";
    // }
    int mid = (N - 1) / 2;
    // cout << "mid : " << mid << "\n";
    memset(visited, false, sizeof(visited));
    for (int i = 1; i <= N; i++) {
        if (bigger[i] > mid || smaller[i] > mid) visited[i] = true; 
    }

    for (int i = 1; i <= N; i++){
        if (visited[i]) ans++;
    }

    cout << ans;
    return 0;
}