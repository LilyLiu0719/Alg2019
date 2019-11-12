#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    vector<pair<int,int> > chords;
    chords.push_back(make_pair(1, 3));
    chords.push_back(make_pair(5, 4));
    chords.push_back(make_pair(8, 5));
    chords.push_back(make_pair(4, 6));
    sort(chords.begin(), chords.end());
    for(int i=0; i<chords.size(); i++){
        cout << "(" << chords[i].first  << ", " << chords[i].second << ")" << endl;
    }
}