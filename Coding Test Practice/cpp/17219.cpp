#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

#define MAX 100000;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, M;
    cin>>N>>M;

    vector<pair<string, string>> v(N);
    for (int i=0; i<N; i++) {
        cin>>v[i].first>>v[i].second;
    }
    sort(v.begin(), v.end());

    for (int i=0; i<M; i++) {
        string s;
        cin>>s;

        int low = 0, high = N-1;
        while (low<=high) {
            int mid = (low + high) / 2;
            if (v[mid].first == s) {
                cout<<v[mid].second<<"\n";
                break;
            }
            else if (v[mid].first < s) {
                low = mid + 1;
            }
            else {
                high = mid - 1;
            }
        }
    }
    return 0;
}