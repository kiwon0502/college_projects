#include <iostream>
#include <algorithm>
#include <string>
#include <map>
using namespace std;

map<string, int> book;
int N, best_sell;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    for (int i = 0; i < N; i++) {
        string name; cin >> name;
        if (!book.count(name)) book[name] = 1;
        else book[name]++;
    }
    for (auto it = book.begin(); it != book.end(); it++) best_sell = max(best_sell, it->second);
    for (auto it = book.begin(); it != book.end(); it++) {
        if (it->second == best_sell) {cout << it->first; return 0;}
    }
}
