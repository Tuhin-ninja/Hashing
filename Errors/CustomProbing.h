#ifndef CUSTOMPROBING_H
#define CUSTOMPROBING_H

#include "GeneralHash.h"

class CustomProbing : public Hash
{
private:
    Node *table;
    ll tableSize;
    ll function;
    ll c1;
    ll c2;

public:
    CustomProbing(ll n, ll function, ll c1, ll c2) : Hash(nextPrime(n))
    {
        tableSize = nextPrime(n);
        table = new Node[tableSize];
        this->function = function;
        this->c1 = c1;
        this->c2 = c2;
    }

    CustomProbing(const CustomProbing &other) : Hash(other)
    {
        tableSize = other.tableSize;
        table = new Node[tableSize];
        function = other.function;
        c1 = other.c1;
        c2 = other.c2;
        for (ll i = 0; i < tableSize; i++)
        {
            table[i] = other.table[i];
        }
    }

    void insert(string key, long long value)
    {
        ll index = 0;
        if (function == 1)
        {
            if (find(key) != -1)
            {
                return;
            }
            index = customHash(key);
        }
        else if (function == 2)
        {
            if (find(key) != -1)
            {
                return;
            }
            index = simpleHash(key);
        }

        if (table[index].getKey() == "")
        {
            table[index] = Node(key, value);
        }
        else
        {
            ll i = 1;
            ll hash_k = index;
            while (table[(index + c1 * i + c2 * i * i) % tableSize].getKey() != "")
            {
                i++;
                collisions++;
            }
            table[(index + c1 * i + c2 * i * i) % tableSize] = Node(key, value);
        }
        size++;
    }

    void remove(string key)
    {
        ll index = 0;
        if (function == 1)
        {
            if (find(key) == -1)
            {
                return;
            }
            index = customHash(key);
        }
        else if (function == 2)
        {
            if (find(key) == -1)
            {
                return;
            }
            index = simpleHash(key);
        }

        if (table[index].getKey() == key)
        {
            table[index] = Node();
        }
        else
        {
            ll i = 1;
            ll hash_k = index;
            while (table[(index + c1 * i + c2 * i * i) % tableSize].getKey() != key)
            {
                i++;
            }
            table[(index + c1 * i + c2 * i * i) % tableSize] = Node();
        }
        size--;
    }

    long long find(string key)
    {
        ll index = 0;
        if (function == 1)
        {
            if (find(key) == -1)
            {
                return -1;
            }
            index = customHash(key);
        }
        else if (function == 2)
        {
            if (find(key) == -1)
            {
                return -1;
            }
            index = simpleHash(key);
        }

        if (table[index].getKey() == key)
        {
            return table[index].getValue();
        }
        else
        {
            ll i = 1;
            ll hash_k = index;
            while (table[(index + c1 * i + c2 * i * i) % tableSize].getKey() != key)
            {
                i++;
                probes++;
            }
            return table[(index + c1 * i + c2 * i * i) % tableSize].getValue();
        }
    }
};

#endif