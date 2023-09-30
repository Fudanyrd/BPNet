#include "BPNN.h"
#include <stdexcept>
using std::endl;
using std::istream;		using std::ostream;
using std::domain_error;

/* return a random number in range[0,1]*/
double drnd() {
	return ((double)rand()) / ((double)RAND_MAX);
}

/* return a double random number in range[-1,1].*/
double dpn1() {
	return drnd() * 2.0 - 1.0;
}

/* operating function(currently S function) */
double squash(double x) {
	return 1.0 / (1.0 + exp(-x));
}

/* allocate memory for 1 dimension double array. */
double* alloc_1d_dbl(size_t n) {
	double* new1 = new double[n];
	if (new1 == 0) throw domain_error("alloc_1d_dbl: allocation failure");
	return new1;
}

/* allocate memory for 2d double array*/
double** alloc_2d_dbl(size_t rows, size_t cols) {
	double** dat = new double* [rows];
	if (dat == 0) throw domain_error("alloc_2d_dbl: allocation failure");
	for (size_t i = 0; i != rows; ++i) {
		dat[i] = alloc_1d_dbl(cols);
	}
	return dat;
}

/* randomly initialize weights*/
void randomize_weights(double** dat,size_t rows, size_t cols) {
	size_t r, c;
	for (r = 0; r != rows; ++r) {
		for (c = 0; c != cols; ++c) {
			dat[r][c] = dpn1();
		}
	}
}

/* use zero to initialize weights*/
void zero_weights(double** dat, size_t rows, size_t cols) {
	size_t r, c;
	for (r = 0; r != rows; ++r) {
		for (c = 0; c != cols; ++c) {
			dat[r][c] = 0.0;
		}
	}
}

BPNN::BPNN(size_t n_in, size_t n_hidden, size_t n_out){
	input_n = n_in;
	hidden_n = n_hidden;
	output_n = n_out;

	input_units = alloc_1d_dbl(n_in + 1u);
	hidden_units = alloc_1d_dbl(n_hidden + 1u);
	output_units = alloc_1d_dbl(n_out + 1u);

	hidden_delta = alloc_1d_dbl(n_hidden + 1);
	output_delta = alloc_1d_dbl(n_out + 1);
	target = alloc_1d_dbl(n_out + 1);

	input_weights = alloc_2d_dbl(n_in + 1, n_hidden + 1);
	hidden_weights = alloc_2d_dbl(n_hidden + 1, n_out + 1);

	input_prev_weights = alloc_2d_dbl(n_in + 1, n_hidden + 1);
	hidden_prev_weights = alloc_2d_dbl(n_hidden + 1, n_out + 1);

	randomize_weights(input_weights,n_in,n_hidden);
	randomize_weights(hidden_weights,n_hidden,n_out);
	zero_weights(input_prev_weights,n_in,n_hidden);
	zero_weights(hidden_prev_weights,n_hidden,n_out);

	return;		//done.
}

BPNN::~BPNN() {
	delete[] input_units;
	delete[] hidden_units;
	delete[] output_units;

	delete[] hidden_delta;
	delete[] output_delta;
	delete[] target;

	for (size_t i = 0; i != input_n; ++i) {
		delete[] input_weights[i];
		delete[] input_prev_weights[i];
	}
	delete[] input_weights;
	delete[] input_prev_weights;

	for (size_t i = 0; i != hidden_n; ++i) {
		delete[] hidden_weights[i];
		delete[] hidden_prev_weights[i];
	}
	delete[] hidden_weights;
	delete[] hidden_prev_weights;
}

void BPNN::layerforward(double* l1, double* l2, double** conn, size_t n1, size_t n2) {
	double sum; size_t j, k;
	l1[0] = 1.0;

	for (j = 1; j != n2 + 1; ++j) {
		sum = 0.0;
		for (k = 0; k != n1 + 1; ++k) {
			sum += conn[k][j] * l1[k];
		}
		l2[j] = squash(sum);
	}
}

void BPNN::output_error(double* delta,double* target,double* output,
	size_t nj, double* err) {
	size_t j;
	double o, t, errsum = 0.0;

	for (j = 1; j != nj + 1; ++j) {
		o = output[j];
		t = target[j];
		delta[j] = o * (1.0 - o) * (t - o);
		errsum += fabs(delta[j]);
	}
	*err = errsum;
}

void BPNN::hidden_error(double* delta_h, size_t nh, double* delta_o,
	size_t no, double** who, double* hidden, double* err) {
	size_t j, k;
	double h, sum, errsum = 0.0;

	for (j = 1; j <= nh; ++j) {
		h = hidden[j];
		sum = 0.0;
		for (k = 1; k <= no; ++k) {
			sum += delta_o[k] * who[j][k];
		}
		delta_h[j] = h * (1.0 - h) * sum;
		errsum += fabs(delta_h[j]);
	}
	*err = errsum;
}

void BPNN::adjust_weights(double* delta, size_t ndelta, double* ly, size_t nly,
	double** w, double** oldw, double eta, double momentum) {
	double new_dw;
	size_t k, j;

	ly[0] = 1.0;
	for (j = 1; j != ndelta + 1; ++j) {
		for (k = 0; k != nly + 1; ++k) {
			new_dw = ((eta * delta[j] * ly[k]) + (momentum * oldw[k][j]));
			w[k][j] += new_dw;
			oldw[k][j] = new_dw;
		}
	}
}

void BPNN::feed_forward() {
	size_t in, hid, out;

	in = this->input_n;
	hid = this->hidden_n;
	out = this->output_n;

	BPNN::layerforward(input_units, hidden_units, input_weights, in, hid);
	BPNN::layerforward(hidden_units, output_units, hidden_weights, hid, out);
}

void BPNN::train(double eta, double momentum, double* eo, double* eh) {
	size_t in, hid, out;
	double out_err, hid_err;

	in = this->input_n;
	hid = this->hidden_n;
	out = this->output_n;

	BPNN::layerforward(this->input_units, this->hidden_units, this->input_weights, in, hid);
	BPNN::layerforward(this->hidden_units, this->output_units, this->hidden_weights, hid, out);

	BPNN::output_error(this->output_delta, this->target, this->output_units, out, &out_err);
	BPNN::hidden_error(this->hidden_delta, hid, this->output_delta, out,
		this->hidden_weights, this->hidden_units, &hid_err);
	*eo = out_err;
	*eh = hid_err;

	BPNN::adjust_weights(this->output_delta, out, this->hidden_units, hid, this->hidden_weights,
		this->hidden_prev_weights, eta, momentum);
	BPNN::adjust_weights(this->hidden_delta, hid, this->input_units, in, this->input_weights,
		this->input_prev_weights, eta, momentum);
}
