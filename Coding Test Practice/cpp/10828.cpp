#include <iostream>
#include <string>
#include <stack>
typedef long long ll;
using namespace std;

stack<int> st;
int N, X;
string s;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>N;
    for (int t = 0; t < N; t++) {
        cin>>s;
        if (s == "push") {
            cin>>X;
            st.push(X);
        }
        else if (s == "pop") {
            if (st.empty()) cout<<"-1\n";
            else {
                X = st.top();
                st.pop();
                cout<<X<<"\n";
            }
        }
        else if (s == "size") {
            cout<<st.size()<<"\n";
        }
        else if (s == "empty") {
            if (st.empty()) cout<<"1\n";
            else cout<<"0\n";
        }
        else {
            if (st.empty()) cout<<"-1\n";
            else cout<<st.top()<<"\n";
        }
    }
    return 0;
}