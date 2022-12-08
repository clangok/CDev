/**
 * 整数数组操作函数库
 */
#ifndef ARRAY_INT_H
#define ARRAY_INT_H

#include <stdlib.h>

// 数组最大长度
#define ARRAY_INT_LENGTH_MAX 100000
// 数组默认值
#define ARRAY_INT_VALUE_DEFAULT 0

// 数组值类型
typedef int ArrayIntValue;
// 数组类型
typedef struct _arrayInt ArrayInt;
// 比较函数
typedef int (*ArrayIntCompare)(ArrayIntValue, ArrayIntValue);

// 数组结构
struct _arrayInt
{
    ArrayIntValue *data;     // 数组数据
    ArrayIntCompare compare; // 比较函数
    unsigned int length;     // 数组长度
    unsigned int usedLength; // 数组已使用长度
};

/**
 * 函数声明列表#############################################################################
 */

ArrayInt *arrint_new(unsigned int len);
int arrint_insert(ArrayInt *arr, ArrayIntValue val, unsigned int id);
int arrint_append(ArrayInt *arr, ArrayIntValue *vals, unsigned int size);
int arrint_modify(ArrayInt *arr, ArrayIntValue val, unsigned int id);
int arrint_delete(ArrayInt *arr, unsigned int id);
int arrint_delete_range(ArrayInt *arr, unsigned int start, unsigned int size);
ArrayIntValue arrint_get(ArrayInt *arr, unsigned int id);
ArrayIntValue *arrint_get_range(ArrayInt *arr, unsigned int start, unsigned int size);
int arrint_getid(ArrayInt *arr, ArrayIntValue val);
ArrayIntValue arrint_max(ArrayInt *arr);
ArrayIntValue arrint_min(ArrayInt *arr);
int arrint_adjust(ArrayInt *arr, unsigned int size);
int arrint_size(ArrayInt *arr);
int arrint_isnull(ArrayInt *arr);
int arrint_isempty(ArrayInt *arr);
int arrint_clear(ArrayInt *arr);
void arrint_free(ArrayInt *arr);
int arrint_compare(ArrayIntValue val1, ArrayIntValue val2);
void arrint_sort(ArrayInt *arr, char mode);
void arrint_reverse(ArrayInt *arr);

/**
 * 函数实现列表#############################################################################
 */

/// @brief 创建新数组
/// @param len
/// @return
ArrayInt *arrint_new(unsigned int len)
{
    // 长度判断
    if ((int)len <= 0 || len > ARRAY_INT_LENGTH_MAX)
    {
        return NULL;
    }

    // 分配数组内存
    ArrayInt *array = (ArrayInt *)malloc(sizeof(ArrayInt));
    if (array == NULL)
    {
        return NULL;
    }

    // 分配数组数据内存
    array->data = (ArrayIntValue *)malloc(sizeof(ArrayIntValue) * len);
    if (array->data == NULL)
    {
        free(array);
        return NULL;
    }
    array->length = len;
    array->usedLength = 0;
    array->compare = arrint_compare;

    // 所有数组元素赋值为默认值
    for (int i = 0; i < len; i++)
    {
        array->data[i] = ARRAY_INT_VALUE_DEFAULT;
    }

    return array;
}

/// @brief 在下标指定位置添加数据
/// @param arr
/// @param val
/// @param id
/// @return 1:成功，-1:失败
int arrint_insert(ArrayInt *arr, ArrayIntValue val, unsigned int id)
{
    if (arr == NULL || (int)id < 0 || id > arr->usedLength)
    {
        return -1;
    }
    if (arr->usedLength >= arr->length && arrint_adjust(arr, 1) < 0)
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

/// @brief 将一个值数组追加到数组中
/// @param arr
/// @param vals
/// @param size
/// @return -1:失败,1:成功
int arrint_append(ArrayInt *arr, ArrayIntValue *vals, unsigned int size)
{
    if (arr == NULL || (int)size < 0)
    {
        return -1;
    }
    if (arr->usedLength + size >= arr->length && arrint_adjust(arr, arr->usedLength + size - arr->length) < 0)
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

/// @brief 修改下标指定位置的数据
/// @param arr
/// @param val
/// @param id
/// @return 1:成功，-1:失败
int arrint_modify(ArrayInt *arr, ArrayIntValue val, unsigned int id)
{
    int result = -1;
    if (arr != NULL && arr->usedLength > 0 && (int)id >= 0 && id < arr->usedLength)
    {
        arr->data[id] = val;
        result = 1;
    }
    return result;
}

/// @brief 删除下标指定位置的数据
/// @param arr
/// @param id
/// @return 1:成功,-1:失败
int arrint_delete(ArrayInt *arr, unsigned int id)
{
    int result = -1;
    if (arr != NULL && arr->usedLength > 0 && (int)id >= 0 && id < arr->usedLength)
    {
        for (int i = id; i < arr->usedLength - 1; i++)
        {
            arr->data[i] = arr->data[i + 1];
        }
        arr->data[arr->usedLength - 1] = ARRAY_INT_VALUE_DEFAULT;
        arr->usedLength--;
        result = 1;
    }
    return result;
}

/// @brief 删除指定范围内的元素数据
/// @param arr
/// @param start
/// @param size
/// @return 0:未删除，>=1:删除的数据数量
int arrint_delete_range(ArrayInt *arr, unsigned int start, unsigned int size)
{
    int result = 0;
    if (arr != NULL && arr->usedLength > 0 && (int)start >= 0 && (int)size > 0 && start + size < arr->usedLength)
    {
        for (int i = 0; i < size; i++)
        {
            if (arrint_delete(arr, start) > 0)
            {
                result++;
            }
        }
    }
    return result;
}

/// @brief 获取下标指定位置的数据
/// @param arr
/// @param id
/// @return 元素的值：成功，默认值：失败
ArrayIntValue arrint_get(ArrayInt *arr, unsigned int id)
{
    ArrayIntValue result = ARRAY_INT_VALUE_DEFAULT;
    if (arr != NULL && arr->usedLength > 0 && (int)id >= 0 && id < arr->usedLength)
    {
        result = arr->data[id];
    }
    return result;
}

/// @brief 截取指定范围的元素的值输出到数组
/// @param arr
/// @param start
/// @param size
/// @return
ArrayIntValue *arrint_get_range(ArrayInt *arr, unsigned int start, unsigned int size)
{
    ArrayIntValue *result = NULL;
    if (arr != NULL && arr->usedLength > 0 && (int)start >= 0 && (int)size > 0 && start + size < arr->usedLength)
    {
        result = (ArrayIntValue *)malloc(sizeof(ArrayIntValue) * size);
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

/// @brief 根据元素的值找到元素的下标
/// @param arr
/// @param val
/// @return -1：不存在，>=0:存在该值
int arrint_getid(ArrayInt *arr, ArrayIntValue val)
{
    int result = -1;
    if (arr != NULL && arr->usedLength > 0)
    {
        for (int i = 0; i < arr->usedLength; i++)
        {
            if (arr->compare(val, arr->data[i]) == 0)
            {
                result = i;
                break;
            }
        }
    }
    return result;
}

/// @brief 数组最大值
/// @param arr
/// @return 数组最大值：成功，默认值：失败
ArrayIntValue arrint_max(ArrayInt *arr)
{
    ArrayIntValue result = ARRAY_INT_VALUE_DEFAULT;
    if (arr != NULL && arr->usedLength > 0)
    {
        result = arr->data[0];

        for (int i = 1; i < arr->usedLength && arr->usedLength > 1; i++)
        {
            if (arr->compare(arr->data[i], result) == 1)
            {
                result = arr->data[i];
            }
        }
    }
    return result;
}

/// @brief 数组最小值
/// @param arr
/// @return 数组最小值：成功，默认值：失败
ArrayIntValue arrint_min(ArrayInt *arr)
{
    ArrayIntValue result = ARRAY_INT_VALUE_DEFAULT;
    if (arr != NULL && arr->usedLength > 0)
    {
        result = arr->data[0];

        for (int i = 1; i < arr->usedLength && arr->usedLength > 1; i++)
        {
            if (arr->compare(arr->data[i], result) == -1)
            {
                result = arr->data[i];
            }
        }
    }
    return result;
}

/// @brief 自动调节数组大小
/// @param arr
/// @param size
/// @return 1:成功,-1:失败
int arrint_adjust(ArrayInt *arr, unsigned int size)
{
    int result = -1;
    if (arr != NULL && (int)size > 0 && arr->length + size <= ARRAY_INT_LENGTH_MAX)
    {
        int len = arr->length + size;
        arr->data = (ArrayIntValue *)realloc(arr->data, sizeof(ArrayIntValue) * len);
        if (arr->data != NULL)
        {
            arr->length = len;
            result = 1;
        }
    }
    return result;
}

/// @brief 数组实际使用长度
/// @param arr
/// @return arr->usedLength
int arrint_size(ArrayInt *arr)
{
    return (arr != NULL) ? arr->usedLength : 0;
}

/// @brief 判断数组指针是否为空
/// @param arr
/// @return 1:为空，0:不为空
int arrint_isnull(ArrayInt *arr)
{
    return (arr == NULL) ? 1 : 0;
}

/// @brief 判断数组数据是否为空
/// @param arr
/// @return 1:为空,0:不为空
int arrint_isempty(ArrayInt *arr)
{
    return (arr != NULL && arr->usedLength == 0) ? 1 : 0;
}

/// @brief 清空所有数据，并设为默认值
/// @param arr
/// @return 清空数据的个数
int arrint_clear(ArrayInt *arr)
{
    int result = 0;
    if (arr != NULL && arr->usedLength > 0)
    {
        for (int i = 0; i < arr->usedLength; i++)
        {
            arr->data[i] = ARRAY_INT_VALUE_DEFAULT;
            result++;
        }
        arr->usedLength = 0;
    }
    return result;
}

/// @brief 释放内存
/// @param arr
void arrint_free(ArrayInt *arr)
{
    arrint_clear(arr);
    free(arr->data);
    free(arr);
}

/// @brief 比较函数
/// @param val1
/// @param val2
/// @return 1:前>后,0:前=后,-1:前<后
int arrint_compare(ArrayIntValue val1, ArrayIntValue val2)
{
    if (val1 > val2)
        return 1;
    else if (val1 == val2)
        return 0;
    else
        return -1;
}

/// @brief 数组排序
/// @param arr
/// @param mode
void arrint_sort(ArrayInt *arr, char mode)
{
    if (arr != NULL && arr->usedLength > 1)
    {
        ArrayIntValue tmp;
        for (int i = 0; i < arr->usedLength; i++)
        {
            for (int j = i + 1; j < arr->usedLength; j++)
            {
                if (mode == 'A')
                {
                    if (arr->compare(arr->data[i], arr->data[j]) == 1)
                    {
                        tmp = arr->data[i];
                        arr->data[i] = arr->data[j];
                        arr->data[j] = tmp;
                    }
                }
                else if (mode == 'D')
                {
                    if (arr->compare(arr->data[i], arr->data[j]) == -1)
                    {
                        tmp = arr->data[i];
                        arr->data[i] = arr->data[j];
                        arr->data[j] = tmp;
                    }
                }
            }
        }
    }
}

/// @brief 数组反转
/// @param arr
void arrint_reverse(ArrayInt *arr)
{
    if (arr != NULL)
    {
        ArrayIntValue tmp;
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

#endif // ARRAY_INT_H