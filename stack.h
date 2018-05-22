#ifndef STACK_H
#define STACK_H

typedef struct {
    int info;
} DATA;

typedef struct node {
    DATA data;
    struct node *prev;
} NODE;

void stack_init(NODE **top);

/**
 *  Returns new top of stack
 * [In ] Current top of stack
 * [In ] Data node to push
 */
NODE *push(NODE *top, DATA data);

/**
 * Returns new top of stack
 * [In] top of stack
 * [Out] Data node to pop
 */
NODE *pop(NODE *top, DATA *element);

/**
 * Returns the original top of stack
 * [In] top of stack
 * [Out] Data node of stack
 */
DATA *top(NODE *top);

/**
 * Returns TRUE or FALSE whether the stack is empty
 * [In] top of stack
 */
int empty(NODE *top);

#endif // !STACK_H
