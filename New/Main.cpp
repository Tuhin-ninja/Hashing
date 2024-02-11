#include "HashTable.hpp"
#define N 10000

ll c1 = 3, c2 = 5;
ll allowedChain = 3;

#define seed  2105


int main(){ 
    //srand(seed);
    ll size[] = {5000,10000,20000};
    ofstream fout("report.txt");
    ofstream fout2("report2.txt");
    fout2<<CUSTOM<<" "<<SIMPLE<<" "<<DOUBLE_HASHING<<endl;

    string *testWords = new string[N]; 
    for(ll i=0;i<N;i++){ 
       testWords[i] = generateRandomWord(5 + rand() % 6);
       fout2<<testWords[i]<<endl;
    }

    double report[3][3][2][2];  //table_size, resolution_method, hash_functon, [collisions, probes]

    for(ll m=0;m<3;m++){ 
        //HashTable *hashTable = new HashTable(size[m],allowedChain);
        for(ll i=0;i<3;i++){ 
            for(ll j=0;j<2;j++){ 
                HashTable *hashTable = new HashTable(size[m],allowedChain,testWords);
                cout<<"new table creating for : ";
                cout<<size[m]<<" "<<i<<" "<<j<<endl;
                for(ll k=0;k<N;k++){ 
                    hashTable->insert(testWords[k],hashTable->getSize()+1,j,i,c1,c2);
                    hashTable->resetProbes();
                }
                cout<<"after insertion"<<endl;
                report[m][i][j][0] = hashTable->getCollisions();
                hashTable->resetProbes();
                // cout<<hashTable->getProbes()<<endl;
                fout<<report[m][i][j][0]<<endl;

                for(ll k=0;k<0.011*size[m];k++){ 
                    hashTable->find(testWords[k],j,i,c1,c2);
                }

                report[m][i][j][1] = (double)hashTable->getProbes()/(0.011*size[m]);
                fout<<report[m][i][j][1]<<endl;
                delete hashTable;
            }
        }
    }

    return 0;

}