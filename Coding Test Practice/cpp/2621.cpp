#include <iostream>
#include <string.h>
using namespace std;

int num[5];
int sort[5];
char card[5];
int ans[9];
bool cases[8];

void bubbleSort() {
    int temp;
    for (int i=1; i<5; i++) {
        for (int j=0; j<5-i; j++) {
            if (sort[j] > sort[j+1]) {
                temp = sort[j];
                sort[j] = sort[j+1];
                sort[j+1] = temp;
            }
        }
    }
}

bool ifseuquential() {
    for (int i=0; i<4; i++) {
        if (sort[i+1] != sort[i] + 1) return false;
    }
    return true;
}

bool find4equal() {
    int count = 0;
    for (int i=1; i<5; i++) {
        if (num[0] == num[i]) count++;
    }
    if (count == 3) {
        ans[1] = num[0];
        return true;
    }
    else {
        for (int i=2; i<5; i++) {
            if (num[1] != num[i]) return false;
        }
        ans[1] = num[1];
        return true;
    }
    return false;
}

bool find32equal() {
    int count = 0;
    int index;
    for (int i=1; i<5; i++) {
        if (num[0] == num[i]) count++;
        else index = i;
    }
    if (count == 2) {
        count = 0;
        for (int i=1; i<5; i++) {
            if (index != i && num[index] == num[i]) count++;
        }
        if (count == 1) {
            ans[2] = num[0] * 10 + num[index] + 700;
            return true;
        }
        else return false;
    }
    else if (count == 1) {
        count = 0;
        for (int i=1; i<5; i++) {
            if (index != i && num[index] == num[i]) count++;
        }
        if (count == 2) {
            ans[2] = num[index] * 10 + num[0] + 700;
            return true;
        }
        else return false;
    }
    return false;
}

bool find3equal() {
    int count = 0;
    for (int i=1; i<5; i++) {
        if (num[0] == num[i]) count++;
    }
    if (count == 2) {
        ans[5] = num[0] + 400;
        return true;
    }
    else {
        count = 0;
        for (int i=2; i<5; i++) {
            if (num[1] == num[i]) count++;
        }
        if (count == 2) {
            ans[5] = num[1] + 400;
            return true;
        }
        else {
            count = 0;
            for (int i=3; i<5; i++) {
                if (num[2] == num[i]) count++;
            }
            if (count == 2) {
                ans[5] = num[2] + 400;
                return true;
            }
            else return false;

        }
    }
    return false;
}

bool find22equal() {
    int count = 0;
    for (int i=1; i<5; i++) {
        if (num[0] == num[i]) count++;
    }
    if (count == 1) {
        count = 0;
        for (int i=2; i<5; i++) {
            if (num[1] == num[i]) count++;
        }
        if (count == 1) {
            if (num[0] < num[1]) {
                ans[6] = num[1] * 10 + num[0] + 300;
                return true;
            }
            else {
                ans[6] = num[0] * 10 + num[1] + 300;
                return true;
            }
        }
        else {
            count = 0;
            for (int i=3; i<5; i++) {
                if (num[2] == num[i]) count++;
            }
            if (count == 1) {
                if (num[0] < num[2]) {
                    ans[6] = num[2] * 10 + num[0] + 300;
                    return true;
                }
                else {
                    ans[6] = num[0] * 10 + num[2] + 300;
                    return true;
                }
            }
            else {
                if (num[3] == num[4]) {
                    if (num[0] < num[3]) {
                        ans[6] = num[3] * 10 + num[0] + 300;
                        return true;
                    }
                    else {
                        ans[6] = num[0] * 10 + num[3] + 300;
                        return true;
                    }
                }
                else return false;
            }
        }
    }
    return false;
}

bool find2equal() {
    int count = 0;
    for (int i=1; i<5; i++) {
        if (num[0] == num[i]) count++;
    }
    if (count == 1) {
        ans[7] = num[0] + 200;
        return true;
    }
    else {
        count = 0;
        for (int i=2; i<5; i++) {
            if (num[1] == num[i]) count++;
        }
        if (count == 1){
            ans[7] = num[1] + 200;
            return true;
        }
        else {
            count = 0;
            for (int i=3; i<5; i++) {
                if (num[2] == num[i]) count++;
            }
            if (count == 1) {
                ans[7] = num[2] + 200;
                return true;
            }
            else {
                if (num[4] == num[5]) {
                    ans[7] = num[4] + 200;
                    return true;
                }
                else return false;
            }
        }
    }
    return false;
}

int main() {
    memset(cases, false, sizeof(bool) * 8);

    for (int i=0; i<9; i++) {
        ans[i] = 0;
    }

    for (int i=0; i<5; i++) {
        cin>>card[i]>>num[i];
    }

    for (int i=0; i<5; i++) {
        sort[i] = num[i];
    }
    bubbleSort();

    if (card[0] == card[1] && card[1] == card[2] && card[2] == card[3] && card[3] == card[4]) {
        bubbleSort();
        if (ifseuquential()) {
            cases[0] = true;
            ans[0] = sort[4] + 900;
        }
        cases[3] = true;
        ans[3] = sort[4] + 600;
    }
    if (find4equal()) {
        cases[1] = true;
        ans[1] += 800;
    }
    if (find32equal()) {
        cases[2] = true;
    }
    if (ifseuquential()) {
        cases[4] = true;
        ans[4] = sort[4] + 500;
    }
    if (find3equal()) {
        cases[5] = true;
    }

    if (find22equal()) {
        cases[6] = true;
    }
    else if (find2equal()) {
        cases[7] = true;
    }

    if (!cases[0] && !cases[1] && !cases[2] && !cases[3] && !cases[4] && !cases[5] && !cases[6] && !cases[7]) {
        ans[8] = sort[4] + 100;
    }

    int temp = ans[0];
    for (int i=1; i<9; i++) {
        if (temp < ans[i]) {
            temp = ans[i];
        }
    }
    // for (int i=0; i<9; i++) {
    //     cout<<cases[i]<<" ";
    // }
    // cout<<endl;
    cout<<temp<<endl;
    return 0;
}