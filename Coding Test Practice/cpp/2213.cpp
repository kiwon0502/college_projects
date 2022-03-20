#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
#define ll long long int
using namespace std;

int n;
vector<int> weight;
vector<vector<int>> graph;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>n;
    for (int i = 0; i < n; i++) {
        int w; cin>>w;
        weight.push_back(w);
    }
    

    return 0;
}