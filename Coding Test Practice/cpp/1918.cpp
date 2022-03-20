#include <iostream>
#include <stack>
#include <string>
using namespace std;

string in;
stack<char> st;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> in;
    for (int i = 0; i < in.size(); i++) {
        if (in[i] >= 'A' && in[i] <= 'Z') {
            cout << in[i];
        }
        else {
            switch (in[i]) {
                case '(':
                    st.push('(');
                    break;

                case '*':
                case '/':
                    while (!st.empty() && (st.top() == '*' || st.top() == '/')) {
                        cout << st.top();
                        st.pop();
                    }
                    st.push(in[i]);
                    break;

                case '+':
                case '-':
                    while (!st.empty() && st.top() != '(') {
                        cout << st.top();
                        st.pop();
                    }
                    st.push(in[i]);
                    break;

                case ')':
                    while (!st.empty() && st.top() != '(') {
                        cout << st.top();
                        st.pop();
                    }
                    st.pop();
                    break;
            }
        }
    }
    while (!st.empty()) {
        cout << st.top();
        st.pop();
    }
    return 0;
}