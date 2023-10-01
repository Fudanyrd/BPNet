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

    /* dump weights of InputLayer and HiddenLayer. */
    const char* fn1 = "input_weights.txt";
    const char* fn2 = "hidden_weights.txt";
    layers[0]->dump(fn1);
    layers[1]->dump(fn2);

    return 0;
}