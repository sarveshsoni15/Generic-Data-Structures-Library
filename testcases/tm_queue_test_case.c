#include<stdio.h>
#include<tm_queue.h>
int main()
{
int success;
Queue *queue;
int x1,x2,x3,x4;
int *x;
x1=10;
x2=20;
x3=30;
x4=40;
queue=createQueue(&success);
if(success==false)
{
printf("Unable to create queue\n");
return 0;
}
addToQueue(queue,&x1,&success);
if(success) printf("%d add to queue\n",x1);
else printf("Unable to add %d to queue\n",x1);

addToQueue(queue,&x2,&success);
if(success) printf("%d add to queue\n",x2);
else printf("Unable to add %d to queue\n",x2);

addToQueue(queue,&x3,&success);
if(success) printf("%d add to queue\n",x3);
else printf("Unable to add %d to queue\n",x3);

addToQueue(queue,&x4,&success);
if(success) printf("%d add to queue\n",x4);
else printf("Unable to add %d to queue\n",x4);


printf("Size of queue : %d\n",getSizeOfQueue(queue));

if(isQueueEmpty(queue)) printf("Queue is Empty\n");
else printf("Queue is not Empty\n");

x=(int *)elementAtFrontOfQueue(queue,&success);
printf("Element at Front of Queue : %d\n",*x);

printf("Now removing all elements from queue\n");
while(!isQueueEmpty(queue))
{
x=(int *)removeFromQueue(queue,&success);
printf("%d removed from Queue\n",*x);
}

destroyQueue(queue);
return 0;
}
