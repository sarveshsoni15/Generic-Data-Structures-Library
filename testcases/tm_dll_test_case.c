#include<tm_dll.h>
#include<stdio.h>
int main()
{
bool success;
DoublyLinkedListReverseIterator iter;
int i1,i2,i3,i4,i5,i6,y;
int *x;
i1=100;
i2=200;
i3=300;
i4=400;
i5=500;
i6=600;
DoublyLinkedList *list1;
list1=createDoublyLinkedList(&success);

addToDoublyLinkedList(list1,(void *)&i1,&success);
addToDoublyLinkedList(list1,(void *)&i2,&success);
addToDoublyLinkedList(list1,(void *)&i3,&success);
addToDoublyLinkedList(list1,(void *)&i4,&success);
addToDoublyLinkedList(list1,(void *)&i5,&success);
addToDoublyLinkedList(list1,(void *)&i6,&success);

iter=getDoublyLinkedListReverseIterator(list1,&success);
printf("Doubly linked list  Reverse iterator\n");
if(success)
{
while(hasPreviousInDoublyLinkedList(&iter))
{
x=(int *)getPrevious	ElementFromDoublyLinkedList(&iter,&success);
printf("%d\n",*x);
}
}
destroyDoublyLinkedList(list1);
return 0;
}