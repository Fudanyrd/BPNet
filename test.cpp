#include "BPNet.h"

using std::cout;        using std::cin;
using std::endl;

int main(int argc,char** argv){
    /* construct a 3-layer network with one InputLayer,OutputLayer,HiddenLayer.*/
    Vec<BPBase*> layers;
    layers.push_back(new InputLayer(2,10));
    layers.push_back(new HiddenLayer(10,1));
    layers.push_back(new OutputLayer(1));

    /*collect train data. */
    double train_dat[4][2]={
        {0,0},{0,1},{1,0},{1,1}
    };
    double targets[4][1]={
        {0},{1},{1},{0}
    };

    /*train it*/
    const size_t max_iteration=10;
    const double max_err = 0.02;
    double current_err = 0.1;
    for(size_t i=0;i!=max_iteration&&current_err>max_err;++i){
        for(size_t k=0;k!=4;++k)
            current_err=train(layers,0.01,0.3,train_dat[k],targets[k]);
        cout << "Iteration: " << i << "current error: " << current_err << endl;
    }

    return 0;
}