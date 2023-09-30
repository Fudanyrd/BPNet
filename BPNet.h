#ifndef BPNET_H
#define BPNET_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <stdexcept>
#include "Vec.h"

double* construct_1d(size_t length);
double** construct_2d(size_t rows,size_t cols);
void randomize_weights(double**,size_t,size_t);

class BPBase{
public:
    BPBase(size_t neuros):Neuros(neuros){}
    virtual void layerforward(BPBase* next_layer)= 0;
    /*
        rate: Learning rate during training.
        mometum: literal.
    */
    virtual void adjust_weights(double rate,double mometum,BPBase* last)=0;
    virtual double error(BPBase* next){ return 0.0; }
    virtual ~BPBase(){}
//protected:
    double* units;
    double* delta;
    size_t Neuros;
    double* target;
//    double** weights;
//   double** prev_weights;
};

class InputLayer: public BPBase{
public:
    InputLayer(size_t neuros,size_t branch):BPBase(neuros),branches(branch){
        weights = construct_2d(Neuros+1, branches+1);
        randomize_weights(weights,Neuros+1,branches+1);
        prev_weights = construct_2d(Neuros+1,branches+1); 
        units = construct_1d(Neuros+1);
    }
    ~InputLayer(){
        delete[] units;
        for(size_t r = 0;r!=Neuros+1;++r){
            delete[] weights[r];
            delete[] prev_weights[r];
        }
        delete[] weights;
        delete[] prev_weights;
    }

    void layerforward(BPBase* next);
    void adjust_weights(double rate,double momentum,BPBase* next);
//protected:
    size_t branches;        //the number of Neuros of the next layer.
    double** weights;
    double** prev_weights;
};

class HiddenLayer: public BPBase{
public:
    HiddenLayer(size_t neuros,size_t branch):BPBase(neuros),branches(branch){
        weights = construct_2d(Neuros+1, branches+1);
        randomize_weights(weights,Neuros+1,branches+1);
        prev_weights = construct_2d(Neuros+1,branches+1); 
        units = construct_1d(Neuros+1);
        delta = construct_1d(Neuros+1);
    }
    ~HiddenLayer(){
        delete[] units;
        for(size_t r = 0;r!=Neuros+1;++r){
            delete[] weights[r];
            delete[] prev_weights[r];
        }
        delete[] weights;
        delete[] prev_weights;
        delete[] delta;
    }

    void layerforward(BPBase* next);
    void adjust_weights(double rate,double momentum,BPBase* next);
    double error(BPBase* next);
//protected:
    size_t branches;
    double** prev_weights;
    double** weights;
};

class OutputLayer: public BPBase{
public:
    OutputLayer(size_t neuros):BPBase(neuros){
        units = construct_1d(Neuros+1);
        delta = construct_1d(Neuros+1);
        target = construct_1d(Neuros+1);
    }
    ~OutputLayer(){
        delete[] delta;
        delete[] units;
        delete[] target;
    }
    
    void layerforward(BPBase* next){}
    void adjust_weights(double rate,double mometum,BPBase* next){}

    double error(BPBase* next);
protected:
};

/*
    train a BP network made of a set of layers
    learn rate: 0.01-0.8
    mometum: about 0.3
    input: train data.
    targets: expected result.
    return the output error.
*/
double train(Vec<BPBase*>& layers,double rate, double momentum,
    double* inputs, double* targets);

#endif//BPNET_H