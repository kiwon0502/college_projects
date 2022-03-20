#include <iostream>
using namespace std;

int** ground;
int N, M, B;

int main() {
    cin>>N>>M>>B;
    ground = new int*[N];
    for (int i=0; i<N; i++) {
        ground[i] = new int[M];
    }

    for (int i=0; i<N; i++) {
        for (int j=0; j<M; j++) {
            cin>>ground[i][j];
        }
    }


    for (int i=0; i<N; i++) {
        delete[] ground[i];
    }
    delete[] ground;
    return 0;
}