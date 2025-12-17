
#define NN_IMPLEMENTATION
#include "nn.h"


int main(void){
  Mat m = mat_alloc(2, 2);
  Mat m2 = mat_alloc(2, 2);
  mat_rand(m , 0, 1);
  mat_rand(m2, 0, 10);
  mat_print(m);
  mat_print(m2);
  mat_sum(m , m2);
  mat_print(m);
  return 0;
}
