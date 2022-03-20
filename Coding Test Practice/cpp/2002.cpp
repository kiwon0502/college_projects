#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#define ll long long int
using namespace std;

int N, ans;
map<string, int> in;
vector<string> out;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>N;
    for (int i = 0; i < N; i++) {
        string car; cin>>car;
        in.insert({car, i});
    }

    for (int i = 0; i < N; i++) {
        string car; cin>>car;
        out.push_back(car);
    }

    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (in[out[i]] > in[out[j]]) {ans++; break;}
        }
    }
    cout<<ans;
    return 0;
}