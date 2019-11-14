#include "maxPlanarSubset.h"
#include <algorithm>

MPChords::MPChords(string filename){
    fstream fin(filename.c_str());
    fin >> n;
    chords = new int[n];
    for(int i=0; i<n;  i++){
        chords[i] = -1;
    }
    int a,b;
    while (fin >> a >> b){
        chords[a] = b;
        chords[b] = a;
    }
    fin.close();
    mpnum = new int* [n];
    for(int i=0; i<n; i++) mpnum[i] = new int[n];
    for(int i=0; i<n;  i++){
        for(int j=0; j<n; j++){
            mpnum[i][j] = 0;
        }
    }
    mpcase = new int* [n];
    for(int i=0; i<n; i++) mpcase[i] = new int[n];
    for(int i=0; i<n;  i++){
        for(int j=0; j<n; j++){
            mpcase[i][j] = 0;
        }
    }
}

void MPChords::find_max(int a, int b){
    // cout << "find max (" << a << ", " << b << ")" <<  endl;
    int dia = chords[b];
    // cout << "dia = "  << dia << endl;
    if(dia > a && dia < b){
        int c2 = get_mpnum(a, dia-1) + get_mpnum(dia+1, b-1) + 1; // case2
        int c1 = get_mpnum(a, b-1); // case1
        mpnum[a][b] = (c1>c2?c1:c2);
        mpcase[a][b] = (c1>c2?1:2);
    }
    else if(dia == a){ // case3
        mpnum[a][b] = get_mpnum(a+1, b-1) + 1;
        mpcase[a][b] = 3;
    }
    else{ // case1
        mpnum[a][b] = get_mpnum(a, b-1);
        mpcase[a][b] = 1;
    }
}

void MPChords::write(string filename){
    fstream fout;
    fout.open(filename.c_str(), ios::out);
    fout << mpnum[0][n-1] << endl;
    for (int i = 0; i< mpsubchords.size(); i++){
        fout << mpsubchords[i].first  << " " << mpsubchords[i].second << endl;
    }
    fout.close();
}

void MPChords::trace(int i, int j){
    if(i >= j) return;
    int dia = chords[j];
    if(mpcase[i][j]==1){
        trace(i, j-1);
    }
    else if(mpcase[i][j]==2){
        mpsubchords.push_back(j>dia ? make_pair(dia, j) : make_pair(j, dia));
        trace(i, dia-1);
        trace(dia+1, j-1);
    }
    else if(mpcase[i][j]==3){
        mpsubchords.push_back(make_pair(i, j));
        trace(i+1, j-1);
    }
}

void MPChords::sort_and_clean(){
    sort(mpsubchords.begin(), mpsubchords.end());
    for(int i=1; i< mpsubchords.size(); i++){
        if( mpsubchords[i].first == mpsubchords[i-1].first){ 
            mpsubchords.erase(mpsubchords.begin()+i);
            i--;
        }
    }
}

void  MPChords::print(){
    cout << "-----mpnum-----" << endl << "   ";
    for(int i=0; i<n; i++) cout << i << ' ';
    cout << endl << "--------------------------" << endl;
    for(int i=0; i<n; i++){
        cout << i << "|" << " "; 
        for(int j=0; j<n; j++) cout << mpnum[i][j] << " ";
        cout << endl;
    }
    cout << "-----mpcase-----" << endl << "   ";
    for(int i=0; i<n; i++) cout << i << ' ';
    cout << endl << "--------------------------" << endl;
    for(int i=0; i<n; i++){
        cout << i << "|" << " "; 
        for(int j=0; j<n; j++) cout << mpcase[i][j] << " ";
        cout << endl;
    }
    cout << "-----mpsubchords-----" << endl;
    for(int i=0; i<mpsubchords.size(); i++){

        cout << mpsubchords[i].first  << " " << mpsubchords[i].second << endl;
    }
}