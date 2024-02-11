#include "HashTable.hpp"

#define N 10000

int main(){ 
    HashTable *hashTable = new HashTable(5000,5);
    for(ll i=1;i<=N;i++){ 
        hashTable->insert(generateRandomWord(10),i,1,1,3,5);
    }
}