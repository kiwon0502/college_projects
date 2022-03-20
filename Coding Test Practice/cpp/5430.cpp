#include <iostream>
#include <string>
using namespace std;
int T;
string ans[101];

class Node {
public:
    Node(const int data, Node* prev = nullptr, Node* next = nullptr) {
        this->data = data;
        this->prev = prev;
        this->next = next;
    }
    int getData() const {
        return data;
    }
    Node* getPrev() const {
        return prev;
    }
    Node* getNext() const {
        return next;
    }
    void setData(const int data) {
        this->data = data;
    }
    void setPrev(Node* node) {
        this->prev = node;
    }
    void setNext(Node* node) {
        this->next = node;
    }
private:
    int data;
    Node* prev;
    Node* next;
};

class List {
public:
    List() {
        headNode = nullptr;
        tailNode = nullptr;
        dataSize = 0;
        rflag = false;
    }
    ~List() {
        while (!empty()) {
            popFront();
        }
    }

    bool empty() const {
        return dataSize == 0;
    }
    int size() const {
        return dataSize;
    }
    void pushBack(const int data) {
        if (empty()) {
            headNode = tailNode = new Node(data);
            dataSize++;
            return;
        }
        Node* node = new Node(data, tailNode, nullptr);
        tailNode->setNext(node);
        tailNode = node;
        dataSize++;
    }
    bool popFront() {
        if (dataSize == 0) return true;

        Node* node = headNode;
        headNode = headNode->getNext();
        if (headNode != nullptr) {
            headNode->setPrev(nullptr);
        }
        delete node;
        dataSize--;
        return false;
    }
    bool popBack() {
        if (dataSize == 0) return true;
        
        Node* node = tailNode;
        tailNode = tailNode->getPrev();
        if (tailNode != nullptr) {
            tailNode->setNext(nullptr);
        }
        delete node;
        dataSize--;
        return false;
    }
    void reverse() {
        rflag = !rflag;
    }
    bool getFlag() {
        return rflag;
    }
    void showinorder(int t) {
        string answer = "";
        answer += "[";
        for (Node* node = headNode; node != tailNode; node = node->getNext()) {
            answer += to_string(node->getData()) + ",";
        }
        answer += to_string(tailNode->getData()) + "]";
        ans[t] = answer;
    }
    void showreverse(int t) {
        string answer = "";
        answer += "[";
        for (Node* node = tailNode; node != headNode; node = node->getPrev()) {
            answer += to_string(node->getData()) + ",";
        }
        answer += to_string(headNode->getData()) + "]";
        ans[t] = answer;     
    }

private:
    Node* headNode;
    Node* tailNode;
    int dataSize;
    bool rflag;
};

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>T;
    for (int t = 0; t < T; t++) {
        List* X = new List();
        string p; cin>>p;               // 수행할 함수
        int size; cin>>size;            // 배열 원소 개수
        bool errorflag = false;

        string l; cin>>l;
        l = l.substr(1, l.length() - 2);
        if (l.length() != 0) {
            int previous = 0;
            int current = 0;
            string substring;

            current= l.find(',');
            //find는 찾을게 없으면 npos를 리턴함
            while(current != string::npos){
                substring = l.substr(previous, current - previous);
                X->pushBack(stoi(substring));
                previous = current + 1;
                current = l.find(',', previous);
            }
            substring = l.substr(previous, current - previous);
            X->pushBack(stoi(substring));
        }

        for (int i = 0; i < p.length(); i++) {
            switch(p[i]) {
                case 'R':
                    X->reverse();
                    break;
                case 'D':
                    if (X->getFlag()) errorflag = X->popBack();
                    else errorflag = X->popFront();
                    break;
            }
            if (errorflag) break;
        }
        if (errorflag) {
            ans[t] = "error";
            continue;
        }
        if (X->getFlag()) X->showreverse(t);
        else X->showinorder(t);
    }

    for (int t = 0; t < T; t++)
        cout<<ans[t]<<endl;

    return 0;
}
