/**
 * 斐波那契数列
*/
#include <stdio.h>

//缓存数组
static long long arr[100] = {0, 1, 1, 0};

/// @brief 递归+缓存实现的斐波那契数列
/// @param n n>93超出long long范围
/// @return 
long long Fibonacci(int n)
{
    long long result = 0;
    if (n <= 2)
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
            arr[n] = Fibonacci(n - 1) + Fibonacci(n - 2);
            result = arr[n];
        }
    }
    return result;
}


int main()
{
    //输出1～90斐波那契数列
    for (int i = 1; i < 93; i++)
    {
        printf("Fibonacci(%d)=%lld\n", i, Fibonacci(i));
    }
}