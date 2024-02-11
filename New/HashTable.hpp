#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define seed 2105

enum HashFunction
{
    CUSTOM,
    SIMPLE
};

enum ResolutionMethod
{
    SEPARATE_CHAINING,
    DOUBLE_HASHING,
    CUSTOM_PROBING
};

ll nearestPrime(ll n)
{
    cout << "custom : " << CUSTOM << endl;
    while (true)
    {
        bool isPrime = true;
        for (ll i = 2; i <= sqrt(n); i++)
        {
            if (n % i == 0)
            {
                isPrime = false;
                break;
            }
        }
        if (isPrime)
        {
            return n;
        }
        n++;
    }
}

string generateRandomWord(long long length)
{
    static const string alphabet = "abcdefghijklmnopqrstuvwxyz";
    long long alphabet_size = 26;
    string word;

    for (long long i = 0; i < length; i++)
    {
        long long index = rand() % alphabet_size;
        word += alphabet[index];
    }

    return word;
}

class Node
{
private:
    string key;
    long long value;
    Node *next;
    bool softDeleted;

public:
    Node(string key, long long value)
    {
        this->key = key;
        this->value = value;
        next = nullptr;
        softDeleted = false;
    }
    string getKey()
    {
        return key;
    }
    long long getValue()
    {
        return value;
    }
    Node *getNext()
    {
        return next;
    }
    void setNext(Node *next)
    {
        this->next = next;
    }
    void setSoftDeleted(bool softDeleted)
    {
        this->softDeleted = softDeleted;
    }
    bool isSoftDeleted()
    {
        return softDeleted;
    }

    // ll getLengthCount(){
    //     return lengthCount;
    // }

    // void setLengthCount(ll lengthCount){
    //     this->lengthCount = lengthCount;
    // }
};

class HashTable
{
    ll N, size, probes, collisions, insertCount, allowedChainLength, maxChainLength;
    ll deleteCount;
    vector<Node *> table;
    string *testWords;
    // priority_queue<pair<ll,Node*>> pq;
public:
    HashTable(ll N, ll allowedChainLength, string* testWords)
    {
        srand(seed);
        this->N = nearestPrime(N);
        size = 0;
        probes = 0;
        collisions = 0;
        this->allowedChainLength = allowedChainLength;
        maxChainLength = 0;
        table.resize(N);
        testWords = new string[N];
        this->testWords = testWords;
        for(ll i=0;i<N;i++){
            table[i] = nullptr;
        }

    }

    ~HashTable()
    {
        for (Node *node : table)
        {
            if (node != nullptr)
            {
                Node *temp = node;
                while (temp != nullptr)
                {
                    Node *temp2 = temp;
                    temp = temp->getNext();
                    delete temp2;
                }
            }
        }
    }

    ll getSize()
    {
        return size;
    }

    void resetProbes()
    {
        this->probes = 0;
    }

    void resetCollisions()
    {
        collisions = 0;
    }

    ll getProbes()
    {
        return probes;
    }

    ll getCollisions()
    {
        return collisions;
    }

    void insert(string key, ll value, ll function, ll method, ll c1 = 0, ll c2 = 0)
    {
        ll index = 0;
        if (function == CUSTOM)
        {
            // cout<<"in the custom"<<endl;
            index = customHash(key);
        }
        else if (function == SIMPLE)
        {
            index = simpleHash(key);
        }

        if (method == SEPARATE_CHAINING)
        {

            if (find(key, function, SEPARATE_CHAINING))
            {
                cout << "key already exixts" << endl;
                return;
            }

            if (insertCount >= 100)
            {
                if (maxChainLength >= allowedChainLength)
                {
                    insertCount = 0;
                    // cout<<"in the rehashing"<<endl;
                    rehash(1, function);
                }
            }

            Node *newNode = new Node(key, value);
            if (table[index] == nullptr)
            {
                //cout << "in the insertion of null" << endl;
                table[index] = newNode;
            }
            else
            {
                //cout << "in the insertion of not null" << endl;
                int counter = 1;
                Node *temp = table[index];
                while (temp->getNext() != nullptr)
                {
                    counter++;
                    temp = temp->getNext();
                }
                if (counter > maxChainLength)
                {

                    maxChainLength = counter;
                }
                temp->setNext(newNode);
                collisions += counter;
                // table[index]->setLengthCount(counter);
            }
            size++;
            insertCount++;
        }

        else if (method == DOUBLE_HASHING)
        {

            // Double Hashing

            if (size >= 0.65 * N)
            {
                // cout<<"Ignore the insertion"<<endl;
                return;
            }

            if (find(key, function, DOUBLE_HASHING))
            {
                cout << "key already exixts" << endl;
                return;
            }

            ll hash_k = index;
            if (table[hash_k] == nullptr || table[hash_k]->isSoftDeleted())
            {
                // cout<<"in the insertion"<<endl;
                table[hash_k] = new Node(key, value);
            }

            else
            {
                ll i = 1;
                ll stepSize = auxHash(key);
                while (table[(hash_k + i * stepSize) % N] != nullptr && !table[(hash_k + i * stepSize) % N]->isSoftDeleted())
                {
                    i++;
                    collisions++;
                }
                table[(hash_k + i * stepSize) % N] = new Node(key, value);
            }
            size++;
        }

        else if (method == CUSTOM_PROBING)
        {

            // Custom Probing

            if (size >= 0.65 * N)
            {
                // cout<<"Ignore the insertion"<<endl;
                return;
            }

            if (find(key, function, CUSTOM_PROBING, c1, c2))
            {
                cout << "key already exixts" << endl;
                return;
            }

            ll hash_k = index;
            if (table[hash_k] == nullptr || table[hash_k]->isSoftDeleted())
            {
                table[hash_k] = new Node(key, value);
            }
            else
            {
                ll i = 1;
                ll stepSize = auxHash(key);
                while (table[(hash_k + i *c1* stepSize +c2*i*i) % N] != nullptr && !table[(hash_k + i *c1* stepSize + c2*i*i) % N]->isSoftDeleted())
                {
                    i++;
                    collisions++;
                }
                table[(hash_k + c1 * i * stepSize + i * i * c2) % N] = new Node(key, value);
            }
        }
    }

    void Delete(string key, ll function, ll method, ll c1 = 0, ll c2 = 0)
    {
        // seperate chaining method

        ll index = 0;
        if (function == CUSTOM)
        {
            index = customHash(key);
        }
        else if (function == SIMPLE)
        {
            index = simpleHash(key);
        }

        if (method == SEPARATE_CHAINING)
        {
            if (table[index] == nullptr)
            {
                cout << "Key not found" << endl;
                return;
            }

            // rehashing condition will be applied here

            if (deleteCount >= 100)
            {
                if (maxChainLength <= 0.8 * allowedChainLength && size < nearestPrime(N / 2))
                {
                    deleteCount = 0;
                    rehash(2, function);
                }
            }

            if (table[index]->getKey() == key)
            {
                Node *temp = table[index];
                table[index] = temp->getNext();
                // table[index]->setLengthCount(table[index]->getLengthCount()-1);
                delete temp;
                size--;
                deleteCount++;
                return;
            }

            Node *temp = table[index];
            while (temp->getNext() != nullptr)
            {
                if (temp->getNext()->getKey() == key)
                {
                    Node *temp2 = temp->getNext();
                    temp->setNext(temp2->getNext());
                    delete temp2;
                    size--;
                    deleteCount++;
                    return;
                }
            }

            cout << "Key not found" << endl;
        }

        // Double Hashing

        else if (method == DOUBLE_HASHING)
        {
            ll i = 0;
            ll stepSize = auxHash(key);
            ll hash_k = index;
            while (table[(hash_k + i * stepSize) % N] != nullptr)
            {
                if (table[(hash_k + i * stepSize) % N]->getKey() == key && !table[(hash_k + i * stepSize) % N]->isSoftDeleted())
                {
                    table[(hash_k + i * stepSize) % N]->setSoftDeleted(true);
                    size--;
                    return;
                }
                i++;
            }

            cout << "Key not found" << endl;
        }

        else if (method == CUSTOM_PROBING)
        {
            ll i = 0;
            ll stepSize = auxHash(key);
            ll hash_k = index;
            while (table[(hash_k + i * c1 * stepSize + c2 * i * i) % N] != nullptr)
            {
                if (table[(hash_k + i * c1 * stepSize + c2 * i * i) % N]->getKey() == key && !table[(hash_k + i * c1 * stepSize + c2 * i * i) % N]->isSoftDeleted())
                {
                    table[(hash_k + i * c1 * stepSize + c2 * i * i) % N]->setSoftDeleted(true);
                    size--;
                    return;
                }
                i++;
            }

            cout << "Key not found" << endl;
        }
    }

    void rehash(int input, int function)
    {
        // rehashed for both insertion and deletion
        // input 1 for insertion and 2 for deletion

        cout << N << endl;

        cout << "Before Rehashing: " << endl;
        cout << "maxChainLength: " << maxChainLength << endl;
        cout << "Load Factor : " << (double)size / N << endl;
        resetProbes();
        ll checks = 1000;

        for (ll i = 0; i < checks; i++)
        {
            bool x = find(testWords[i], function, SEPARATE_CHAINING);
        }

        cout << "Average Probe Count : " << (double)probes / 1.0 * checks << endl;

        if (input == 1)
        {
            // for insertion
            N = nearestPrime(2 * N);
            cout<<N<<endl;
        }
        else if (input == 2)
        {
            N = nearestPrime(N / 2);
        }

        vector<Node *> temp = table;
        for (Node *node : table)
        {
            delete node;
        }
        table.clear();
        table.resize(N);
        for(ll i=0;i<N;i++){
            table[i] = nullptr;
        }
        size = 0;
        // collisions = 0;
        probes = 0;
        maxChainLength = 0;
        insertCount = 0;
        ll counter = 0;
        for (Node *node : temp)
        {
            counter++;
            if (node != nullptr)
            {
                Node *temp2 = node;
                while (temp2 != nullptr)
                {
                    if (function == CUSTOM)
                    {
                        insert(temp2->getKey(), temp2->getValue(), CUSTOM, SEPARATE_CHAINING);
                    }
                    else if (function == SIMPLE)
                    {
                        insert(temp2->getKey(), temp2->getValue(), SIMPLE, SEPARATE_CHAINING);
                    }
                    temp2 = temp2->getNext();
                }
            }
        }
        cout << "counter is " << counter << endl;

        cout << "\n\n-------------------------------------------------\n\n"
             << endl;

        cout << "After Rehashing: " << endl;
        cout << "maxChainLength: " << maxChainLength << endl;
        cout << "Load Factor : " << (double)size / N << endl;
        resetProbes();
        for (ll i = 0; i < checks; i++)
        {
            bool x = find(testWords[i], function, SEPARATE_CHAINING);
        }

        cout << "Average Probe Count : " << (double)probes / 1.0 * checks << endl;

        cout << "\n\n-------------------------------------------------\n\n"
             << endl;
    }

    bool find(string key, ll function, ll method, ll c1 = 0, ll c2 = 0)
    {
        ll index = 0;
        if (function == CUSTOM)
        {
            index = customHash(key);
        }
        else if (function == SIMPLE)
        {
            index = simpleHash(key);
        }

        // Separate Chaining

        if (method == SEPARATE_CHAINING)
        {
            Node *temp = table[index];
            while (temp != nullptr)
            {
                probes++;
                // cout<<"in the chain"<<endl;
                if (temp->getKey() == key)
                {
                    return true;
                }
                temp = temp->getNext();
            }
            return false;
        }

        // Double Hasing

        else if (method == DOUBLE_HASHING)
        {
            ll i = 0;
            ll stepSize = auxHash(key);
            ll hash_k = index;
            while (table[(hash_k + i * stepSize) % N] != nullptr)
            {
                probes++;
                if (table[(hash_k + i * stepSize) % N]->getKey() == key && !table[(hash_k + i * stepSize) % N]->isSoftDeleted())
                {
                    return true;
                }
                i++;
            }
            return false;
        }

        // Custom Probing

        else if (method == CUSTOM_PROBING)
        {
            ll i = 0;
            ll stepSize = auxHash(key);
            ll hash_k = index;
            while (table[(hash_k + c1 * i * stepSize + i * i * c2) % N] != nullptr)
            {
                probes++;
                if (table[(hash_k + c1 * i * stepSize + i * i * c2) % N]->getKey() == key && !table[(hash_k + c1 * i * stepSize + i * i * c2) % N]->isSoftDeleted())
                {
                    return true;
                }
                i++;
            }
            return false;
        }

        return false;
    }

    ll customHash(string k)
    {
        ll hash = 0;
        ll preMultiplier = 31;
        for (char c : k)
        {
            hash = (hash * preMultiplier + c);
        }

        if (hash < 0)
            hash *= -1;

        return hash % N;
    }

    ll simpleHash(string k)
    {
        ll hashVal = 0;

        for (ll i = 0; i < k.length(); i++)
            hashVal = 37 * hashVal + k[i];

        hashVal %= N;

        if (hashVal < 0)
            hashVal += N;

        return hashVal;
    }

    ll auxHash(string k)
    {
        ll hash = 0;
        for (char c : k)
        {
            hash = hash + c;
        }

        return hash % N;
    }
};