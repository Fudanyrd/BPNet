#ifndef BPNET_H
#define BPNET_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <stdexcept>
#include <fstream>
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
    
    /* dump weights into a .txt file.*/
    virtual void dump(const char* filename){}
    /* load weights from the .txt file.*/
    virtual void load(const char* filename){}

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

    void dump(const char* filename);
    void load(const char* filename);
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

    void dump(const char* filename);
    void load(const char* filename);

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
/*
    use trained network to get some output.
    result is in the OutputLayer, go and see yourself.
*/
void test(Vec<BPBase*>& layers, double* inputs);

/*  THIS function is mainly for simplifying the construction of a net work.
    construct a neuro network for training.
    nums: number of layers
    Neuros: the number of neuros of each layer
    result is in layers.
*/
void construct_network(Vec<BPBase*>& layers,size_t nums, size_t *Neuros);

#endif//BPNET_H