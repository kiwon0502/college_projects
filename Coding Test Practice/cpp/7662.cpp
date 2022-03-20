#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
#define endl '\n'

priority_queue<pair<int, int>> max_heap;
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> min_heap;
bool valid[1000001];
int T, k;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>T;
    for (int i = 0; i < T; i++) {
        cin>>k;
        memset(valid, false, sizeof(valid));
        for (int j = 0; j < k; j++) {
            char a; cin>>a;
            int x; cin>>x;

            if (a == 'I') {
                min_heap.push({x, j});
                max_heap.push({x, j});
                valid[j] = true;
            }
            else {
                if (x > 0) {
                    while (!max_heap.empty() && !valid[max_heap.top().second]) max_heap.pop();
                    if (!max_heap.empty()) {
                        valid[max_heap.top().second] = false;
                        max_heap.pop();
                    }
                }
                else {
                    while (!min_heap.empty() && !valid[min_heap.top().second]) min_heap.pop();
                    if (!min_heap.empty()) {
                        valid[min_heap.top().second] = false;
                        min_heap.pop();
                    }
                }
            }
        }
        while (!max_heap.empty() && !valid[max_heap.top().second]) max_heap.pop();
        while (!min_heap.empty() && !valid[min_heap.top().second]) min_heap.pop();
        if (max_heap.empty()) cout<<"EMPTY"<<endl;
        else {
            cout<<max_heap.top().first<<" "<<min_heap.top().first<<endl;
        }
    }
    return 0;
}