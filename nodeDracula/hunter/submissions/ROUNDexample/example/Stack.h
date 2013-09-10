#ifndef _Stack_h
#define _Stack_h

#define MAX_STACK_SIZE 1000
typedef int item;
typedef struct stack *Stack;

Stack createStack (void);
void pushStack (Stack s, item value);
item popStack (Stack s);
void deleteStack (Stack s);
int isEmpty (Stack s);

#endif
