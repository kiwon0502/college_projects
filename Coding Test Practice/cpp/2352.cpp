#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int N;
vector<int> port;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    for (int i = 0; i < N; i++) {
        int input; cin >> input;
        if (port.empty() || port.back() < input) port.push_back(input);
        else *lower_bound(port.begin(), port.end(), input) = input;
    }

    cout << port.size();    
    return 0;
}
