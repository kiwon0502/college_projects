#include <iostream>
using namespace std;
#define MAX 10

int N, M;
int pArr[MAX];
bool check[MAX];

void print() {
    for (int i = 0; i < M; i++) cout << pArr[i] << " ";
    cout << "\n";
}

void permutation(int depth) {
    if (depth == M) {
        print();
        return;
    }

    for (int i= 1; i <= N; i++) {
        if (!check[i]) {
            check[i] = true;
            pArr[depth] = i;
            permutation(depth + 1);
            check[i] = false;
        }
    }
}

void duplicatePermuation(int depth) {
    if (depth == M) {
        print();
        return;
    }

    for (int i = 1; i <= N; i++) {
        pArr[depth] = i;
        duplicatePermuation(depth + 1);
    }
}

void combination(int depth, int next) {
    if (depth == M) {
        print();
        return;
    }

    for (int i = next; i <= N; i++) {
        pArr[depth] = i;
        combination(depth + 1, i + 1);
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M;
    permutation(0);
    //duplicatePermuation(0);
    //combination(0, 1);
    return 0;
}
