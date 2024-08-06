#include<stdio.h>
#include<tm_stack.h>
int main()
{
int success;
int x1,x2,x3,x4;
int *x;
x1=10;
x2=20;
x3=30;
x4=40;
Stack *stack;
stack=createStack(&success);
if(success==false)
{
printf("Unable to create stack\n");
return 0;
}

pushOnStack(stack,&x1,&success);
if(success) printf("%d pushed on stack\n",x1);
else printf("Unable to pushed %d on stack\n",x1);

pushOnStack(stack,&x2,&success);
if(success) printf("%d pushed on stack\n",x2);
else printf("Unable to pushed %d on stack\n",x2);

pushOnStack(stack,&x3,&success);
if(success) printf("%d pushed on stack\n",x3);
else printf("Unable to pushed %d on stack\n",x3);

pushOnStack(stack,&x4,&success);
if(success) printf("%d pushed on stack\n",x4);
else printf("Unable to pushed %d on stack\n",x4);

printf("Size of stack : %d\n",getSizeOfStack(stack));

if(isStackEmpty(stack)) printf("Stack is Empty\n");
else printf("Stack is not Empty\n");

x=(int *)elementAtTopOfStack(stack,&success);
printf("Element at Top of Stack : %d\n",*x);

printf("Now popping all elements from stack\n");

while(!isStackEmpty(stack))
{
x=(int *)popFromStack(stack,&success);
printf("%d Poppped from Stack\n",*x);
}
destroyStack(stack);
return 0;
}
