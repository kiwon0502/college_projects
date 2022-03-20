#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
using namespace std;

int N;
vector<pair<int, int>> kr;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    for (int i = 1; i <= 2; i++) {
        string x; cin>>x;
        kr.push_back({57 - x[1], x[0] - 64});
    }
    cin>>N;

    for (int t = 0; t < N; t++) {
        int nr, nc, rnr, rnc;
        string move; cin>>move;

        if (move == "R") {
            nr = kr[0].first;
            nc = kr[0].second + 1;
            if (0 >= nr || nr > 8 || 0 >= nc || nc > 8) continue;
            if (nr == kr[1].first && nc == kr[1].second) {
                rnr = kr[1].first;
                rnc = kr[1].second + 1;
                if (0 >= rnr || rnr > 8 || 0 >= rnc || rnc > 8) continue;
                kr[1].first = rnr;
                kr[1].second = rnc;
            }
            kr[0].first = nr;
            kr[0].second = nc;
        }
        else if (move == "L") {
            nr = kr[0].first;
            nc = kr[0].second - 1;
            if (0 >= nr || nr > 8 || 0 >= nc || nc > 8) continue;
            if (nr == kr[1].first && nc == kr[1].second) {
                rnr = kr[1].first;
                rnc = kr[1].second - 1;
                if (0 >= rnr || rnr > 8 || 0 >= rnc || rnc > 8) continue;
                kr[1].first = rnr;
                kr[1].second = rnc;
            }
            kr[0].first = nr;
            kr[0].second = nc;
        }
        else if (move == "B") {
            nr = kr[0].first + 1;
            nc = kr[0].second;
            if (0 >= nr || nr > 8 || 0 >= nc || nc > 8) continue;
            if (nr == kr[1].first && nc == kr[1].second) {
                rnr = kr[1].first + 1;
                rnc = kr[1].second;
                if (0 >= rnr || rnr > 8 || 0 >= rnc || rnc > 8) continue;
                kr[1].first = rnr;
                kr[1].second = rnc;
            }
            kr[0].first = nr;
            kr[0].second = nc;
        }
        else if (move == "T") {
            nr = kr[0].first - 1;
            nc = kr[0].second;
            if (0 >= nr || nr > 8 || 0 >= nc || nc > 8) continue;
            if (nr == kr[1].first && nc == kr[1].second) {
                rnr = kr[1].first - 1;
                rnc = kr[1].second;
                if (0 >= rnr || rnr > 8 || 0 >= rnc || rnc > 8) continue;
                kr[1].first = rnr;
                kr[1].second = rnc;
            }
            kr[0].first = nr;
            kr[0].second = nc;
        }
        else if (move == "RT") {
            nr = kr[0].first - 1;
            nc = kr[0].second + 1;
            if (0 >= nr || nr > 8 || 0 >= nc || nc > 8) continue;
            if (nr == kr[1].first && nc == kr[1].second) {
                rnr = kr[1].first - 1;
                rnc = kr[1].second + 1;
                if (0 >= rnr || rnr > 8 || 0 >= rnc || rnc > 8) continue;
                kr[1].first = rnr;
                kr[1].second = rnc;
            }
            kr[0].first = nr;
            kr[0].second = nc;
        }
        else if (move == "LT") {
            nr = kr[0].first - 1;
            nc = kr[0].second - 1;
            if (0 >= nr || nr > 8 || 0 >= nc || nc > 8) continue;
            if (nr == kr[1].first && nc == kr[1].second) {
                rnr = kr[1].first - 1;
                rnc = kr[1].second - 1;
                if (0 >= rnr || rnr > 8 || 0 >= rnc || rnc > 8) continue;
                kr[1].first = rnr;
                kr[1].second = rnc;
            }
            kr[0].first = nr;
            kr[0].second = nc;
        }
        else if (move == "RB") {
            nr = kr[0].first + 1;
            nc = kr[0].second + 1;
            if (0 >= nr || nr > 8 || 0 >= nc || nc > 8) continue;
            if (nr == kr[1].first && nc == kr[1].second) {
                rnr = kr[1].first + 1;
                rnc = kr[1].second + 1;
                if (0 >= rnr || rnr > 8 || 0 >= rnc || rnc > 8) continue;
                kr[1].first = rnr;
                kr[1].second = rnc;
            }
            kr[0].first = nr;
            kr[0].second = nc;
        }
        else if (move == "LB") {
            nr = kr[0].first + 1;
            nc = kr[0].second - 1;
            if (0 >= nr || nr > 8 || 0 >= nc || nc > 8) continue;
            if (nr == kr[1].first && nc == kr[1].second) {
                rnr = kr[1].first + 1;
                rnc = kr[1].second - 1;
                if (0 >= rnr || rnr > 8 || 0 >= rnc || rnc > 8) continue;
                kr[1].first = rnr;
                kr[1].second = rnc;
            }
            kr[0].first = nr;
            kr[0].second = nc;            
        }
    }
    cout<<(char)(kr[0].second + 64)<<(char)(57 - kr[0].first)<<endl;
    cout<<(char)(kr[1].second + 64)<<(char)(57 - kr[1].first)<<endl;

    return 0;
}