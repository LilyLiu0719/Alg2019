#include "maxPlanarSubset.h"

using namespace std;

int main(int argc, char* argv[]){
    if(argc != 3) {
       cerr << "please provide I/O file path!" << endl;
       return 0;
    }
    MPChords mpchords(argv[1]);
    for(int i=0; i<mpchords.get_n(); i++){
        // cout << "find max " << i << endl; 
        for(int j=0; j<mpchords.get_n()-i-1; j++){
            mpchords.find_max(j, i+j+1);
        }
    }
    mpchords.trace(0, mpchords.get_n()-1);
    mpchords.sort_and_clean();
    // mpchords.print();
    mpchords.write(argv[2]);
}