#include <iostream>
#define MAX_SIZE 100001
using namespace std;

int n;
int heap[MAX_SIZE];
int heap_count = 0;

void swap(int* a, int* b) {
    int tmp = *a; *a = *b; *b = tmp;
}

void init() {
    heap_count = 0;
}

int size() {
    return heap_count;
}

void push(int data) {
    heap[++heap_count] = data;
    int child = heap_count;
    int parent = child / 2;
    while (child > 1 && heap[parent] < heap[child]) {
        swap(&heap[parent], &heap[child]);
        child = parent;
        parent = child / 2;
    }
}

int pop() {
    int result = heap[1];
    swap(&heap[1], &heap[heap_count]);
    heap_count--;

    int parent = 1;
    int child = parent * 2;
    if (child + 1 <= heap_count) {
        child = (heap[child] > heap[child + 1]) ? child : child + 1;
    }

    while (child <= heap_count && heap[parent] < heap[child]) {
        swap(&heap[parent], &heap[child]);

        parent = child;
        child = child * 2;
        if (child + 1 <= heap_count) {
            child = (heap[child] > heap[child + 1]) ? child : child + 1;
        }
    }
    return result;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    init();
    cin>>n;
    while (n-- > 0) {
        int x; cin>>x;
        if (x == 0) {
            if (!size()) cout<<"0\n";
            else cout<<pop()<<"\n";
        }
        else push(x);
    }
    return 0;
}