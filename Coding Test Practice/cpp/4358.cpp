#include <iostream>
#include <map>
#include <string>
using namespace std;

map<string, double> tree;
int total;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    string ss;
    while(getline(cin, ss)) {
        total++;
        tree[ss]++;
    }

    cout<<fixed;
    cout.precision(4);

    for (auto iter = tree.begin(); iter != tree.end(); iter++) {
        string name = iter->first;
        double n = (iter->second / total) * 100;
        cout<<name<<" "<<n<<"\n";
    }
    return 0;
}