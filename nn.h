#ifndef NN_H_
#define NN_H_

#include<time.h>
#include<stddef.h>
#include<stdio.h>
#include<math.h>
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
  size_t stride;
  size_t cols;
  double *es;
} Mat;

#define MAT_AT(m, i, j) (m).es[(i)*(m).stride + (j)]
#define MAT_PRINT(m) mat_print(m, #m)

double sigmoid(double x);
Mat mat_alloc(size_t rows, size_t cols);
void mat_dot(Mat dst, Mat a, Mat b);
Mat mt_row(Mat m , size_t row);
void mat_copy(Mat dst, Mat src);
void mat_sum(Mat dst, Mat a);
void mat_print(Mat m, const char *name);
double rand_double(void);
void mat_rand(Mat m , double low , double high);
void mat_fill(Mat dst, double x);
void mat_sig(Mat m);


#endif //NN_H_

#ifdef NN_IMPLEMENTATION

double sigmoid(double x){
  return 1.0/(1.0 + exp(-x));
}

double rand_double(void){
  return (double) rand()/ (double)RAND_MAX;
}

void mat_fill(Mat dst, double x){
  for(size_t i = 0; i < dst.rows; ++i){
    for(size_t j= 0; j < dst.cols; j ++){
      MAT_AT(dst, i, j) = x; 
    }
  }  

}

Mat mat_alloc(size_t rows, size_t cols){
  Mat m;
  m.rows = rows;
  m.cols = cols;
  m.stride = cols;
  m.es = NN_MALLOC(sizeof(*m.es)*rows*cols);
  NN_ASSERT(m.es != NULL);
  return m;
}

void mat_dot(Mat dst, Mat a, Mat b){

  NN_ASSERT(a.cols == b.rows);
  NN_ASSERT(dst.rows == a.rows);
  NN_ASSERT(dst.cols == b.cols);
  size_t n = a.cols;
  for(size_t i=0; i<dst.rows; i++){
    for(size_t j=0 ; j < dst.cols; ++j){
      MAT_AT(dst, i, j) = 0;
      for(size_t k = 0; k <  n; ++k){
	MAT_AT(dst, i, j) += MAT_AT(a, i, k) * MAT_AT(b, k, j);
      }
    }
  }
  
}

Mat mat_row(Mat m , size_t row){
  return (Mat) {
    .rows = 1,
    .cols = m.cols,
    .stride = m.stride,
    .es = &MAT_AT(m, row, 0),
  };

}

void mat_copy(Mat dst, Mat src){
  NN_ASSERT(dst.rows == src.rows && dst.cols == src.cols);
  for(size_t i = 0; i < dst.rows; ++i){
    for(size_t j= 0; j < dst.cols; j ++){
      MAT_AT(dst, i, j) = MAT_AT(src, i, j);
    }
  }

}

void mat_sum(Mat dst, Mat a){
  NN_ASSERT(dst.rows == a.rows && dst.cols == a.cols);
  for(size_t i = 0; i < dst.rows; ++i){
    for(size_t j= 0; j < dst.cols; j ++){
      MAT_AT(dst, i, j) += MAT_AT(a, i, j); 
    }
  }
  
}

void mat_sig(Mat m){
  for(size_t i = 0; i < m.rows; ++i){
    for(size_t j= 0; j < m.cols; j ++){
      MAT_AT(m, i, j) = sigmoid(MAT_AT(m, i , j));
    }
  }

}

void mat_rand(Mat m, double low, double high){
  for(size_t i = 0; i < m.rows; ++i){
    for(size_t j= 0; j < m.cols; j ++){
      MAT_AT(m, i, j) = rand_double()*(high - low) + low;
    }
  }
}


void mat_print(Mat m, const char *name){

  printf("%s = [\n", name);
  for(size_t i = 0; i < m.rows; ++i){
    for (size_t j=0; j < m.cols; ++j){
      printf("\t%f ", MAT_AT(m, i, j));
    }
    printf("\n");
  }
  
  printf("]\n");
}


#endif //NN_IMPLEMENTATION
