#include "maxPlanarSubset.h"

MPChords::MPChords(string filename){
    fstream fin(filename);
    fin >> n;
    int a,b;
    while (fin >> a >> b)
        chords.push_back(make_pair(a, b));
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
    int dia = get_dia(b);
    if(dia > a && dia < b){
        if(get_mpnum(a,dia-1)==-1) find_max(a, dia-1);
        if(get_mpnum(dia+1,b-1)==-1) find_max(dia+1, b-1);
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
int MPChords::get_dia(int a){
    int ans = -1;
    for(int i=0; i<chords.size(); i++){
        if(chords[i].first == a){ ans = chords[i].second; break;}
        if(chords[i].second == a){ ans = chords[i].first; break;}
    }
    return ans;
}

void MPChords::write(string filename){
    fstream fout;
    fout.open(filename,ios::out);
    fout << mpnum[0][n-1] << endl;
    for (int i = 0; i< mpsubchords.size(); i++){
        fout << mpsubchords[i].first  << " " << mpsubchords[i].second << endl;
    }
    fout.close();
}

void MPChords::trace(int i, int j){
    if(i >= j) return;
    int dia = get_dia(j);
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