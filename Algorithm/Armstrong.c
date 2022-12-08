#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static int arm[100];
static int arm_size = 0;

void Arm3()
{
    int a, b, c;
    for (int i = 100; i <= 999; i++)
    {
        a = i / 100;
        b = (i % 100) / 10;
        c = i % 10;
        if (pow(a, 3) + pow(b, 3) + pow(c, 3) == i)
        {
            arm[arm_size] = i;
            arm_size++;
        }
    }
}

void Arm4()
{
    int a, b, c, d;
    for (int i = 1000; i <= 9999; i++)
    {
        a = i / 1000;
        b = (i % 1000) / 100;
        c = (i % 100) / 10;
        d = i % 10;

        // printf("%d,%d,%d,%d\n", a, b, c, d);
        if (pow(a, 4) + pow(b, 4) + pow(c, 4) + pow(d, 4) == i)
        {
            arm[arm_size] = i;
            arm_size++;
        }
    }
}

int main(void)
{
    Arm3();
    Arm4();
    for (int i = 0; i < arm_size; i++)
    {
        printf("%d ", arm[i]);
    }

    return 0;
}