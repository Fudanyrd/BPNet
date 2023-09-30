#pragma once
#ifndef BPNN_H
#define BPNN_H
/*=========================================================
	this program aims to construct a 3-layer neural network.
	the zero element each layer is a gate.
==========================================================*/

#include <iostream>
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <cmath>

class BPNN {
private:
	size_t input_n;
	size_t hidden_n;		
	size_t output_n;

	double* input_units;
	double* hidden_units;
	double* output_units;

	double* hidden_delta;
	double* output_delta;

	double* target;

	double** input_weights;
	double** hidden_weights;

	double** input_prev_weights;
	double** hidden_prev_weights;

public:
	/*output error, result in err.
		target--target array
		delta--error array
		nj--actual neural number
		err--combination of all errors.
	*/
	static void output_error(double* delta, double* target, 
		double* output, size_t nj, double* err);
	/*
		delta_h: error of hidden layer, nh: number of neurals in hidden layer
		delta_o: error of output layer, no: outputlayer neural
		who: hidden layer->output layer weight
		hidden: neural os hidden layer
		err: total err
	*/
	static void hidden_error(double* delta_h, size_t nh, double* delta_o, size_t no,
		double** who, double* hidden, double* err);
	/*
	* l1, l2: front, next layer of neural
	conn: connetion weight
	n1, n2: numbers of neurals.
	*/
	static void layerforward(double* l1, double* l2, double** conn, size_t n1, size_t n2);
	/*
		eta: learning rate
		delta: error array
		w: weight array.
	*/
	static void adjust_weights(double* delta, size_t ndelta, double* ly, size_t nly,
		double** w, double** oldw, double eta, double momentum);
	
	BPNN(size_t n_in, size_t n_hidden, size_t n_out);
	~BPNN();

	void train(double eta, double mometum, double* eo,double* eh);
	void feed_forward();

	void initialize()const { srand((unsigned)time(0)); }

	void save(std::ostream&);
	void read(std::istream&);
};

#endif//BPNN_H
