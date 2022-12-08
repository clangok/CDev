/**
 * 链表栈函数头
 */
#ifndef STACK_LINK_H
#define STACK_LINK_H

#include <stdlib.h>

#define STACK_LENGTH_MAX 10000

typedef void *StackValue;
typedef struct _stackNode StackNode;
typedef struct _stack Stack;

struct _stackNode
{
    StackValue data;
    StackNode *next;
};

struct _stack
{
    StackNode *head;         // 头节点指针
    unsigned int length;     // 栈长度
    unsigned int usedLength; // 已使用栈长度
};

/**
 * 函数声明列表#############################################################################
 */
Stack *stack_new(unsigned int len);
StackValue stack_peek(Stack *stack);
StackValue stack_pop(Stack *stack);
int stack_push(Stack *stack, StackValue val);
int stack_isempty(Stack *stack);
int stack_size(Stack *stack);
int stack_clear(Stack *stack);
void stack_free(Stack *stack);

/**
 * 函数实现列表#############################################################################
 */

/// @brief 
/// @param len 
/// @return 
Stack *stack_new(unsigned int len)
{
    if ((int)len <= 0 || len > STACK_LENGTH_MAX)
    {
        return NULL;
    }

    Stack *stack = (Stack *)malloc(sizeof(Stack));
    if (stack == NULL)
    {
        return NULL;
    }

    stack->head = NULL;
    stack->length = len;
    stack->usedLength = 0;

    return stack;
}

/// @brief 
/// @param stack 
/// @return 
StackValue stack_peek(Stack *stack)
{
    StackValue result = NULL;
    if (stack != NULL && stack->usedLength > 0)
    {
        result = stack->head->data;
    }
    return result;
}

/// @brief 
/// @param stack 
/// @return 
StackValue stack_pop(Stack *stack)
{
    StackValue result = NULL;
    if (stack != NULL && stack->usedLength > 0)
    {
        result = stack->head->data;

        StackNode *node = stack->head;
        stack->head = stack->head->next;
        stack->usedLength--;
        free(node);
    }
    return result;
}

/// @brief 
/// @param stack 
/// @param val 
/// @return 
int stack_push(Stack *stack, StackValue val)
{
    int result = -1;
    if (stack != NULL && stack->usedLength < stack->length)
    {
        StackNode *node = (StackNode *)malloc(sizeof(StackNode));
        if (node != NULL)
        {
            node->data = val;
            node->next = stack->head;
            stack->head = node;
            stack->usedLength++;
            result = 1;
        }
    }
    return result;
}

/// @brief 
/// @param stack 
/// @return 
int stack_isempty(Stack *stack)
{
    return (stack != NULL) ? 0 : 1;
}

/// @brief 
/// @param stack 
/// @return 
int stack_size(Stack *stack)
{
    return (stack != NULL) ? stack->usedLength : 0;
}

/// @brief 
/// @param stack 
/// @return 
int stack_clear(Stack *stack)
{
    int result = 0;
    if (stack != NULL && stack->usedLength > 0)
    {
        while (stack->head != NULL)
        {
            StackNode *node = stack->head;
            stack->head = stack->head->next;
            free(node);
            result++;
        }
        stack->head = NULL;
        stack->usedLength = 0;
    }
    return result;
}

/// @brief 
/// @param stack 
void stack_free(Stack *stack)
{
    stack_clear(stack);
    free(stack);
}

#endif // STACK_LINK_H