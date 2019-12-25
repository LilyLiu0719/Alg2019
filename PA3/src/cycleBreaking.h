#include <vector>
#include <cstring>
#include <iostream>
#include <fstream>

using namespace std;

class Edge{
public:
    friend class cycleMgr;
    size_t get_u() const { return _u; }
    size_t get_v() const { return _v; }
    int get_w() const { return _w; }
    void update(size_t u, size_t v, int w) { _u = u; _v = v; _w = w; }
    Edge(size_t u, size_t v, int w): _u(u), _v(v), _w(w){}
    ~Edge(){}
    friend ostream& operator<<(ostream& os, const Edge& e);
    void print(){
        cout << "(" << _u << ", " << _v << ", " << _w << ")" <<  endl;;
    }
private:
    size_t _u, _v;
    int _w;
};

class cycleMgr{
public:
    cycleMgr(string filename);
    ~cycleMgr(){}

    void visit(size_t v){ visited[v] = true; }
    bool is_visited(size_t v) const { return visited[v]; }
    void print_adj() const;
    void print_breaking_list() const;
    void breakcycle(bool );
    // void find_cycle(size_t );
    void dfs(size_t, size_t );
    int MaxKeyExtract();
    void write(string);
    
private:
    bool type; // undir:0, dir:1
    size_t v; // # of vertex
    size_t e; // # of edge
    vector<Edge* > breaking_list;
    int ** adj_list;
    bool * visited;
    bool ** mst;
    int * key;
    size_t * predecessor;
    int cost;
    bool flag;
    Edge *min_edge;
    // vector<size_t> stack;
    // bool * blocked;
    // size_t * blocked_map;  
};

ostream& operator<<(ostream& os, const Edge& e)
{
    os << e._u << ' ' << e._v << ' ' << e._w;
    return os;
}