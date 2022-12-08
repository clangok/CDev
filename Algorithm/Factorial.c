/**
 * 阶乘
 */
#include <stdio.h>

//阶乘结果缓存
static long long arr[25] = {1, 1, 0};

/// @brief 递归实现阶乘
/// @param n n=21超出long long范围
/// @return 
long long Factorial(int n)
{
    long long result = 0;
    if (n <= 1)
    {
        result = arr[n];
    }
    else
    {
        if (arr[n] != 0)
        {
            result = arr[n];
        }
        else
        {
            arr[n] = n * Factorial(n - 1);
            result = arr[n];
        }
    }
    return result;
}

int main()
{
    //计算1～20阶乘并打印
    for (int i = 1; i < 21; i++)
    {
        printf("Factorial(%d)=%lld\n", i, Factorial(i));
    }
}