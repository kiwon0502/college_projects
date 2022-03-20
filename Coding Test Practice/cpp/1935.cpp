#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#define ll long long int
using namespace std;

int N;
double a, b;
stack<double> s;
string st;
double arr[26];

int ifop(char c) {
    if (c == '+') return 1;
    else if (c == '-') return 2;
    else if (c == '*') return 3;
    else if (c == '/') return 4;
    else return 0;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cout << fixed;
    cout.precision(2);
    cin>>N;
    cin>>st;
    for (int i = 0; i < N; i++) {
        cin>>arr[i];
    }

    for (int i = 0; i < st.length(); i++) {
        int op = ifop(st[i]);
        if (op == 0) {  // 알파벳
            s.push(arr[st[i] - 'A']);
        }
        else {
            b = s.top();
            s.pop();
            a = s.top();
            s.pop();
            switch(op) {
                case 1:
                    s.push(a + b);
                    break;
                case 2:
                    s.push(a - b);
                    break;
                case 3:
                    s.push(a * b);
                    break;
                case 4:
                    s.push(a / b);
                    break;
                default:
                    break;
            }
        }
    }
    cout<<s.top();
    return 0;
}