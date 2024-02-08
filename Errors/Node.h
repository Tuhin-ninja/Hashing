#include<bits/stdc++.h>
using namespace std;
#define ll long long 


bool isPrime(ll num){ 
    if (num <= 1) return false;
    if (num <= 3) return true;    
    if (num % 2 == 0 || num % 3 == 0) 
        return false;
    
    for (ll i = 5; i * i <= num; i += 6) 
        if (num % i == 0 || num % (i + 2) == 0) 
            return false;
            
    return true;

}


ll nextPrime(ll num){
    while (true) {
        if (isPrime(num))
            return num;
        num++;
    }
}

string RandomWord(long long length) {
    static const string alphabet = "abcdefghijklmnopqrstuvwxyz";
    long long alphabet_size = 26;
    string word;

    for (long long i = 0; i < length; i++) {
        long long index = rand() % alphabet_size;
        word += alphabet[index];
    }

    return word;
}


class Node {
private:
    std::string key;
    long long value;
    Node* next;

public:
    Node(std::string key = "", ll value = -1, Node* next = nullptr) 
        : key(key), value(value), next(next) {}

    void setKey(const std::string& key) { this->key = key; }
    std::string getKey() const { return key; }

    void setValue(long long value) { this->value = value; }
    long long getValue() const { return value; }

    void setNext(Node* next) { this->next = next; }
    Node* getNext() const { return next; }
};