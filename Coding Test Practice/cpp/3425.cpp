#include <iostream>
#include <algorithm>
#include <cmath>
#include <stack>
#include <cstring>
#define upper_bound pow(10, 9)

typedef long long ll;
using namespace std;

stack<ll> St;
string s;
pair<int, ll> func[100001];

bool NUM(ll x) {
    if (x >= upper_bound) return false;
    St.push(x); return true;
}
bool POP() {
    if (St.empty()) return false;

    St.pop(); return true;
}
bool INV() {
    if (St.empty()) return false;

    ll tp = St.top() * (-1);
    St.pop();
    St.push(tp); return true;
}
bool DUP() {
    if (St.empty()) return false;

    ll tp = St.top();
    St.push(tp); return true;
}
bool SWP() {
    if (St.size() < 2) return false;

    ll first = St.top();
    St.pop();
    ll second = St.top();
    St.pop();

    St.push(first);
    St.push(second); return true;
}
bool ADD() {
    if (St.size() < 2) return false;

    ll first = St.top();
    St.pop();
    ll second = St.top();
    St.pop();
    ll sum = first + second;

    if (abs(sum) >= upper_bound) return false;
    St.push(sum); return true;
}
bool SUB() {
    if (St.size() < 2) return false;

    ll first = St.top();
    St.pop();
    ll second = St.top();
    St.pop();
    ll gap = second - first;

    if (abs(gap) >= upper_bound) return false;
    St.push(gap); return true;
}
bool MUL() {
    if (St.size() < 2) return false;

    ll first = St.top();
    St.pop();
    ll second = St.top();
    St.pop();
    ll times = first * second;

    if (abs(times) >= upper_bound) return false;
    St.push(times); return true;
}
bool DIV() {
    if (St.size() < 2) return false;

    ll first = St.top();
    St.pop();
    ll second = St.top();
    St.pop();

    if (first == 0) return false;
    St.push(second/first); return true;
}
bool MOD() {
    if (St.size() < 2) return false;

    ll first = St.top();
    St.pop();
    ll second = St.top();
    St.pop();

    if (first == 0) return false;
    St.push(second%first); return true;
}

void do_fuc(int f, ll x) {
    switch(f) {
        case 0:
            NUM(x); break;
        case 1:
            POP(); break;
        case 2:
            INV(); break;
        case 3:
            DUP(); break;
        case 4:
            SWP(); break;
        case 5:
            ADD(); break;
        case 6:
            SUB(); break;
        case 7:
            MUL(); break;
        case 8:
            DIV(); break;
        case 9:
            MOD(); break;
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    bool quit_signal = false;
    while(!quit_signal) {
        memset(func, -1, sizeof(func)); int func_len = 0;
        while(true) {
            cin>>s;
            if (s == "QUIT") {quit_signal = true; break;}
            else if (s == "END") {
                // 프로그램 실행
                int N; cin>>N;
                for (int i = 0; i < N; i++) {
                    ll start; cin>>start;

                }
            }
            else if (s == "NUM") {
                ll x; cin>>x;
                func[func_len++] = {0, x};
            }                
            else if (s == "POP") func[func_len++] = {1, -1};
            else if (s == "INV") func[func_len++] = {2, -1};
            else if (s == "DUP") func[func_len++] = {3, -1};
            else if (s == "SWP") func[func_len++] = {4, -1};
            else if (s == "ADD") func[func_len++] = {5, -1};
            else if (s == "SUB") func[func_len++] = {6, -1};
            else if (s == "MUL") func[func_len++] = {7, -1};
            else if (s == "DIV") func[func_len++] = {8, -1};
            else if (s == "MOD") func[func_len++] = {9, -1};
            func_len++;
        }
    }
    return 0;
}