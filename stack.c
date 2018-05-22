#include "stack.h"
#include <stdlib.h>

void stack_init(NODE **top) { *top = NULL; }

NODE *push(NODE *top, DATA data) {
    NODE *tmp = (NODE *)malloc(sizeof(NODE));
    if (tmp == NULL) {
        exit(0);
    }
    tmp->data = data;
    tmp->prev = top;
    top = tmp;
    return top;
}

NODE *pop(NODE *top, DATA *element) {
    NODE *tmp = top;
    *element = top->data;
    top = top->prev;
    free(tmp);
    return top;
}

DATA *top(NODE *top) { return &top->data; }

int empty(NODE *top) { return (top == NULL) ? 1 : 0; }