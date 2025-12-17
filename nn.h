#ifndef NN_H_
#define NN_H_

#include<time.h>
#include<stddef.h>
#include<stdio.h>
#ifndef NN_MALLOC
#include<stdlib.h>
#define NN_MALLOC malloc
#endif //NN_MALLOC

#ifndef NN_ASSERT
#include <assert.h>
#define NN_ASSERT assert
#endif //NN_ASSERT

typedef struct{
  size_t rows;
  size_t cols;
  double *es;
} Mat;

#define MAT_AT(m, i, j) (m).es[(i)*(m).cols + (j)]

Mat mat_alloc(size_t rows, size_t cols);
void mat_dot(Mat dst, Mat a, Mat b);
void mat_sum(Mat dst, Mat a);
void mat_print(Mat m);
double rand_double(void);
void mat_rand(Mat m , double low , double high);

#endif //NN_H_

#ifdef NN_IMPLEMENTATION

double rand_double(void){
  return (double) rand()/ (double)RAND_MAX;
}

Mat mat_alloc(size_t rows, size_t cols){
  Mat m;
  m.rows = rows;
  m.cols = cols;
  m.es = NN_MALLOC(sizeof(*m.es)*rows*cols);
  NN_ASSERT(m.es != NULL);
  return m;
};
void mat_dot(Mat dst, Mat a, Mat b){
  (void) dst;
  (void) a;
  (void) b;

};

void mat_sum(Mat dst, Mat a){
  NN_ASSERT(dst.rows == a.rows && dst.cols == a.cols);
  for(size_t i = 0; i < dst.rows; ++i){
    for(size_t j= 0; j < dst.cols; j ++){
      MAT_AT(dst, i, j) += MAT_AT(a, i, j); 
    }
  }
  
};

void mat_rand(Mat m, double low, double high){
  for(size_t i = 0; i < m.rows; ++i){
    for(size_t j= 0; j < m.cols; j ++){
      MAT_AT(m, i, j) = rand_double()*(high - low) + low;
    }
  }
}


void mat_print(Mat m){
  for(size_t i = 0; i < m.rows; ++i){
    for (size_t j=0; j < m.cols; ++j){
      printf("%f ", MAT_AT(m, i, j));
    }
    printf("\n");
  }
  
  (void) m;
};


#endif //NN_IMPLEMENTATION
