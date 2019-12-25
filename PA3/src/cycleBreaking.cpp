#include "cycleBreaking.h"
#include <iomanip>

#define  MIN -2147483648
#define DUMMY_WEIGHT -101

cycleMgr::cycleMgr(string filename){
    fstream fin(filename.c_str());
    int count=0;
    cost = 0;
    char d;
    fin >> d;
    if(d == 'u') type = false;
    else if(d == 'd') type = true;
    else{
        cerr << "ERROR: unsupported format!(" << d << ")" << endl;
        return ;
    }
    fin >> v >> e;
    cout << "v = " << v << ", e = " << e << endl;

    // contruct a v*v adjacency matrix
    adj_list = new int *[v];
    visited = new bool[v];
    for(int i=0; i<v; i++){
        adj_list[i] = new int[v];
        for(int j=0; j<v; j++) adj_list[i][j] = DUMMY_WEIGHT;
        visited[i] = false;
    }

    int x, y, w;
    for(int i=0; i<e; i++){
        if(fin >> x >> y >> w){
            if(x < v && y < v){
                if(adj_list[x][y]!=DUMMY_WEIGHT) cout << "duplicated edge!(" << x << ", " <<  y << ")" << endl;
                adj_list[x][y] = w;
                if(!type) adj_list[y][x] = w;
            }
            else{
                cerr << "ERROR: vertex index out of range!(" << x << "->" << y << endl;
                return ;
            }
        }
        else{
            cerr << "ERROR: missing edge!(" << i+1 << ")" << endl; 
        }
    }
    // print_adj();
}

void cycleMgr::breakcycle(bool type){
    if(type){ // dir
        blocked_map = new size_t[v];
        blocked = new bool[v];
        for(int i=0; i<v; i++){ 
            blocked_map[i] = v;
            blocked[i] = false;
        }
        for(int i=0; i<v; i++){
            find_cycle(i);
        }
        return;
    }
    else{ //undir
        Edge * min_edge = new Edge(0, 0, 101);
        int count = 0;
        key = new int[v];
        predecessor = new size_t[v];
        mst = new bool* [v];
        for(size_t i=0; i<v; i++){
            key[i] = MIN;
            predecessor[i] = v;
            visited[i] = false;
            mst[i] = new bool[v];
            for(int j=0; j<v; j++) mst[i][j] = 0;
        }
        key[0] = 0;
        for(int i=0; i<v; i++) {
            int u = MaxKeyExtract();
            visit(u);
            if(predecessor[u]!=v){
                mst[u][predecessor[u]] = true;
                mst[predecessor[u]][u] = true;
                count++;
            }
            for(int j=0; j<v; j++) {
                if(!is_visited(j) && adj_list[u][j]!=DUMMY_WEIGHT && adj_list[u][j]>key[j]){
                    key[j] = adj_list[u][j];
                    predecessor[j] = u;
                }
            }
        }
        for(int i=0; i<v; i++){
            for(int j=i; j<v; j++){
                if(adj_list[i][j]!=DUMMY_WEIGHT && mst[i][j]==0){
                    breaking_list.push_back(new Edge(i, j, adj_list[i][j]));
                    cost+=adj_list[i][j];
                }
            }
        }
    }
}

int cycleMgr::MaxKeyExtract(){
    int max = MIN, max_idx = 0;
    for(int i=0; i<v; i++) {
        if(!is_visited(i) && key[i]>max){
            max = key[i];
            max_idx = i;
        }
    }
    return max_idx;
}

void cycleMgr::dfs_d(size_t x, size_t pi, Edge* min_edge){
    visit(x);
    for(int i=0; i<v && i!=pi; i++){
        if(adj_list[x][i]!=DUMMY_WEIGHT){ // there is an edge between x->i
            cout << "edge " << x << ' ' << i << endl;
            if(adj_list[x][i] < min_edge->get_w()){
                min_edge->update(x, i, adj_list[x][i]);
                cout << "update! ";
                min_edge->print();
            }
            if(is_visited(i)){ // cycle detected!
                cout << "cycle detected!" << endl;
                breaking_list.push_back(min_edge);
                min_edge = new Edge(0, 0, -101);
            }
            else dfs_d(i, x, min_edge);
        }
    }
}

void cycleMgr::find_cycle(size_t x){
    stack.push_back(x);
}

void cycleMgr::write(string filename){
    fstream fout;
    fout.open(filename.c_str(), ios::out);
        fout << cost << endl;
        for(int i=0; i<breaking_list.size(); i++) fout << *breaking_list[i] << endl;
    fout.close();
}

void cycleMgr::print_adj() const{
    cout << "    ";
    for(int i=0; i<v; i++) cout << setw(4) << i;
    cout << endl;
    for(int i=0;  i<v; i++){
        cout << setw(4) << i;
        for(int j=0; j<v; j++) cout << setw(4) << adj_list[i][j];
        cout << endl;
    }
}

void cycleMgr::print_breaking_list() const {
    cout << "total " << breaking_list.size() << " edges need to remove!" << endl;
    cout << "cost = " << cost << endl;
    // for(int i=0; i<breaking_list.size(); i++) cout << *breaking_list[i] << endl;
}