#include "cycleBreaking.h"

using namespace std;

int main(int argc, char* argv[]){
    if(argc != 3) {
       cerr << "please provide I/O file path!" << endl;
       return 0;
    }
    cycleMgr mycycleMgr(argv[1]);
    // mycycleMgr.breakcycle(0);
    // mycycleMgr.print_breaking_list();
    // mycycleMgr.write(argv[2]);
}