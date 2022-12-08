/**
 * 数组实现的队列
 */

#ifndef ARRAY_QUEUE_H
#define ARRAY_QUEUE_H

#include <stdlib.h>

// 队列长度最大值
#define ARRAY_QUEUE_LENGTH_MAX 10000

// 队列元素的值类型
typedef void *ArrayQueueValue;
// 队列类型
typedef struct _arrayQueue ArrayQueue;

// 队列结构
struct _arrayQueue
{
    ArrayQueueValue *data;
    unsigned int length;
    unsigned int usedLength;
};

/**
 * 函数声明列表#############################################################################
 */
ArrayQueue *arrqueue_new(unsigned int len);
ArrayQueueValue arrqueue_peek(ArrayQueue *queue);
ArrayQueueValue arrqueue_pop(ArrayQueue *queue);
int arrqueue_push(ArrayQueue *queue, ArrayQueueValue val);
int arrqueue_isempty(ArrayQueue *queue);
int arrqueue_size(ArrayQueue *queue);
int arrqueue_clear(ArrayQueue *queue);
void arrqueue_free(ArrayQueue *queue);
/**
 * 函数实现列表#############################################################################
 */

/// @brief 创建新队列
/// @param len
/// @return
ArrayQueue *arrqueue_new(unsigned int len)
{
    if ((int)len <= 0 || len > ARRAY_QUEUE_LENGTH_MAX)
    {
        return NULL;
    }

    ArrayQueue *queue = (ArrayQueue *)malloc(sizeof(ArrayQueue));
    if (queue == NULL)
    {
        return NULL;
    }
    queue->data = (ArrayQueueValue *)malloc(sizeof(ArrayQueueValue) * len);
    if (queue->data == NULL)
    {
        free(queue);
        return NULL;
    }
    queue->length = len;
    queue->usedLength = 0;

    return queue;
}

/// @brief 查看队列头
/// @param queue
/// @return
ArrayQueueValue arrqueue_peek(ArrayQueue *queue)
{
    ArrayQueueValue result = NULL;
    if (queue != NULL && queue->usedLength > 0)
    {
        result = queue->data[queue->usedLength - 1];
    }
    return result;
}

/// @brief 数据出队列
/// @param queue
/// @return
ArrayQueueValue arrqueue_pop(ArrayQueue *queue)
{
    ArrayQueueValue result = NULL;
    if (queue != NULL && queue->usedLength > 0)
    {
        result = queue->data[queue->usedLength - 1];
        queue->data[queue->usedLength - 1] = NULL;
        queue->usedLength--;
    }
    return result;
}

/// @brief 数据添加到队列
/// @param queue
/// @param val
/// @return
int arrqueue_push(ArrayQueue *queue, ArrayQueueValue val)
{
    int result = -1;
    if (queue != NULL && queue->usedLength < queue->length)
    {
        for (int i = queue->usedLength - 1; i >= 0; i--)
        {
            queue->data[i + 1] = queue->data[i];
        }
        queue->data[0] = val;
        queue->usedLength++;
        result = 1;
    }
    return result;
}

/// @brief 判断队列指针是否为空
/// @param queue
/// @return
int arrqueue_isempty(ArrayQueue *queue)
{
    return (queue != NULL) ? 0 : 1;
}

/// @brief 队列长度
/// @param queue
/// @return
int arrqueue_size(ArrayQueue *queue)
{
    return (queue != NULL) ? queue->usedLength : 0;
}

/// @brief 清空队列数据
/// @param queue
/// @return
int arrqueue_clear(ArrayQueue *queue)
{
    int result = 0;
    if (queue != NULL || queue->usedLength > 0)
    {
        for (int i = 0; i < queue->usedLength; i++)
        {
            queue->data[i] = NULL;
            result++;
        }
        queue->usedLength = 0;
    }
    return result;
}

/// @brief 释放内存
/// @param queue
void arrqueue_free(ArrayQueue *queue)
{
    arrqueue_clear(queue);
    free(queue->data);
    free(queue);
}

#endif // ARRAY_QUEUE_H