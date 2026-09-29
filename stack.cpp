#include <cstddef>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>

#define MAX_CAPACITY 1000000
#define NAME(x) #x

typedef double stack_elem;

struct stack_t
{
    stack_elem* data;
    size_t size;//типа текущий размер сколько элементов
    size_t capacity;//размер массива
};

enum Errors
{
    OK = 1,
    ERR_NULL_POINTER,
    ERR_ZERO_LENGTH,
    ERR_LENGTH_TOO_BIG,
    ERR_CALLOC_ERROR,
    ERR_STACK_EXISTS
};

typedef struct
{
    const char* var_name;
    const char* file;
    const unsigned int line;
} var_info;

int StackPush(stack_t* stack, stack_elem elem);
int StackPop(stack_t* stack, stack_elem* elem);
int StackInit(stack_t* stack, size_t capacity);
int StackFree(stack_t* stack);
void StackDump(stack_t* stack, var_info info);
const char* GetErrorMessage(int error);
int ResizeData(stack_t* stack);

#define STACK_ELEM_SPEC _Generic((stack_elem)0, \
    int: "%d",                                  \
    char: "%c",                                 \
    double: "%g",                               \
    float: "%g",                                \
    char*: "%s",                                \
    unsigned int: "%zu",                        \
    default: "%p")

#define VARINFO(var) (var_info){NAME(var), __FILE__, __LINE__}

#define ASSERT_RETURN_VALUE(err) do {if (err != OK) \
{                                                   \
    printf("ERROR at %s:%d ", __FILE__, __LINE__);  \
    printf("%s", GetErrorMessage(err));             \
    printf("\n");                                   \
    abort();                                        \
}} while(0)


int main()
{
    stack_t stk1 = {};
    size_t start_capacity = 10;
    int err = StackInit(&stk1, start_capacity);
    ASSERT_RETURN_VALUE(err);

    StackDump(&stk1, VARINFO(stk1));

    stack_elem elem1 = 3.14;

    err = StackPush(&stk1, elem1);

    StackDump(&stk1, VARINFO(stk1));

    err = StackPush(&stk1, 3.19);
    ASSERT_RETURN_VALUE(err);

    StackDump(&stk1, VARINFO(stk1));

    err = StackPush(&stk1, 1.1111111);
    ASSERT_RETURN_VALUE(err);

    StackDump(&stk1, VARINFO(stk1));

    err = StackPop(&stk1, &elem1);
    ASSERT_RETURN_VALUE(err);

    StackDump(&stk1, VARINFO(stk1));

    printf("%g\n", elem1);

    StackDump(&stk1, VARINFO(stk1));

    err = StackFree(&stk1);
    ASSERT_RETURN_VALUE(err);
}

int StackPush(stack_t* stack, stack_elem elem)
{
    if (stack->size >= stack->capacity)
    {
        stack->capacity *= 2;
        int err = ResizeData(stack);
        if (err != OK) return err;
    }
    stack->data[stack->size++] = elem;
    return 1;
}

int StackPop(stack_t* stack, stack_elem* elem)
{
    if (elem == NULL) return ERR_NULL_POINTER;
    if (stack->size <= 0) return ERR_ZERO_LENGTH;

    if (stack->capacity > 10 && stack->size * 4 <= stack->capacity)
    {
        stack->capacity /= 2;

        int err = ResizeData(stack);
        if (err != OK) return err;
    }
    *elem = stack->data[--stack->size];
    return 1;
}

int StackInit(stack_t* stack, size_t capacity)
{
    if (stack == NULL) return ERR_NULL_POINTER;
    if (stack->data != NULL || stack->capacity != 0 || stack->size != 0) return ERR_STACK_EXISTS;
    if (capacity == 0) return ERR_ZERO_LENGTH;
    if (capacity > MAX_CAPACITY) return ERR_LENGTH_TOO_BIG;

    stack->capacity = capacity;
    stack->size = 0;
    stack->data = (stack_elem*)calloc(capacity, sizeof(stack_elem));
    if (stack->data == NULL) return ERR_CALLOC_ERROR;

    return 1;
}

int StackFree(stack_t* stack)
{
    if (stack == NULL) return ERR_NULL_POINTER;
    free(stack->data);
    stack->data = NULL;
    stack->capacity = 0;
    stack->size = 0;
    return 1;
}

void StackDump(stack_t* stack, var_info info)
{
    printf("---------PRINTING STACK---------\n");
    printf("Printing stack_t \"%s\"[%p] CALLED at %s:%u\n", info.var_name, stack, info.file, info.line);
    printf("%s = %zu, %s = %zu\n", NAME(stack->size), stack->size, NAME(stack->capacity), stack->capacity);
    printf("\"%s\"[%p]\n{\n", NAME(stack->data), stack->data);
    if (stack-> data != NULL)
    {
        for (unsigned int i = 0; i < stack->size; i++)
        {
            printf("\t[%u] = <", i);
            printf(STACK_ELEM_SPEC, stack->data[i]);
            printf(">\n");
        }
        printf("}\n");
    }
    else printf("%s IS NULL!!!\n", NAME(stack->data));
    printf("---------\n");

}

const char* GetErrorMessage(int error)
{
    switch(error)
    {
        case OK:                  return "OK";
        case ERR_NULL_POINTER:    return "ERR_NULL_POINTER";
        case ERR_ZERO_LENGTH:     return "ERR_ZERO_LENGTH";
        case ERR_LENGTH_TOO_BIG:  return "ERR_LENGTH_TOO_BIG";
        case ERR_CALLOC_ERROR:    return "ERR_CALLOC_ERROR";
        case ERR_STACK_EXISTS:    return "ERR_STACK_EXISTS";
        default:                  return "ERROR IS NOT IN ENUM";
    }
}

int ResizeData(stack_t* stack)
{
    stack_elem* new_data = (stack_elem*)realloc(stack->data, stack->capacity * sizeof(stack_elem));
    if (new_data == NULL) return ERR_CALLOC_ERROR;
    stack->data = new_data;
    if (stack->data == NULL) return ERR_CALLOC_ERROR;
    return OK;
}
