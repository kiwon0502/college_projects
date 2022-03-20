#include <iostream>
#include <cmath>
#include <cctype>
using namespace std;

int X;
int* _min;

int main() {
    cin>>X;
    _min = new int[X+1];

    _min[1] = 0;
    for (int i=2; i<(X+1); i++) {
        if (i%2 == 0 && i%3 ==0) {
            _min[i] = _min[i-1] >= _min[i/2] ? (_min[i/2] >= _min[i/3] ? _min[i/3] : _min[i/2]) : (_min[i-1] >= _min[i/3] ? _min[i/3] : _min[i-1]);
            _min[i] += 1;
        }
        else if (i%2 == 0) {
            _min[i] = _min[i-1] >= _min[i/2] ? _min[i/2] : _min[i-1];
            _min[i] += 1;
        }
        else if (i%3 == 0) {
            _min[i] = _min[i-1] >= _min[i/3] ? _min[i/3] : _min[i-1];
            _min[i] += 1;
        }
        else {
            _min[i] = _min[i-1] + 1;
        }
    }
    cout<<_min[X]<<endl;
    delete[] _min;
    return 0;
}