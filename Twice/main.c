#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

float sigmoidf(float x)
{
    return 1.f / (1.f + expf(-x)); // exp = número de euler
}

float train[][3] = {
    {0, 0, 0},
    {1, 0, 1},
    {0, 1, 1},
    {1, 1, 1},
};
#define train_count (sizeof(train)/sizeof(train[0]))

float cost(float w1, float w2)
{
    float result = 0.0f;
    for(size_t i = 0; i < train_count; i++) {
        float x1 = train[i][0];
        float x2 = train[i][1];
        float y = sigmoidf(x1*w1 + x2*w2);
        float d = y-train[i][2];
        result += d*d;
    }
    result /= train_count;

    return result;
}

float rand_float(void)
{
    return (float) rand()/ (float) RAND_MAX;
}

int main(void)
{
    srand(time(0));
    float w1 = rand_float()*10 - 5;
    float w2 = rand_float()*10 - 5;

    float eps = 1e-1;
    float rate = 1e-1;

    for(size_t i = 0; i < 1000*1000; ++i) {
        float c = cost(w1, w2);

        float dw1 = (cost(w1 + eps, w2) - c) / eps;
        float dw2 = (cost(w1, w2 + eps) - c) / eps;
        w1 -= rate*dw1;
        w2 -= rate*dw2;
    }
    printf("w1 = %f, w2 = %f, c = %f\n", w1, w2, cost(w1, w2));

    return 0;
}