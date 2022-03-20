#include <iostream>
using namespace std;
#define INF 987654321;

int** dist;
int* near;
int N, M;

void floyd(){
    for (int mid=0; mid<N; mid++){
        for (int start=0; start<N; start++){
            for (int end=0; end<N; end++){
                if (dist[start][end] > dist[start][mid] + dist[mid][end]){
                    // 더 가까운 경로가 있을 경우 최신화
                    dist[start][end] = dist[start][mid] + dist[mid][end];                    
                }
            }
        }
    }
}

int main() {
    cin>>N>>M;
    dist = new int*[N];
    for (int i=0; i<N; i++) {
        dist[i] = new int[N];
    }
    near = new int[N];

    // 초기화
    // dist : 각 정점에서 다른 정점까지의 최단 거리 // 초기에는 직접적으로 연결되어 있지 않는 경우 INF
    // near : 케빈 베이컨의 수
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            if (i == j) dist[i][j] = 0;
            else dist[i][j] = INF;
        }
        near[i] = 0;
    }

    for (int i=0; i<M; i++) {
        int a, b;
        cin>>a>>b;
        dist[a-1][b-1] = 1;
        dist[b-1][a-1] = 1;
    }

    floyd();
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            near[i] += dist[i][j];
        }
    }
    int temp = near[0];
    int lowest = 1;
    for (int i=1; i<N; i++) {
        if (temp > near[i]) {
            temp = near[i];
            lowest = i+1;
        }
    }
    cout<<lowest<<endl;

    for (int i=0; i<N; i++) {
        delete[] dist[i];
    }
    delete[] dist;
    delete[] near;
    return 0;
}