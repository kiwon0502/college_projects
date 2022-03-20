#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
#define ll long long int
using namespace std;

int G, P;
int poss_Gate[10001];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>G>>P;
    for (int i = 1; i <= P; i++) {
        cin>>poss_Gate[i];
    }
    
    return 0;
}