#include <iostream>
#include <string>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int M;
    bool S[21];
    for (int i=0; i<21; i++) {
        S[i] = false;
    }
    cin>>M;
    for (int z=0; z<M; z++) {
        string action;
        int num;
        cin>>action;

        if (action == "add") {
            cin>>num;
            if (!S[num]) S[num] = true;
        }
        else if (action == "remove") {
            cin>>num;
            if (S[num]) S[num] = false;
        }
        else if (action == "check") {
            cin>>num;
            if (S[num]) cout<<"1\n";
            else cout<<"0\n";
        }
        else if (action == "toggle") {
            cin>>num;
            S[num] = !S[num];
        }
        else if (action == "all") {
            for (int i=1; i<21; i++) {
                S[i] = true;
            }
        }
        else if (action == "empty") {
            for (int i=1; i<21; i++) {
                S[i] = false;
            }
        }
    }
    return 0;
}