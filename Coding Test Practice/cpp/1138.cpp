#include <iostream>
#include <cstring>
using namespace std;
int N;
int bigger[11];
int order[10];

int main() {
    memset(order, -1, sizeof(order));
    cin>>N;
    for (int i = 1; i <= N; i++)
        cin>>bigger[i];

    for (int i = 1; i <= N; i++) {
        int cnt = -1;
        for (int j = 0; j < N; j++) {
            if (order[j] == -1) cnt++;
            if (cnt == bigger[i]) {
                order[j] = i;
                break;
            }
        }
    }

    for (int i = 0; i < N; i++)
        cout<<order[i]<<" ";
    return 0;
}