#include "Stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct stack {
   item items[MAX_STACK_SIZE];
   int stackSize;
} stack;

// create a new stack
Stack createStack (void) {
   Stack retStack = malloc(sizeof(struct stack));
   retStack->stackSize = 0;
   return retStack;
}

// add an item to the end of the stack
void pushStack (Stack s, item value) {
   assert(s != NULL);
   assert(s->stackSize >= 0 && s->stackSize < MAX_STACK_SIZE);
   s->items[s->stackSize] = value;
   s->stackSize += 1;
}

// remove and return the last item on the stack
item popStack (Stack s) {
   assert(s != NULL);
   assert(s->stackSize > 0 && s->stackSize <= MAX_STACK_SIZE);
   item retValue = s->items[s->stackSize - 1];
   s->stackSize -= 1;
   return retValue;
}

// is this stack empty?
int isEmpty (Stack s) {
    assert(s != NULL);
    return (s->stackSize <= 0);
}

// delete this stack
void deleteStack (Stack s) {
    assert(s != NULL);
    free(s);
}


