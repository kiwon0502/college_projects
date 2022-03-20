#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int N, M, dist;
vector<pair<int, int>> home;
vector<pair<int, int>> chick;
bool Select[14];

int get_distance(int h_idx, int c_idx) {
    return abs(home[h_idx].first - chick[c_idx].first) + abs(home[h_idx].second - chick[c_idx].second);
}

int cal_dist() {
    int city_distance = 0;
    for (int i = 0; i < home.size(); i++) {
        int c_dist = 6974;
        for (int j = 0; j < chick.size(); j++) {
            if (Select[j]) c_dist = min(c_dist, get_distance(i, j));
        }
        city_distance += c_dist;
    }
    return city_distance;
}

void dfs(int idx, int cnt) {
    if (cnt == M) {
        dist = min(dist, cal_dist());
        return;
    }

    for (int i = idx; i < chick.size(); i++) {
        if (Select[i] == true) continue;
        Select[i] = true;

        dfs(i, cnt + 1);
        Select[i] = false;
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>N>>M;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            int n; cin>>n;
            if (n == 1) home.push_back({i, j});
            else if (n == 2) chick.push_back({i, j});
        }
    }
    dist = 6974;
    dfs(0, 0);
    cout<<dist;
    return 0;
}