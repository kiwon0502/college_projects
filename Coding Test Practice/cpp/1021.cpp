#include <iostream>
#include <deque>
#include <algorithm>
using namespace std;

int N, M, ans, q, mov;
deque<int> dq;

int find_idx(int target) {
    for (int i=0; i<N; i++) {
        if (dq[i] == target) {
            return i;
        }
    }
    return -1;
}

void act2() {
    for (int i=0; i<mov; i++) {
        int temp = dq[0];
        dq.push_back(temp);
        dq.pop_front();
    }
}

void act3() {
    for (int i=0; i<mov; i++) {
        int temp = dq[N-1];
        dq.push_front(temp);
        dq.pop_back();
    }
}

void show() {
    for (int i=0; i<N; i++) {
        cout<<dq[i]<<" ";
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>N>>M;

    for (int i=1; i<=N; i++) {
        dq.push_back(i);
    }

    for (int i=0; i<M; i++) {
        cin>>q;
        int idx = find_idx(q);
        mov = 0;
        if (idx == 0) {
            dq.pop_front();
            N--;
        }
        else if (idx <= (int(N/2))) {
            mov = idx;
            act2();
            dq.pop_front();
            N--;
            ans += mov;
        }
        else {
            mov = N - idx;
            act3();
            dq.pop_front();
            N--;
            ans += mov;
        }
    }
    cout<<ans;
    return 0;
}