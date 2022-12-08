/**
 * 字符串数组操作函数
 */

#ifndef ARRAY_STRING_H
#define ARRAY_STRING_H

#define ARRAY_STRING_LENGTH_MAX

typedef char *ArrayStringValue;
typedef struct _arrayString ArrayString;

struct _arrayString
{
    ArrayStringValue *data;
    unsigned int length;
    unsigned int usedLength;
};

/**
 * 函数声明列表#############################################################################
 */

ArrayString *arrstr_new(unsigned int len);
int arrstr_insert(ArrayString *arr, ArrayStringValue val, unsigned int id);
int arrstr_append(ArrayString *arr, ArrayStringValue *vals, unsigned int size);
int arrstr_modify(ArrayString *arr, ArrayStringValue val, unsigned int id);
int arrstr_delete(ArrayString *arr, unsigned int id);
int arrstr_delete_range(ArrayString *arr, unsigned int start, unsigned int size);
ArrayStringValue arrstr_get(ArrayString *arr, unsigned int id);
ArrayStringValue *arrstr_get_range(ArrayString *arr, unsigned int start, unsigned int size);
int arrstr_getid(ArrayString *arr, ArrayStringValue val);
int arrstr_adjust(ArrayString *arr, unsigned int size);
int arrstr_size(ArrayString *arr);
int arrstr_isnull(ArrayString *arr);
int arrstr_isempty(ArrayString *arr);
int arrstr_clear(ArrayString *arr);
void arrstr_free(ArrayString *arr);
int arrstr_compare(ArrayStringValue val1, ArrayStringValue val2);
void arrstr_sort(ArrayString *arr, char mode);
void arrstr_reverse(ArrayString *arr);

#endif // ARRAY_STRING_H