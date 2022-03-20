#include <iostream>
using namespace std;
#define MAX 100001
int n;
int inorder[MAX], postorder[MAX], Index[MAX];

void solve(int is, int ie, int ps, int pe) {
    if (is > ie || ps > pe) return;
    int rootIndex = Index[postorder[pe]];
    int leftSize = rootIndex - is;
    int rightSize = ie - rootIndex;
    cout << inorder[rootIndex] << " ";

    solve(is, rootIndex - 1, ps, ps + leftSize - 1);
    solve(rootIndex + 1, ie, ps + leftSize, pe - 1);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> inorder[i];
        Index[inorder[i]] = i;
    }
    for (int i = 1; i <= n; i++) cin >> postorder[i];
    solve(1, n, 1, n);
    return 0;
}
