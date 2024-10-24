#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct {
    float or_w1;
    float or_w2;
    float or_b;

    float nand_w1;
    float nand_w2;
    float nand_b;

    float and_w1;
    float and_w2;
    float and_b;
} Xor;

float sigmoidf(float x)
{
    return 1.f / (1.f + expf(-x)); // exp = número de euler elevado ao parametro
}

float forward(Xor m, float x1, float x2)
{
    float a = sigmoidf(m.or_w1*x1 + m.or_w2*x2 + m.or_b);
    float b = sigmoidf(m.nand_w1*x1 + m.nand_w2*x2 + m.nand_b);
    return sigmoidf(a*m.and_w1 + b*m.and_w2 + m.and_b);
}

typedef float sample[3]; // associa um name a um tipo especificado

sample xor_train[] = {
    {0, 0, 0},
    {1, 0, 1},
    {0, 1, 1},
    {1, 1, 0},
};

sample *train = xor_train;
size_t train_count = 4;

float cost(Xor m)
{
    float result = 0.0f;
    for(size_t i = 0; i < train_count; i++) {
        float x1 = train[i][0];
        float x2 = train[i][1];
        float y = forward(m, x1, x2);
        float d = y-train[i][2];
        result += d*d;
    }
    result /= train_count;

    return result;
}

float rand_float(void)
{
    return (float)rand() / (float)RAND_MAX;
}

Xor rand_xor(void)
{
    Xor m;
    m.or_w1   = rand_float();
    m.or_w2   = rand_float();
    m.or_b    = rand_float();

    m.nand_w1 = rand_float();
    m.nand_w2 = rand_float();
    m.nand_b  = rand_float();
    
    m.and_w1  = rand_float();
    m.and_w2  = rand_float();
    m.and_b   = rand_float();

    return m;
}

void print_xor(Xor m)
{
    printf("or_w1 = %f\n", m.or_w1);
    printf("or_w2 = %f\n", m.or_w2);
    printf("or_b = %f\n", m.or_b);

    printf("nand_w1 = %f\n", m.nand_w1);
    printf("nand_w2 = %f\n", m.nand_w2);
    printf("nand_b = %f\n", m.nand_b);
    
    printf("and_w1 = %f\n", m.and_w1);
    printf("and_w2 = %f\n", m.and_w2);
    printf("and_b = %f\n", m.and_b);
}

int main(void)
{
    Xor m = rand_xor();
    print_xor(m);

    return 0;
}