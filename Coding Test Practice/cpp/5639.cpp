#include <iostream>
#define MAX 1000000
using namespace std;
int tree[MAX];

void postO(int start, int end) {
    if (start == end) return;           // 한 개도 없음
    else if (start == end - 1) {
        cout<< tree[start] << "\n"; return;      // 노드 1개
    }

    int idx = start + 1;
    while(1) {
        if ((idx < end && tree[idx] < tree[start]) == false) break;
        idx++;
    }

    postO(start + 1, idx);
    postO(idx, end);
    cout<< tree[start] <<"\n";   
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int idx;
    for (idx = 0; (cin>>tree[idx]); idx++);
    postO(0, idx);
    return 0;
}