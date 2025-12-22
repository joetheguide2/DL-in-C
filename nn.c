
#define NN_IMPLEMENTATION
#include "nn.h"


int main(void){
  Mat m = mat_alloc(2, 2);
  Mat m2 = mat_alloc(2, 2);
  Mat m3 = mat_alloc(2, 2);

 
  mat_fill(m , 2);
  mat_fill(m2, 1);
  mat_sum(m , m2);
  MAT_PRINT(m);

  mat_dot(m3, m2, m);
  return 0;
 
  
}
