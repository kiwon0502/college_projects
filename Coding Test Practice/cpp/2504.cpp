#include <iostream>
#include <stack>
#include <string>
using namespace std;

stack<char> st;
bool imp;
int ans;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    string s; cin>>s;
    int temp = 1;

    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '(') {
            temp *= 2;
            st.push(s[i]);
        }
        else if (s[i] == '[') {
            temp *= 3;
            st.push(s[i]);
        }
        else if ((s[i] == ')' && (st.empty() || st.top() != '(')) || (s[i] == ']' && (st.empty() || st.top() != '['))) {
            imp = true;
            break;
        }
        else if (s[i] == ')') {
            if (s[i - 1] == '(') ans += temp;
            st.pop();
            temp /= 2;
        }
        else if (s[i] == ']') {
            if (s[i - 1] == '[') ans += temp;
            st.pop();
            temp /= 3;
        }
    }
    if (imp || !st.empty()) cout<<"0";
    else cout<<ans;
    return 0;
}