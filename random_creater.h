#ifndef RANDOM_CREATER_H
#define RANDOM_CREATER_H

#include <cstddef>
/*I may need the rand() function in it*/
#include <cstdlib>
#include <stdexcept>
#include <fstream>

class random_creater{
public:
   
   /*dump rows * cols of random number in range(0,1) into a file
        the file is organized like this:
        rows cols
        a11 a12 a13 ....
        a21 a22 a23 ...
        ....
   */
   static void dump(size_t rows, size_t cols, const char* filename){
       std::ofstream out(filename);
       out << rows << ' ' << cols << std::endl;
       for(size_t r=0;r!=rows;++r){
            for(size_t c=0;c!=cols;++c){
                out << random_creater::RAND() << ' '; 
            }
            out << std::endl;
       }
   }
   /*load rows*cols of data from a .txt file, return an 2-dim array
    remember to free it when you are done. */
    static double** load(const char* filename){
        std::ifstream in(filename);
        size_t rows, cols;
        in >> rows >> cols; //load rows and cols
        double** dat = new double*[rows];
        for(size_t r=0;r!=rows;++r){
            dat[r] = new double[cols];
            if(dat[r]==0) throw std::domain_error("random_creater: allocation err");
            for(size_t c=0;c!=cols;++c){
                in >> dat[r][c];
            }
        }

        return dat;
    }

    /*deallocate an 2-dim array*/
    static void free(double** dat,size_t rows){
        for(size_t r=0;r!=rows;++r) delete[] dat[r];
        delete[] dat;
        return;
    }
   

private:
    static double RAND(){
        return (double)rand()/(double)(RAND_MAX);
    }
}
;

#endif//RANDOM_CREATER_H
