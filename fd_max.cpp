#include <BPNet.h>
#include "random_creater.h"

using std::cout;                using std::cin;
using std::endl;

#define LAYERS 4u
#define TRAIN_DAT 64u
#define TEST_DAT 10u

double RandFloat(){
    return rand()/(double)RAND_MAX;
}

int main(int argc,char** argv){
    /* train a network which can tell the 2 input which is larger.*/
    Vec<BPBase*> layers;
    size_t neuros[LAYERS] = {2,10,5,1};
    construct_network(layers,LAYERS,neuros);

    /*collect train data.*/
    srand((unsigned)time(0));
    double** train_dat=random_creater::load("trainDat.txt");
    double targets[TRAIN_DAT][1];
    for(size_t i=0;i!=TRAIN_DAT;++i){
        targets[i][0] = train_dat[i][0] > train_dat[i][1] ? train_dat[i][0]:train_dat[i][1]; 
    }    

    /*train the network*/
    cout << "========================train=======================" << endl;
    const size_t max_iteration=131072;
    double current_err = 0.1;
    for(size_t i=0;i!=max_iteration;++i){
        for(size_t k=0;k!=TRAIN_DAT;++k){
            current_err=train(layers,0.125,0.25,train_dat[k],targets[k]);
        }
        if(i%256 == 0)
            cout << "Iteration: " << i << " current error: " << current_err << endl;
    }

    /*After training, do remember to call random_creater::free, unless you need it later. */
    random_creater::free(train_dat,TRAIN_DAT); 

    /*test it*/
    cout << "========================test========================" << endl;
    /*in fact your test data can also be put into a .txt file.*/
    double test_dat[TEST_DAT][2]={
        {0.68,0.23},{0.98,0.12},{0.23,0.66},{0.59,0.12},{0.15,0.09},{0.24,0.78},{0.89,0.94},{0.12,0.03},
        {0.20,0.80},{0.45,0.05}
    };
    for(size_t i=0;i!=TEST_DAT;++i){
        test(layers,test_dat[i]);
        cout << test_dat[i][0] << ',' << test_dat[i][1] << ": ";
        cout << layers[LAYERS-1]->units[1] << endl;
    }

    /* dump weights of InputLayer and HiddenLayer. */
    const char* fn1 = "input_weights.txt";
    const char* fn2 = "hidden_weights1.txt";
    const char* fn3 = "hidden_weights2.txt";
    layers[0]->dump(fn1);
    layers[1]->dump(fn2);
    layers[2]->dump(fn3);


    return 0;
}