#include <iostream>
using namespace std;

int ja1, mo1, ja2, mo2;
int ja_ans, mo_ans;

int uclid(int a, int b) {
    if (a < b) {
        int temp = a;
        a = b;
        b = temp;
    }
    if (b == 0) return a;
    return uclid(a%b, b);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> ja1 >> mo1 >> ja2 >> mo2;
    mo_ans = mo1 * mo2;
    ja_ans = ja1 * mo2 + ja2 * mo1;
    int gcd = uclid(mo_ans, ja_ans);
    cout << ja_ans / gcd << " " << mo_ans / gcd;
    return 0;
}