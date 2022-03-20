#include <iostream>
using namespace std;
#define MAX 110

int N, M, farm[MAX][MAX];
int dr[] = {1, -1, 0, 0, 1, 1, -1, -1};
int dc[] = {0, 0, 1, -1, 1, -1, 1, -1};
bool visited[MAX][MAX];
bool isPeak;
int anw;

void DFS(int r, int c) {
    for (int i = 0; i < 8; i++) {
        int nr = r + dr[i], nc = c + dc[i];
        if (nr < 0 || nc < 0 || nr >= N || nc >= M) continue;

        if (farm[r][c] < farm[nr][nc]) isPeak = false;

        if (visited[nr][nc] || farm[r][c] != farm[nr][nc]) continue;
        visited[nr][nc] = true;
        DFS(nr, nc);
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> farm[i][j];
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (!visited[i][j]) {
                isPeak = true;
                DFS(i, j);
                if (isPeak) anw++;
            }
        }
    }

    cout << anw;    
    return 0;
}
