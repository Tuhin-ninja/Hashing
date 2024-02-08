#ifndef CHAINING_H
#define CHAINING_H

#include "GeneralHash.h"

class Chaining : public Hash {
private:
    Node** table;   
    ll tableSize;
    ll function; 
public:
   Chaining(ll n, ll function) : Hash(nextPrime(n)){
       tableSize = nextPrime(n);
       cout<<"table size: "<<tableSize<<endl;
       table = new Node*[tableSize];
       this->function = function;
       for(ll i = 0; i < tableSize; i++){
           table[i] = nullptr;
       }
   }

    Chaining(const Chaining& other) : Hash(other){
         tableSize = other.tableSize;
         table = new Node*[tableSize];
         function = other.function;
         for(ll i = 0; i < tableSize; i++){
              table[i] = other.table[i];
         }
    }

    ~Chaining(){
        for(ll i = 0; i < tableSize; i++){
            if(table[i] != nullptr){
                Node* temp = table[i];
                while(temp != nullptr){
                    Node* prev = temp;
                    temp = temp->getNext();
                    delete prev;
                }
            }
        }
        delete[] table;
    }

    void insert(string key, long long value){
        ll index = 0;
        if(function == 1){
            index = customHash(key);
        }else if(function == 2){
            index = simpleHash(key);
        }

        Node* newNode = new Node(key, value);
        if(table[index] == nullptr){
            table[index] = newNode;
        }else{
            collisions++;
            Node* temp = table[index];
            while(temp->getNext() != nullptr){
                //cout<<"in the loop"<<endl;
                temp = temp->getNext();
            }
            temp->setNext(newNode);
        }
        size++;
    }

    void remove(string key){
        ll index = 0;
        if(function == 1){
            if(find(key) == -1){
                return;
            }
            index = customHash(key);
        }else if(function == 2){
            if(find(key) == -1){
                return; 
            }
            index = simpleHash(key);
        }

        Node* temp = table[index];
        Node* prev = nullptr;
        while(temp != nullptr && temp->getKey() != key){
            prev = temp;
            temp = temp->getNext();
        }

        if(temp == nullptr){
            return;
        }

        if(prev == nullptr){
            table[index] = temp->getNext();
        }else{
            prev->setNext(temp->getNext());
        }
        size--;
    }

    long long find(string key){
        ll index = 0;
        if(function == 1){
            index = customHash(key);
        }else if(function == 2){
            index = simpleHash(key);
        }

        Node* temp = table[index];
        while(temp != nullptr && temp->getKey() != key){
            temp = temp->getNext();
        }

        if(temp == nullptr){
            //cout<<"key not found"<<endl;
            return -1;
        }
        //cout<<"found and passing"<<endl;
        return temp->getValue();
    }


};
#endif