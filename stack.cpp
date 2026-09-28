#include <cstddef>
#include <stdio.h>
#include <stdlib.h>

#define MAX_CAPACITY 10e7

typedef double stack_elem;

struct stack_t
{
    stack_elem* data;
    size_t size;//типа текущий размер сколько элементов
    size_t capacity;//размер массива
};

int StackPush(stack_t* stack, stack_elem elem);
int StackInit(stack_t* stack, size_t capacity);
int StackRemove(stack_t* stack);

int main()
{
    stack_t stk1 = {};
    size_t start_capacity = 10;
    int err = StackInit(&stk1, start_capacity);
    if (err != 1) return 1;

    stack_elem elem1 = 3.14;

    err = StackPush(&stk1, elem1);
    if (err != 1) return 1;

    for (int i = 0; i < stk1.size; i++) {printf("<%g>", stk1.data[i]);}

    err = StackRemove(&stk1);
    if (err != 1) return 1;

}

int StackPush(stack_t* stack, stack_elem elem)
{
    if (stack->size < stack->capacity)
    {
        stack->data[stack->size] = elem;
        stack->size++;
    }
    else return -1;

    return 1;
}

int StackInit(stack_t* stack, size_t capacity)
{
    if (stack == NULL) return -1;
    if (capacity == 0) return -2;
    if (capacity > MAX_CAPACITY) return -3;

    stack->capacity = capacity;
    stack->size = 0;
    stack->data = (stack_elem*)calloc(capacity, sizeof(stack_elem));
    if (stack->data == NULL) return -4;

    return 1;
}

int StackRemove(stack_t* stack)
{
    if (stack == NULL) return -1;
    free(stack->data);
    stack->data = NULL;
    stack->capacity = NULL;
    stack->size = NULL;
    return 1;
}

