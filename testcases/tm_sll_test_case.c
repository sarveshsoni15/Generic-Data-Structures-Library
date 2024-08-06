#include<tm_sll.h>
#include<stdio.h>
int main()
{
bool success;
SinglyLinkedListIterator iter;
int i1,i2,i3,i4,i5,i6,y;
int *x;
i1=300;
i2=600;
i3=300;
i4=400;
i5=500;
i6=600;
SinglyLinkedList *list1;
list1=createSinglyLinkedList(&success);

addToSinglyLinkedList(list1,(void *)&i1,&success);
addToSinglyLinkedList(list1,(void *)&i2,&success);
addToSinglyLinkedList(list1,(void *)&i3,&success);
addToSinglyLinkedList(list1,(void *)&i4,&success);
addToSinglyLinkedList(list1,(void *)&i5,&success);
addToSinglyLinkedList(list1,(void *)&i6,&success);

iter=getSinglyLinkedListIterator(list1,&success);
printf("Singly linked list iterator\n");
if(success)
{
while(hasNextInSinglyLinkedList(&iter))
{
x=(int *)getNextElementFromSinglyLinkedList(&iter,&success);
printf("%d\n",*x);
}
}
destroySinglyLinkedList(list1);
return 0;
}