#include "BPNet.h"

using std::cout;        using std::cin;
using std::endl;

int main(int argc,char** argv){
    /* construct a 3-layer network with one InputLayer,OutputLayer,HiddenLayer.*/
    Vec<BPBase*> layers;
    srand((unsigned)time(0));
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
    cout << "========================train=======================" << endl;
    const size_t max_iteration=2000;
    const double max_err = 1e-3;
    double current_err = 0.1;
    for(size_t i=0;i!=max_iteration;++i){
        for(size_t k=0;k!=4;++k)
            current_err=train(layers,0.5,0,train_dat[k],targets[k]);
        cout << "Iteration: " << i << " current error: " << current_err << endl;
    }

    /* test it*/
    cout << endl << "========================test========================" << endl;
//    test(layers, train_dat[0]);
//    cout << "(0,0): " << layers[layers.size() - 1]->units[0] << endl;
    for (size_t i = 0; i != 4; ++i) {
        test(layers, train_dat[i]);
        cout << '(' << train_dat[i][0] << ',' << train_dat[i][1] << "): "
            << layers[layers.size() - 1]->units[1] << endl;
    }

    return 0;
}