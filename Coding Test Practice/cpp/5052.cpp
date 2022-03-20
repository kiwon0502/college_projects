#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

#define LEN_MAX 11
#define N_MAX 10010
#define NODE_MAX N_MAX * LEN_MAX

struct TRIE {
    bool finish;
    TRIE* Node[LEN_MAX];
    void Insert(char *str) {

    }
    bool Call(char *str);
};

int t, n;




int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> t;
    while (t--) {
        cin >> n;
        

    }
    return 0;
}
