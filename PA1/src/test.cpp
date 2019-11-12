#include<vector>
#include<iostream>

using namespace std;

int main(){
    vector<int> data;
    data.push_back(20);
    data.push_back(140);
    data.push_back(3);
    data.push_back(2);
    data.push_back(9);
    data.push_back(2);
    data.push_back(100);
    data.push_back(39);
    cout << "size = " << data.size() << endl;
    for(int i=0; i<data.size(); i++) cout << data.at(i) << " ";
    cout << endl;

    for(int i=1; i<data.size(); i++){
        int j = i-1;
        int x = data[i];
        while(x < data[j] && j >= 0){
            data[j+1] = data[j];
            j--;
        }
        data[j+1] = x;
    }
    
    for(int i=0; i<data.size(); i++) cout << data.at(i) << " ";
    cout << endl;
}