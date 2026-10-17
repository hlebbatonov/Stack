#include "stack.h"

Errors RunTestOK(stack_t* stack);
Errors RunTestStackNullPointer();
Errors RunTestDataNullPointer(stack_t* stack);
Errors RunTestZeroLength(stack_t* stack);
Errors RunTestLengthTooBig(stack_t* stack);
Errors RunTestDeadLeftCanary(stack_t* stack);
Errors RunTestDeadRightCanary(stack_t* stack);

int main()
{
    stack_t stack = {};

    if (OK == RunTestOK(&stack)) printf("TEST 1 OK\n");
    stack = {};

    if (ERR_STACK_NULL_POINTER == RunTestStackNullPointer()) printf("TEST 2 OK");
    stack = {};

    if (ERR_NULL_POINTER == RunTestDataNullPointer(&stack)) printf("TEST 3 OK");
    stack = {};

}

Errors RunTestOK(stack_t* stack)
{
    size_t start_capacity = 5;

    Errors err = StackInit(stack, start_capacity);
    if (err != OK) return err;
    stack_elem elem1 = 3.14;

    err = StackPush(stack, elem1);
    if (err != OK) return err;
    for (double i = 1; i < 20; i++)
    {
        err = StackPush(stack, i * 1.1);
        if (err != OK) return err;
    }

    StackPop(stack, &elem1);
    return err;
}

Errors RunTestStackNullPointer()
{
    Errors err = StackInit(NULL, 5);
    return err;
}

Errors RunTestDataNullPointer(stack_t* stack)
{
    StackInit(stack, 5);
    stack->data = NULL;
    stack_elem elem1 = 0;
    Errors err = StackPop(stack, &elem1);
    return err;
}

Errors RunTestZeroLength(stack_t* stack)
{
    StackInit(stack, 2);
    stack_elem elem1 = 0;
    Errors err = StackPop(stack, &elem1);
    return err;
}

Errors RunTestLengthTooBig(stack_t* stack)
{
    Errors err = StackInit(stack, 2000000000000000);
    return err;
}

Errors RunTestDeadLeftCanary(stack_t* stack)
{
    StackInit(stack, 4);
    stack->data[0] = 0;
    stack_elem elem1 = 0;
    Errors err = StackTop(stack, &elem1);
    return err;
}

Errors RunTestDeadRightCanary(stack_t* stack)
{
    StackInit(stack, 4);
    stack->data[stack->capacity + 2] = 0;
    stack_elem elem1 = 0;
    Errors err = StackTop(stack, &elem1);
    return err;
}
