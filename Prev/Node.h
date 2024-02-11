#include <string>

class Node {
private:
    std::string key;
    long long value;
    Node* next;

public:
    Node(std::string key = "", long long value = -1, Node* next = nullptr) 
        : key(key), value(value), next(next) {}

    void setKey(const std::string& key) { this->key = key; }
    std::string getKey() const { return key; }

    void setValue(long long value) { this->value = value; }
    long long getValue() const { return value; }

    void setNext(Node* next) { this->next = next; }
    Node* getNext() const { return next; }
};