/**
 * void*型数组操作函数
 */

#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <stdlib.h>

// 数组最大长度
#define ARRAY_LIST_LENGTH_MAX 10000
// 数组默认值
#define ARRAY_LIST_VALUE_DEFAULT NULL

// 数组值类型
typedef void *ArrayListValue;
// 数组类型
typedef struct _arrayList ArrayList;
// 比较函数
typedef int (*ArrayListCompare)(ArrayListValue, ArrayListValue);

// 数组结构
struct _arrayList
{
    ArrayListValue *data;
    ArrayListCompare compare;
    unsigned int length;
    unsigned int usedLength;
};

/**
 * 函数声明列表#############################################################################
 */
ArrayList *arrlist_new(unsigned int len, ArrayListCompare compare);
int arrlist_insert(ArrayList *arr, ArrayListValue val, unsigned int id);
int arrlist_append(ArrayList *arr, ArrayListValue *vals, unsigned int size);
int arrlist_modify(ArrayList *arr, ArrayListValue val, unsigned int id);
int arrlist_delete(ArrayList *arr, unsigned int id);
int arrlist_delete_range(ArrayList *arr, unsigned int start, unsigned int size);
ArrayListValue arrlist_get(ArrayList *arr, unsigned int id);
ArrayListValue *arrlist_get_range(ArrayList *arr, unsigned int start, unsigned int size);
int arrlist_adjust(ArrayList *arr, unsigned int size);
int arrlist_size(ArrayList *arr);
int arrlist_isnull(ArrayList *arr);
int arrlist_isempty(ArrayList *arr);
int arrlist_clear(ArrayList *arr);
void arrlist_free(ArrayList *arr);
void arrlist_reverse(ArrayList *arr);

/**
 * 函数实现列表#############################################################################
 */

ArrayList *arrlist_new(unsigned int len, ArrayListCompare compare)
{
    // 长度判断
    if ((int)len <= 0 || len > ARRAY_LIST_LENGTH_MAX || compare == NULL)
    {
        return NULL;
    }

    // 分配数组内存
    ArrayList *array = (ArrayList *)malloc(sizeof(ArrayList));
    if (array == NULL)
    {
        return NULL;
    }

    // 分配数组数据内存
    array->data = (ArrayListValue *)malloc(sizeof(ArrayListValue) * len);
    if (array->data == NULL)
    {
        free(array);
        return NULL;
    }
    array->length = len;
    array->usedLength = 0;
    array->compare = compare;

    // 所有数组元素赋值为默认值
    for (int i = 0; i < len; i++)
    {
        array->data[i] = ARRAY_LIST_VALUE_DEFAULT;
    }

    return array;
}

/// @brief 下标指定的位置插入元素
/// @param arr 
/// @param val 
/// @param id 
/// @return 
int arrlist_insert(ArrayList *arr, ArrayListValue val, unsigned int id)
{
    if (arr == NULL || (int)id < 0 || id > arr->usedLength)
    {
        return -1;
    }
    if (arr->usedLength >= arr->length && arrlist_adjust(arr, 1) < 0)
    {
        return -1;
    }

    if (id < arr->usedLength)
    {
        for (int i = arr->usedLength - 1; i >= id && i >= 0; i--)
        {
            arr->data[i + 1] = arr->data[i];
        }
    }
    arr->data[id] = val;
    arr->usedLength++;

    return 1;
}

/// @brief 批量追加
/// @param arr 
/// @param vals 
/// @param size 
/// @return 
int arrlist_append(ArrayList *arr, ArrayListValue *vals, unsigned int size)
{
    if (arr == NULL || (int)size < 0)
    {
        return -1;
    }
    if (arr->usedLength + size >= arr->length && arrlist_adjust(arr, arr->usedLength + size - arr->length) < 0)
    {
        return -1;
    }

    for (int i = 0; i < size; i++)
    {
        arr->data[arr->usedLength + i] = vals[i];
    }
    arr->usedLength += size;
    return 1;
}

/// @brief 修改下标指定的元素的值
/// @param arr 
/// @param val 
/// @param id 
/// @return 
int arrlist_modify(ArrayList *arr, ArrayListValue val, unsigned int id)
{
    int result = -1;
    if (arr != NULL && arr->usedLength > 0 && (int)id >= 0 && id < arr->usedLength)
    {
        arr->data[id] = val;
        result = 1;
    }
    return result;
}

/// @brief 删除下标指定的数组元素
/// @param arr 
/// @param id 
/// @return 
int arrlist_delete(ArrayList *arr, unsigned int id)
{
    int result = -1;
    if (arr != NULL && arr->usedLength > 0 && (int)id >= 0 && id < arr->usedLength)
    {
        for (int i = id; i < arr->usedLength - 1; i++)
        {
            arr->data[i] = arr->data[i + 1];
        }
        arr->data[arr->usedLength - 1] = ARRAY_LIST_VALUE_DEFAULT;
        arr->usedLength--;
        result = 1;
    }
    return result;
}

/// @brief 删除指定范围的数组元素
/// @param arr 
/// @param start 
/// @param size 
/// @return 
int arrlist_delete_range(ArrayList *arr, unsigned int start, unsigned int size)
{
    int result = 0;
    if (arr != NULL && arr->usedLength > 0 && (int)start >= 0 && (int)size > 0 && start + size < arr->usedLength)
    {
        for (int i = 0; i < size; i++)
        {
            if (arrlist_delete(arr, start) > 0)
            {
                result++;
            }
        }
    }
    return result;
}

/// @brief 获取下标指定的元素的数据
/// @param arr 
/// @param id 
/// @return 
ArrayListValue arrlist_get(ArrayList *arr, unsigned int id)
{
    ArrayListValue result = ARRAY_LIST_VALUE_DEFAULT;
    if (arr != NULL && arr->usedLength > 0 && (int)id >= 0 && id < arr->usedLength)
    {
        result = arr->data[id];
    }
    return result;
}

/// @brief 获取指定范围的数组元素
/// @param arr 
/// @param start 
/// @param size 
/// @return 
ArrayListValue *arrlist_get_range(ArrayList *arr, unsigned int start, unsigned int size)
{
    ArrayListValue *result = NULL;
    if (arr != NULL && arr->usedLength > 0 && (int)start >= 0 && (int)size > 0 && start + size < arr->usedLength)
    {
        result = (ArrayListValue *)malloc(sizeof(ArrayListValue) * size);
        if (result != NULL)
        {
            for (int i = 0; i < size; i++)
            {
                result[i] = arr->data[start + i];
            }
        }
    }
    return result;
}

/// @brief 调整数组长度
/// @param arr 
/// @param size 
/// @return 
int arrlist_adjust(ArrayList *arr, unsigned int size)
{
    int result = -1;
    if (arr != NULL && (int)size > 0 && arr->length + size <= ARRAY_LIST_LENGTH_MAX)
    {
        int len = arr->length + size;
        arr->data = (ArrayListValue *)realloc(arr->data, sizeof(ArrayListValue) * len);
        if (arr->data != NULL)
        {
            arr->length = len;
            result = 1;
        }
    }
    return result;
}

/// @brief 数组长度
/// @param arr 
/// @return 
int arrlist_size(ArrayList *arr)
{
    return (arr != NULL) ? arr->usedLength : 0;
}

/// @brief 判断数组指针是否为空
/// @param arr 
/// @return 
int arrlist_isnull(ArrayList *arr)
{
    return (arr == NULL) ? 1 : 0;
}

/// @brief 判断数组数据是否为空
/// @param arr 
/// @return 
int arrlist_isempty(ArrayList *arr)
{
    return (arr != NULL && arr->usedLength == 0) ? 1 : 0;
}

/// @brief 清空数据
/// @param arr 
/// @return 
int arrlist_clear(ArrayList *arr)
{
    int result = 0;
    if (arr != NULL && arr->usedLength > 0)
    {
        for (int i = 0; i < arr->usedLength; i++)
        {
            arr->data[i] = ARRAY_LIST_VALUE_DEFAULT;
            result++;
        }
        arr->usedLength = 0;
    }
    return result;
}

/// @brief 释放内存
/// @param arr 
void arrlist_free(ArrayList *arr)
{
    arrlist_clear(arr);
    free(arr->data);
    free(arr);
}

/// @brief 数组反转
/// @param arr 
void arrlist_reverse(ArrayList *arr)
{
    if (arr != NULL)
    {
        ArrayListValue tmp;
        if (arr->usedLength == 2)
        {
            tmp = arr->data[0];
            arr->data[0] = arr->data[1];
            arr->data[1] = tmp;
        }
        else if (arr->usedLength > 2)
        {
            int size = (arr->usedLength - 1) / 2;
            for (int i = 0; i <= size; i++)
            {
                tmp = arr->data[i];
                arr->data[i] = arr->data[arr->usedLength - 1 - i];
                arr->data[arr->usedLength - 1 - i] = tmp;
            }
        }
    }
}

#endif // ARRAY_LIST_H