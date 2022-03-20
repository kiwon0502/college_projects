#include <iostream>
#include <algorithm>
#define MAX 100005
using namespace std;

int N, heap[MAX], heap_size;

void push(int x) {
    heap[++heap_size] = x;
    int child = heap_size, parent = child / 2;
    
    while (child > 1 && heap[parent] < heap[child]) {
        swap(heap[parent], heap[child]);
        child = parent;
        parent = child / 2;
    }
}

int pop() {
    int res = heap[1];
    swap(heap[1], heap[heap_size--]);

    int parent = 1, child = parent * 2;
    if (child + 1 <= heap_size) child = (heap[child] > heap[child + 1] ? child : child + 1);

    while (child <= heap_size && heap[parent] < heap[child]) {
        swap(heap[parent], heap[child]);
        parent = child;
        child = parent * 2;

        if (child + 1 <= heap_size) child = (heap[child] > heap[child + 1] ? child : child + 1);
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>N;
    while (N--) {
        int x; cin>>x;
        if (!x) {
            if (!heap_size) cout<<"0\n";
            else cout<<pop()<<"\n";
        }
        else push(x);
    }
    return 0;
}