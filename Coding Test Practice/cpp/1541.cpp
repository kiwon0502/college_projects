#include <iostream>
#include <cstdlib>
#include <string>
#include <stack>
#include <cmath>
using namespace std;

stack<int> maxMinus;
int result, num;
bool minusflag = false;
string d;

int main() {
    cin>>d;
    int length = d.length();
    result = 0;
    int index = 0;
    for (int i=0; i<length; i++) {
        if (d[i] == '+') {
            int len = i - index;
            num = atoi(d.substr(index, len).c_str());
            if (minusflag) {
                maxMinus.push(num);
            }
            else {
                result += num;
            }
            index = i + 1;
        }
        else if (d[i] == '-') {
            int len = i - index;
            num = atoi(d.substr(index, len).c_str());
            if (minusflag) {
                int minusSum = num;
                while (!maxMinus.empty()) {
                    int temp = maxMinus.top();
                    minusSum += temp;
                    maxMinus.pop();
                }
                result -= minusSum;
            }
            else {
                minusflag = true;
                result += num;
            }
            index = i + 1;
        }
        else if (i == length - 1) {
            int len = i - index + 1;
            num = atoi(d.substr(index, len).c_str());
            if (minusflag) {
                int minusSum = num;
                while (!maxMinus.empty()) {
                    int temp = maxMinus.top();
                    minusSum += temp;
                    maxMinus.pop();
                }
                result -= minusSum;
            }
            else {
                result += num;
            }
        }
    }
    cout<<result<<endl;
    return 0;
}