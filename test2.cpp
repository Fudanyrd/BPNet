#include "BPNet.h"

using std::cout;        using std::endl;
using std::cin;

int main(int argc,char** argv){
    /*load weights from files you created by running train2.cpp. */
    Vec<BPBase*> layers;
    srand((unsigned)time(0));
    layers.push_back(new InputLayer(2,10));
    layers.push_back(new HiddenLayer(10,1));
    layers.push_back(new OutputLayer(1));
    layers[0]->load("input_weights.txt");
    layers[1]->load("hidden_weights.txt");

    /*collect test data. */
    double train_dat[4][2]={
        {0,0},{0,1},{1,0},{1,1}
    };
    double targets[4][1]={
        {0},{1},{1},{0}
    };

    /* test it */
    cout << endl << "========================test========================" << endl;
    for (size_t i = 0; i != 4; ++i) {
        test(layers, train_dat[i]);
        cout << '(' << train_dat[i][0] << ',' << train_dat[i][1] << "): "
            << layers[layers.size() - 1]->units[1] << endl;
    }
    cout << "========================Done========================" << endl;

    return 0;
}