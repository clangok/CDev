/**
 * 数组实现的栈
 */

#ifndef ARRAY_STACK_H
#define ARRAY_STACK_H

#include <stdlib.h>

// 栈长度最大值
#define ARRAY_STACK_LENGTH_MAX 10000

// 栈元素的值类型
typedef void *ArrayStackValue;
// 栈类型
typedef struct _arrayStack ArrayStack;

// 栈结构
struct _arrayStack
{
    ArrayStackValue *data;
    unsigned int length;
    unsigned int usedLength;
};

/**
 * 函数声明列表#############################################################################
 */
ArrayStack *arrstack_new(unsigned int len);
ArrayStackValue arrstack_peek(ArrayStack *stack);
ArrayStackValue arrstack_pop(ArrayStack *stack);
int arrstack_push(ArrayStack *stack, ArrayStackValue val);
int arrstack_isempty(ArrayStack *stack);
int arrstack_size(ArrayStack *stack);
int arrstack_clear(ArrayStack *stack);
void arrstack_free(ArrayStack *stack);

/**
 * 函数实现列表#############################################################################
 */

/// @brief 创建新栈
/// @param len
/// @return
ArrayStack *arrstack_new(unsigned int len)
{
    if ((int)len <= 0 || len > ARRAY_STACK_LENGTH_MAX)
    {
        return NULL;
    }

    ArrayStack *stack = (ArrayStack *)malloc(sizeof(ArrayStack));
    if (stack == NULL)
    {
        return NULL;
    }
    stack->data = (ArrayStackValue *)malloc(sizeof(ArrayStackValue) * len);
    if (stack->data == NULL)
    {
        free(stack);
        return NULL;
    }
    stack->length = len;
    stack->usedLength = 0;

    return stack;
}

/// @brief 查看栈头
/// @param stack
/// @return
ArrayStackValue arrstack_peek(ArrayStack *stack)
{
    ArrayStackValue result = NULL;
    if (stack != NULL && stack->usedLength > 0)
    {
        result = stack->data[stack->usedLength - 1];
    }
    return result;
}

/// @brief 数据出栈
/// @param stack
/// @return
ArrayStackValue arrstack_pop(ArrayStack *stack)
{
    ArrayStackValue result = NULL;
    if (stack != NULL && stack->usedLength > 0)
    {
        result = stack->data[stack->usedLength - 1];
        stack->data[stack->usedLength - 1] = NULL;
        stack->usedLength--;
    }
    return result;
}

/// @brief 数据入栈
/// @param stack
/// @param val
/// @return
int arrstack_push(ArrayStack *stack, ArrayStackValue val)
{
    int result = -1;
    if (stack != NULL && stack->usedLength < stack->length)
    {
        stack->data[stack->usedLength] = val;
        stack->usedLength++;
        result = 1;
    }
    return result;
}

/// @brief 栈指针是否为空
/// @param stack
/// @return
int arrstack_isempty(ArrayStack *stack)
{
    return (stack != NULL) ? 0 : 1;
}

/// @brief 栈长度
/// @param stack
/// @return
int arrstack_size(ArrayStack *stack)
{
    return (stack != NULL) ? stack->usedLength : 0;
}

/// @brief 清空栈数据
/// @param stack
/// @return
int arrstack_clear(ArrayStack *stack)
{
    int result = 0;
    if (stack != NULL || stack->usedLength > 0)
    {
        for (int i = 0; i < stack->usedLength; i++)
        {
            stack->data[i] = NULL;
            result++;
        }
        stack->usedLength = 0;
    }
    return result;
}

/// @brief 释放内存
/// @param stack
void arrstack_free(ArrayStack *stack)
{
    arrstack_clear(stack);
    free(stack->data);
    free(stack);
}

#endif // ARRAY_STACK_H