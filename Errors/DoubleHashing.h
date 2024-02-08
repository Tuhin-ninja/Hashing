#ifndef DOUBLEHASHING_H
#define DOUBLEHASHING_H

#include "GeneralHash.h"

class DoubleHashing : public Hash {
private:
    Node** table;
    ll tableSize;
    ll function;
    ll stepSize;
public:
    DoubleHashing(ll n, ll function) : Hash(nextPrime(n)){
        tableSize = nextPrime(n);
        table = new Node*[tableSize];
        this->function = function;
        stepSize = 1;
        for(ll i = 0; i < tableSize; i++){
            table[i] = nullptr;
        }
    }

    DoubleHashing(const DoubleHashing& other) : Hash(other){
        tableSize = other.tableSize;
        table = new Node*[tableSize];
        function = other.function;
        stepSize = other.stepSize;
        for(ll i = 0; i < tableSize; i++){
            table[i] = other.table[i];
        }
    }

    ~DoubleHashing(){
        for(ll i = 0; i < tableSize; i++){
            if(table[i] != nullptr){
                delete table[i];
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

        if(table[index] == nullptr){
            table[index] = new Node(key, value);
        }else{
            ll i = 1;
            stepSize = auxHash(key);
           // cout<<stepSize<<endl;
            ll hash_k = index; 
            while(table[(hash_k + i*stepSize)%tableSize] != nullptr){
                //cout<<"in the loop"<<endl;
                i++;
                collisions++;
            }
           // cout<<"index: "<<(hash_k + i*stepSize)%tableSize<<endl;
            table[(hash_k + i*stepSize)%tableSize] = new Node(key, value);
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

        if(table[index] == nullptr){
            return;
        }else{
            ll i = 1;
            stepSize = auxHash(key);
            ll hash_k = index; 
            while(table[(hash_k + i*stepSize)%tableSize] != nullptr){
                if(table[(hash_k + i*stepSize)%tableSize]->getKey() == key){
                    table[(hash_k + i*stepSize)%tableSize] = nullptr;
                    size--;
                    return;
                }
                i++;
            }
        }
    }

    long long find(string key){
        ll index = 0;
        index = function == 1? customHash(key) : simpleHash(key);
        if(table[index] == nullptr){
            return -1;
        }else{
            ll i = 1;
            stepSize = auxHash(key);
            ll hash_k = index; 
            while(table[(hash_k + i*stepSize)%tableSize] != nullptr){
                if(table[(hash_k + i*stepSize)%tableSize]->getKey() == key){
                    return table[(hash_k + i*stepSize)%tableSize]->getValue();
                }
                i++;
                probes++;
            }
            return -1;
        }
        
    }
};

#endif