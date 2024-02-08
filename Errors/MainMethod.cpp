#include "Chaining.h"
#include "DoubleHashing.h"
#include "CustomProbing.h"


const ll N = 10000, T = 1000; 
ll c1 = 2105; 
ll c2 = 2107;

int main(){
    string *words = new string[N];
    string * testWords = new string[N]; 
    ll size[3] = {5000, 10000, 20000};
    double report[3][3][2][2];

    for(ll i = 0; i < N; i++){
        ll length = 5 + rand() % 6;
        string word = RandomWord(length);
        words[i] = word;
        testWords[i] = word;
    }

    ll n = 0;

    for(ll &i : size){
        cout<<i<<endl;
        cout<<"okay"<<endl;
        for(ll j = 1; j <= 2; j++){
            //cout<<"okay2"<<endl;
            Chaining *chaining = new Chaining(i, j);

            for(ll m = 0; m < N; m++){
                chaining->insert(testWords[m], chaining->getSize() + 1);
                //cout<<"okay"<<endl;
            }

            chaining->resetProbes();

            for(ll m = 0; m < T; m++){
                chaining->find(testWords[m]);
                
            }

            report[n][0][j - 1][0] = chaining->getCollisions();
            report[n][0][j - 1][1] = chaining->getProbes()*1.0 / T;
            cout<<report[n][0][j - 1][0]<<" ";
            cout<<report[n][0][j - 1][1]<<endl;

            delete chaining;
        }

        for(ll j=1;j<=2;j++){ 
            DoubleHashing *doubleHashing = new DoubleHashing(i, j);
            for(ll m = 0; m < T; m++){
                if(doubleHashing->find(testWords[m]) == -1)
                   doubleHashing->insert(testWords[m], doubleHashing->getSize() + 1);
            }
            cout<<"hashing"<<endl;

            doubleHashing->resetProbes();
            for(ll m = 0; m < T; m++){
                doubleHashing->find(testWords[m]);
            }

            report[n][1][j - 1][0] = doubleHashing->getCollisions();
            report[n][1][j - 1][1] = doubleHashing->getProbes()*1.0 / T;
            cout<<report[n][1][j - 1][0]<<" ";
            cout<<report[n][1][j - 1][1]<<endl;
            delete doubleHashing;
        }

        for(ll j=1;j<=2;j++){
            CustomProbing *customProbing = new CustomProbing(i, j,c1,c2);
            for(ll m = 0; m < T; m++){
                //cout<<"inserting"<<endl;
                if(customProbing->find(testWords[m]) == -1){
                   // cout<<"find successful"<<endl;
                    customProbing->insert(testWords[m], customProbing->getSize() + 1);
                }
    
            }
            customProbing->resetProbes();
            for(ll m = 0; m < T; m++){
                cout<<"in the find"<<endl;
                customProbing->find(testWords[m]);
            }
            report[n][2][j - 1][0] = customProbing->getCollisions();
            report[n][2][j - 1][1] = customProbing->getProbes() / T;
            cout<<report[n][2][j - 1][0]<<" ";
            cout<<report[n][2][j - 1][1]<<endl;
            delete customProbing;
        }
    }

    //cout<<"Chaining"<<endl;

    ofstream file("report.txt");
    file << " " << setw(68) << setfill('_') << "" << endl;
    file << setfill(' ');
    file << "| Hash       | Collision         | Hash Function 1 | Hash Function 2 |" << endl;
    file << "| Table Size | Resolution Method | Colls. | Probes | Colls. | Probes |" << endl;
    file << "|" << setw(69) << setfill('_') << "|" << endl;
    file << setfill(' ');

    ll i =0; 


    // for(long long n : size) {
    //     file << "| N = " << setw(7) << left << size[i];

    //     for(long long j = 0; j < 3; j++) {
    //         if(j == 0) file << "| Separate Chaining | ";
    //         else if(j == 1) file << "|" << setw(34) << right << "| Double Hashing    | ";
    //         else file << "|" << setw(34) << right << "| Custom Probing    | ";

    //         for(long long k = 0; k < 2; k++) {
    //             for(long long m = 0; m < 2; m++) {
    //                 if(m == 0) file << defaultfloat << setw(5) << setprecision(5) << right << report[i][j][k][m] << "  ";
    //                 if(m == 1) file << fixed << setw(2) << setprecision(3) << " " << report[i][j][k][m] << "  ";
    //             }

    //             file << "| ";
    //         }

    //         file << endl; 
    //     }

    //     file << "|" << setw(69) << setfill('_') << "|" << endl;
    //     file << setfill(' ');
    //     i++;
    // }
}