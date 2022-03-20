#include <iostream>
#include <queue>
using namespace std;

int N, M, V;
int** graph;
bool* visited;
queue<int> forBFS;

void dfs(int start) {
    visited[start-1] = true;
    cout<<start<<" ";

    for (int i=0; i<N; i++) {
        if (graph[start-1][i] == 1 && visited[i] == false) {
            dfs(i+1);
        }
    }
}

void bfs(int start) {
    forBFS.push(start-1);
    while(!forBFS.empty()) {
        int tag = forBFS.front();
        forBFS.pop();
        
        if (visited[tag] == false) {
            cout<<(tag + 1)<<" ";
            visited[tag] = true;

            for (int i=0; i<N; i++) {
                if (graph[tag][i] == 1 && visited[i] == false) {
                    forBFS.push(i);
                }
            }
        }
    }
}

int main() {
    cin>>N>>M>>V;
    graph = new int*[N];
    for (int i=0; i<N; i++) {
        graph[i] = new int[N];
    }
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            graph[i][j] = 0;
        }
    }
    visited = new bool[N];

    int a, b;
    for (int i=0; i<M; i++) {
        cin>>a>>b;
        graph[a-1][b-1] = 1;
        graph[b-1][a-1] = 1;
    }

    // 방문 노드들을 모두 false로 초기화
    for (int i=0; i<N; i++) {
        visited[i] = false;
    }
    dfs(V);
    cout<<endl;

    // 방문 노드들을 모두 false로 초기화
    for (int i=0; i<N; i++) {
        visited[i] = false;
    }
    bfs(V);

    for (int i=0; i<N; i++) {
        delete[] graph[i];
    }
    delete[] graph;
    delete[] visited;
    return 0;
}