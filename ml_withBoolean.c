#include <stdio.h>  // for printf
#include <stdlib.h> // for rand
#include <time.h>   // for time

float train[][3] = {
  // {x1, x2, y} (OR function)
  {0, 0, 0},
  {0, 1, 1},
  {1, 0, 1},
  {1, 1, 1},
};
#define train_count (sizeof(train)/sizeof(train[0]))

float rand_float(void)
{
  return ((float)rand() / (float)RAND_MAX);
}

float cost_func(float w1, float w2)
{
  float result = 0.0f;
  for (size_t i = 0; i < train_count; ++i) {
    float x1 = train[i][0];
    float x2 = train[i][1];
    float y = x1 * w1 + x2 * w2;
    float loss = y - train[i][2];
    result += loss*loss;
  }
  return result /= train_count;
}

int main(int argc, char *argv[])
{
  srand(time(0));
  float w1 = rand_float();
  float w2 = rand_float();

  float eps  = 1e-3;
  float rate = 1e-3;

  for (int i = 0; i < 2000; ++i) {
    float dw1 = (cost_func(w1 + eps, w2) - cost_func(w1, w2)) / eps;
    float dw2 = (cost_func(w1, w2 + eps) - cost_func(w1, w2)) / eps;

    w1 -= rate * dw1;
    w2 -= rate * dw2;
  }

  printf("w1: %f, w2: %f, f(0, 1) = %f\n", w1, w2, (w1*0 + w2*1));

  return 0;
}
