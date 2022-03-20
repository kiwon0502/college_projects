#include <iostream>
#include <stack>
using namespace std;

bool solution(string input) {
    stack<char> st;
    for (int i = 0; i < input.size(); i++) {
        if (input[i] == '(' || input[i] == '[')  st.push(input[i]);
        else if (input[i] == ']') {
            if (!st.empty() && st.top() == '[') {st.pop(); continue;}
            return false;
        }
        else if (input[i] == ')') {
            if (!st.empty() && st.top() == '(') {st.pop(); continue;}
            return false;
        }
    }
    if (!st.empty()) return false;
    return true;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    while (1) {
        string input; getline(cin, input);
        if (input == ".") break;
        if (solution(input)) cout << "yes\n";
        else cout << "no\n";
    }
    return 0;
}
