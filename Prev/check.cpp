#include<bits/stdc++.h>
using namespace std;


unsigned long fnv1aHash(const std::string& str) {
    const unsigned long FNV_offset_basis = 14695981039346656037LL;
    const unsigned long FNV_prime = 1099511628211LL;

    unsigned long hash = FNV_offset_basis;

    // Iterate through each character of the string
    for (char c : str) {
        // XOR the hash with the current character and multiply by the prime
        hash ^= static_cast<unsigned long>(c);
        hash *= FNV_prime;
    }

    return hash % N;
}


int main(){
    string str = "Hello, World!";
    cout << fnv1aHash(str) << endl;
    return 0;
}