#include "stack.h"


int main()
{
    stack_t stk1 = {};
    size_t start_capacity = 5;

    Errors err = StackInit(&stk1, start_capacity);
    ASSERT_RETURN_VALUE(err);

    StackDump(&stk1);

    stack_elem elem1 = 3.14;

    err = StackPush(&stk1, elem1);
    ASSERT_RETURN_VALUE(err);

    for (double i = 1; i < 20; i++)
        StackPush(&stk1, i * 1.1);

    StackDump(&stk1);

    err = StackPush(&stk1, 3.19);
    ASSERT_RETURN_VALUE(err);

    StackDump(&stk1);

    err = StackPush(&stk1, 1.1111111);
    ASSERT_RETURN_VALUE(err);

    StackDump(&stk1);

    err = StackPop(&stk1, &elem1);
    ASSERT_RETURN_VALUE(err);

    StackDump(&stk1);

    printf("Elem1 = %g\n", elem1);

    for (double i = 1; i < 20; i++)
        StackPush(&stk1, i * 1.1);

    for (double i = 1; i < 31; i++)
        StackPop(&stk1, &elem1);

    StackDump(&stk1);

    err = StackFree(&stk1);
    ASSERT_RETURN_VALUE(err);
}
