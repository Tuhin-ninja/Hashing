#ifndef GENERALHASH_H
#define GENERALHASH_H


#include "Node.h"
using namespace std;

class Hash {
protected:
    long long N, size, probes, collisions;
     
    public : 
      Hash(ll N){
        this->N = N;
        size = 0;
        probes = 0;
        collisions = 0;
      }
      Hash(const Hash& other){
        N = other.N;
        size = other.size;
        probes = other.probes;
        collisions = other.collisions;
      }

    virtual void insert(string key, long long value) = 0;
    virtual void remove(string key) = 0;
    virtual long long find(string key) = 0;

    ll customHash(string k){
        ll hash = 0; 
        ll preMultiplier = 31; 
        for(char c : k){
            hash = (hash * preMultiplier + c);
        }

        return hash % N; 
    }

ll simpleHash(const string& k) {
    ll hash = 0;
    
    for(char c : k) {
        hash += c;
    }

    return hash;
}

    ll auxHash(string k){ 
        ll hash = 0; 
        for(char c : k){
            hash = hash + c;
        }

        return hash % N; 
    }

    void resetProbes(){
        probes = 1;
    }

    void resetCollisions(){
        collisions = 0;
    }

    long long getSize(){
        return size;
    }

    long long getProbes(){
        return probes;
    }

    long long getCollisions(){
        return collisions;
    }

};

#endif