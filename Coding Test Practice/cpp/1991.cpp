#include <iostream>
using namespace std;

struct Node {
    int left;
    int right;
};

Node nodes[27];
int N;

void preorder(int idx) {
    if (idx == ('.' - 'A')) return;
    cout<<char(idx + 'A');
    preorder(nodes[idx].left);
    preorder(nodes[idx].right);
}

void inorder(int idx) {
    if (idx == ('.' - 'A')) return;
    inorder(nodes[idx].left);
    cout<<char(idx + 'A');
    inorder(nodes[idx].right);
}

void postorder(int idx) {
    if (idx == ('.' - 'A')) return;
    postorder(nodes[idx].left);
    postorder(nodes[idx].right);
    cout<<char(idx + 'A');
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>N;
    for (int i = 0; i < N; i++) {
        char node, l, r; cin>>node>>l>>r;
        nodes[node - 'A'].left = l - 'A';
        nodes[node - 'A'].right = r - 'A';
    }
    preorder(0);
    cout<<"\n";
    inorder(0);
    cout<<"\n";
    postorder(0);
    return 0;
}