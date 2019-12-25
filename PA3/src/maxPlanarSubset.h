#include <vector>
#include <cstring>
#include <iostream>
#include <fstream>

using namespace std;

class MPChords{
public:
    MPChords(string);
    ~MPChords();
    void find_max(int, int);
    int get_n(){return n;}
    // int get_dia(int);
    int get_mpnum(int i, int j){
        if(i<0 ||  j<0 || i>=n || j>=n) return 0;
        else return mpnum[i][j];
    }
    void write(string);
    void sort_and_clean();
    void trace(int, int);
    void print();
    int get_top(){
        return mpnum[0][n-1];
    }
private:
    int * chords;
    vector<pair<int,int> > mpsubchords;
    int ** mpnum;
    int ** mpcase;
    int n;
};