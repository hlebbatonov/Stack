#include <cstddef>
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

int StackPush(stack_t* stack, stack_elem elem);
int StackPop(stack_t* stack, stack_elem* elem);
int StackInit(stack_t* stack, size_t capacity);
int StackRemove(stack_t* stack);
void StackDump(stack_t* stack);

int main()
{
    stack_t stk1 = {};
    size_t start_capacity = 10;
    int err = StackInit(&stk1, start_capacity);
    if (err != 1) return 1;

    stack_elem elem1 = 3.14;

    err = StackPush(&stk1, elem1);
    if (err != 1) return 1;

    StackPush(&stk1, 3.19);
    StackPush(&stk1, 1.1111111);
    err = StackPop(&stk1, &elem1);

    printf("%g\n", elem1);
    for (size_t i = 0; i < stk1.size; i++) {printf("%g ", stk1.data[i]);}

    err = StackRemove(&stk1);
    if (err != 1) return 1;

}

int StackPush(stack_t* stack, stack_elem elem)
{
    if (stack->size > stack->capacity)
    {
        stack->capacity *= 2;
        stack->data = (stack_elem*)calloc(stack->capacity, sizeof(stack_elem));
        if (stack->data == NULL) return ERR_CALLOC_ERROR;
    }
    stack->data[stack->size++] = elem;
    return 1;
}

int StackPop(stack_t* stack, stack_elem* elem)
{
    if (elem == NULL) return ERR_NULL_POINTER;
    if (stack->size <= 0) return ERR_ZERO_LENGTH;

    if (stack->size <= stack->capacity / 2)
    {
        stack->capacity /= 2;
        stack->data = (stack_elem*)calloc(stack->capacity, sizeof(stack_elem));
        if (stack->data == NULL) return ERR_CALLOC_ERROR;
    }
    *elem = stack->data[--stack->size];
    return 1;
}

int StackInit(stack_t* stack, size_t capacity)
{
    if (stack == NULL) return ERR_NULL_POINTER;
    if (stack->data != NULL || stack->capacity != NULL || stack->size != NULL) return ERR_STACK_EXISTS;
    if (capacity == 0) return ERR_ZERO_LENGTH;
    if (capacity > MAX_CAPACITY) return ERR_LENGTH_TOO_BIG;

    stack->capacity = capacity;
    stack->size = 0;
    stack->data = (stack_elem*)calloc(capacity, sizeof(stack_elem));
    if (stack->data == NULL) return ERR_CALLOC_ERROR;

    return 1;
}

int StackRemove(stack_t* stack)
{
    if (stack == NULL) return ERR_NULL_POINTER;
    free(stack->data);
    stack->data = NULL;
    stack->capacity = NULL;
    stack->size = NULL;
    return 1;
}

void StackDump(stack_t* stack)
{
    printf("stack_t \"%s\"[%p] created at %s:%d", NAME(*stack));
}
