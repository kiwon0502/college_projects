#include <iostream>
#define MAX 10101
using namespace std;

int N, Q[MAX];
string cmd;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>N;
    int head = 1, tail = 1;
    while(N--) {
        cin>>cmd;
        if (cmd == "push") {
            cin>>Q[tail++];
        }
        else if (cmd == "pop") {
            cout<<(tail - head > 0 ? Q[head++] : -1)<<"\n";
        }
        else if (cmd == "size") {
            cout<<(tail - head)<<"\n";
        }
        else if (cmd == "empty") {
            cout<<(tail - head > 0 ? 0 : 1)<<"\n";
        }
        else if (cmd == "front") {
            cout<<(tail - head > 0 ? Q[head] : -1)<<"\n";
        }
        else {
            cout<<(tail - head > 0 ? Q[tail - 1] : -1)<<"\n";
        }
    }
    return 0;
}