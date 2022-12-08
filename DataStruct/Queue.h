/**
 * 链表队列函数头
 */
#ifndef QUEUE_LINK_H
#define QUEUE_LINK_H

#include <stdlib.h>

#define QUEUE_LENGTH_MAX 10000

typedef void *QueueValue;
typedef struct _queueNode QueueNode;
typedef struct _queue Queue;

struct _queueNode
{
    QueueValue data;
    QueueNode *next;
};

struct _queue
{
    QueueNode *head;         // 头节点指针
    QueueNode *tail;         // 尾节点指针
    unsigned int length;     // 队列长度
    unsigned int usedLength; // 已使用队列长度
};

/**
 * 函数声明列表#############################################################################
 */
Queue *queue_new(unsigned int len);
QueueValue queue_peek(Queue *queue);
QueueValue queue_pop(Queue *queue);
int queue_push(Queue *queue, QueueValue val);
int queue_isempty(Queue *queue);
int queue_size(Queue *queue);
int queue_clear(Queue *queue);
void queue_free(Queue *queue);

/**
 * 函数实现列表#############################################################################
 */

/// @brief 
/// @param len 
/// @return 
Queue *queue_new(unsigned int len)
{
    if ((int)len <= 0 || len > QUEUE_LENGTH_MAX)
    {
        return NULL;
    }

    Queue *queue = (Queue *)malloc(sizeof(Queue));
    if (queue == NULL)
    {
        return NULL;
    }

    queue->head = NULL;
    queue->tail = NULL;
    queue->length = len;
    queue->usedLength = 0;

    return queue;
}

/// @brief 
/// @param queue 
/// @return 
QueueValue queue_peek(Queue *queue)
{
    QueueValue result = NULL;
    if (queue != NULL && queue->usedLength > 0)
    {
        result = queue->head->data;
    }
    return result;
}

/// @brief 
/// @param queue 
/// @return 
QueueValue queue_pop(Queue *queue)
{
    QueueValue result = NULL;
    if (queue != NULL && queue->usedLength > 0)
    {
        result = queue->head->data;

        QueueNode *node = queue->head;
        queue->head = queue->head->next;
        queue->usedLength--;
        free(node);
    }
    return result;
}

/// @brief 
/// @param queue 
/// @param val 
/// @return 
int queue_push(Queue *queue, QueueValue val)
{
    int result = -1;
    if (queue != NULL && queue->usedLength < queue->length)
    {
        QueueNode *node = (QueueNode *)malloc(sizeof(QueueNode));
        if (node != NULL)
        {
            node->data = val;
            node->next = NULL;
            if (queue->usedLength == 0)
            {
                queue->head = node;
            }
            else
            {
                queue->tail->next = node;
            }
            queue->tail = node;
            queue->usedLength++;

            result = 1;
        }
    }
    return result;
}

/// @brief 
/// @param queue 
/// @return 
int queue_isempty(Queue *queue)
{
    return (queue != NULL) ? 0 : 1;
}

/// @brief 
/// @param queue 
/// @return 
int queue_size(Queue *queue)
{
    return (queue != NULL) ? queue->usedLength : 0;
}

/// @brief
/// @param queue
/// @return
int queue_clear(Queue *queue)
{
    int result = 0;
    if (queue != NULL && queue->usedLength > 0)
    {
        while (queue->head != NULL)
        {
            QueueNode *node = queue->head;
            queue->head = queue->head->next;
            free(node);
            result++;
        }
        queue->head = NULL;
        queue->tail = NULL;
        queue->usedLength = 0;
    }
    return result;
}

/// @brief
/// @param queue
void queue_free(Queue *queue)
{
    queue_clear(queue);
    free(queue);
}

#endif // QUEUE_LINK_H