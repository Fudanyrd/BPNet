#include "random_creater.h"
#include <iostream>

using std::cout;            using std::cin;
using std::endl;

/* you will not be promted, but remember: filename is passed to main
    followed by the rows and columns of each file.
*/
int main(int argc,char** argv){
    size_t r, c;
    for(int i=1;i!=argc;++i){
        cin >> r >> c;
        random_creater::dump(r,c,argv[i]);
    } 

    return 0;
}