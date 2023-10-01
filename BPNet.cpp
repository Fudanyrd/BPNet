#include "BPNet.h"

using std::domain_error;
using std::endl;            using std::ifstream;
using std::ofstream;

double* construct_1d(size_t length){
    double* res = new double[length]{0.0};
    if(res==0) throw domain_error("construct_1d: allocation failed");
    return res; 
}

double** construct_2d(size_t rows,size_t cols){
    double** res = new double*[rows];
    if(res == 0) throw domain_error("construct_2d: allocation failed");
    
    for(size_t r = 0;r!=rows;++r){
        res[r] = construct_1d(cols);
    }

    return res;
}

/* return a random number in range[0,1]*/
double drnd() {
	return ((double)rand()) / ((double)RAND_MAX);
}

/* return a double random number in range[-1,1].*/
double dpn1() {
	return drnd() * 2.0 - 1.0;
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

/* operating function(currently S function) */
double squash(double x) {
	return 1.0 / (1.0 + exp(-x));
}

void InputLayer::layerforward(BPBase* next){
    double sum = 0.0;
    size_t j, k;

    this->units[0] = 1.0;       //set value.
    for(j=1;j<=next->Neuros;++j){
        sum = 0;
        for(k = 0;k<=this->Neuros;++k){
            sum+=this->weights[k][j]*this->units[k];
        }
        next->units[j] = squash(sum);
    }
}
void HiddenLayer::layerforward(BPBase* next){
    double sum = 0.0;
    size_t j, k;

    this->units[0] = 1.0;       //set value.
    for(j=1;j<=next->Neuros;++j){
        sum = 0;
        for(k = 0;k<=this->Neuros;++k){
            sum+=this->weights[k][j]*this->units[k];
        }
        next->units[j] = squash(sum);
    }
}

void InputLayer::adjust_weights(double rate,double momentum,BPBase* next){
    double new_dw;
    size_t j, k;

    this->units[0] = 1.0; 
    for(j=1;j<=next->Neuros;++j){
        for(k=0;k<=this->Neuros;++k){
            new_dw = ((rate*next->delta[j]*this->units[k])+(momentum*this->weights[k][j]));
            this->weights[k][j] += new_dw;
            this->prev_weights[k][j] = new_dw;
        }
    }
}
void HiddenLayer::adjust_weights(double rate,double momentum,BPBase* next){
    double new_dw;
    size_t j, k;

    this->units[0] = 1.0; 
    for(j=1;j<=next->Neuros;++j){
        for(k=0;k<=this->Neuros;++k){
            new_dw = ((rate*next->delta[j]*this->units[k])+(momentum*this->weights[k][j]));
            this->weights[k][j] += new_dw;
            this->prev_weights[k][j] = new_dw;
        }
    }
}

double HiddenLayer::error(BPBase* next){
    size_t j, k;
    double h, sum, errsum=0.0;

    for(j=1;j<=this->Neuros;++j){
        h = this->units[j];
        sum = 0.0;
        for(k=1;k<=next->Neuros;++k){
            sum+=next->delta[k] * this->weights[j][k];
        }
        this->delta[j] = h*(1.0-h)*sum;
        errsum+=fabs(this->delta[j]);
    }

    return errsum; 
}
/* next should be zero since there's no layer after the output layer.*/
double OutputLayer::error(BPBase* next){
    double o, t, errsum = 0.0;
    size_t j;
    for(j=1;j<=this->Neuros;++j){
        o=this->units[j];
        t = this->target[j];
        this->delta[j] = o*(1.0-o)*(t-o);
        errsum+=fabs(delta[j]);
    }

    return errsum;
}

double train(Vec<BPBase*>& layers,double rate, double momentum,
    double* inputs, double* targets){

    static size_t sz = layers.size();
    /* put input data into InputLayer::units. */
    for(size_t i=1;i<=layers[0]->Neuros;++i){
        layers[0]->units[i] = inputs[i-1];
    }
    /*put targets into OutputLayer::target. */
    for(size_t i=1;i<=layers[sz-1]->Neuros;++i){
        layers[sz-1]->target[i] = targets[i-1]; 
    }
    /* input activation */
    for(size_t i = 0;i!=sz-1;++i){
        layers[i]->layerforward(layers[i+1]);
    }

    /*calculate error value*/
    double res= layers[sz-1]->error(0);
    for(size_t i=sz-2;i!=0;--i){
        layers[i]->error(layers[i+1]);
    }
    /*adjust weights of each layer*/
    for(size_t i=sz-2;i!=0;--i){
        layers[i]->adjust_weights(rate,momentum, layers[i+1]);
    }
    layers[0]->adjust_weights(rate, momentum, layers[1]);

    return res;
}

/* now that you have trained the network, you may want to test it using a given input.
*/
void test(Vec<BPBase*>& layers,double* inputs) {
    static size_t sz = layers.size();
    /* put input data into InputLayer::units. */
    for(size_t i=1;i<=layers[0]->Neuros;++i){
        layers[0]->units[i] = inputs[i-1];
    }
    /* input activation */
    for(size_t i = 0;i!=sz-1;++i){
        layers[i]->layerforward(layers[i+1]);
    }
    /* done. */
}

void InputLayer::dump(const char* filename){
    ofstream out(filename);
    for(size_t r=0;r!=this->Neuros;++r){
        for(size_t c=0;c!=this->branches;++c){
            out << this->weights[r][c] << ' ';
        }
        out << endl;
    }
}
void InputLayer::load(const char* filename){
    ifstream in(filename);
    for(size_t r=0;r!=this->Neuros;++r){
        for(size_t c=0;c!=this->branches;++c){
            in >> this->weights[r][c];
        }
    }
}

void HiddenLayer::dump(const char* filename){
    ofstream out(filename);
    for(size_t r=0;r!=this->Neuros;++r){
        for(size_t c=0;c!=this->branches;++c){
            out << this->weights[r][c] << ' ';
        }
        out << endl;
    }
}
void HiddenLayer::load(const char* filename){
    ifstream in(filename);
    for(size_t r=0;r!=this->Neuros;++r){
        for(size_t c=0;c!=this->branches;++c){
            in >> this->weights[r][c];
        }
    }
}