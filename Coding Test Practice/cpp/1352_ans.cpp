#include <iostream>
#include <vector>
#include <stack>
#include <cstring>
#include <queue>

using namespace std;

bool dp[101][101];
stack<int> v;
stack<int> s;
queue<char> q;
int N; 

bool solve(int n, int k){
    if(k > N) return false;
    if(k == N) return true;
    if(dp[n][k]) return false;
    dp[n][k] = 1;
    for(int i=k+1; i>=n; i--){
        s.push(i);
        if(solve(i+1, k+i)) return true;
        s.pop();
    }
    return false;
}

int main(void){
    cin>>N;
    if(N==0){ cout<<""<<endl; return 0;}
    int n = 0;
    solve(1,0);
    string anw = "";
    while(!s.empty()){
        int n = s.top();
        s.pop();
        v.push(n);
    }
    if(v.empty()) {cout<<-1<<endl; return 0;}
    char c = 'A';
    for(int i=1; i<=N; i++){
        if(!v.empty() && v.top() == i){
            for(int j=0; j<i-1; j++) q.push(c);
            anw += c;
            c++; v.pop();
        }else{
            anw += q.front();
            q.pop();
        }
    }
    cout<<anw<<endl;
}