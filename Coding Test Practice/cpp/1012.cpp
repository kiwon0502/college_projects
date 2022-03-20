#include <iostream>
using namespace std;

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};
int** field;
bool** visited;
int M, N, K;

void dfs (int x, int y) {
    int nx, ny;
    visited[x][y] = true;

    for (int i=0; i<4; i++) {
        nx = x + dx[i];
        ny = y + dy[i];
        if (nx >= 0 && nx < N && ny >= 0 && ny < M) {
            if (field[nx][ny] == 1 && visited[nx][ny] == false) {
                dfs(nx, ny);
            }
        }
   }
}

int main() {
    int T;
    cin>>T;     // 테스트 케이스 개수
    // 결과 출력용 변수 배열 설정
    int* result = new int[T];
    for (int i=0; i<T; i++) {
        result[i] = 0;
    }

    for (int i=0; i<T; i++) {
        // M: 배추밭의 가로 길이 // N: 배추밭의 세로 길이 // K: 배추가 심어져 있는 위치의 개수
        cin>>M>>N>>K;
        // 배추밭 배열 동적 할당    // 0으로 초기화
        // 방문 배열 동적 할당      // false로 초기화
        field = new int*[N];
        visited = new bool*[N];
        for (int j=0; j<N; j++) {
            field[j] = new int[M];
            visited[j] = new bool[M];
            for (int l=0; l<M; l++) {
                field[j][l] = 0;
                visited[j][l] = false;
            }
        }

        // 배추가 심어져 있는 부분 1로 설정
        for (int j=0; j<K; j++) {
            int a, b;
            cin>>a>>b;
            field[b][a] = 1;
        }

        for (int j=0; j<N; j++) {
            for (int l=0; l<M; l++) {
                if (field[j][l] == 1 && visited[j][l] == false) {
                    dfs(j, l);
                    result[i]++;
                }
            }
        }

        for (int j=0; j<N; j++) {       // free memory
            delete[] field[j];
            delete[] visited[j];
        }
        delete[] field;
        delete[] visited;
    }

    // 결과 출력
    for (int i=0; i<T; i++) {
        cout<<result[i]<<endl;
    }
    delete[] result;
    return 0;
}