#ifndef __TM_SLL__C
#define __TM_SLL__C 123
#include<stdlib.h>
#include<tm_sll.h>
SinglyLinkedList *createSinglyLinkedList(bool *success)
{
if(success) *success=false;
SinglyLinkedList *singlyLinkedList;
singlyLinkedList=(SinglyLinkedList *)malloc(sizeof(SinglyLinkedList));
if(singlyLinkedList==NULL) return NULL;
singlyLinkedList->start=NULL;
singlyLinkedList->end=NULL;
singlyLinkedList->size=0;
if(success) *success=true;
return singlyLinkedList;
}

void addToSinglyLinkedList(SinglyLinkedList *singlyLinkedList,void *ptr,bool *success)
{
SinglyLinkedListNode *node;
if(success) *success=false;
if(singlyLinkedList==NULL) return;
node=(SinglyLinkedListNode *)malloc(sizeof(SinglyLinkedListNode));
if(node==NULL) return;
node->ptr=ptr;
node->next=NULL;
if(singlyLinkedList->start==NULL)
{
singlyLinkedList->start=node;
singlyLinkedList->end=node;
}
else
{
singlyLinkedList->end->next=node;
singlyLinkedList->end=node;
}
singlyLinkedList->size++;
if(success) *success=true;
}

void destroySinglyLinkedList(SinglyLinkedList *singlyLinkedList)
{
if(singlyLinkedList==NULL) return;
clearSinglyLinkedList(singlyLinkedList);
free(singlyLinkedList);
}

void clearSinglyLinkedList(SinglyLinkedList *singlyLinkedList)
{
SinglyLinkedListNode *node;
if(singlyLinkedList==NULL) return;

while(singlyLinkedList->start)
{
node=singlyLinkedList->start;
singlyLinkedList->start=singlyLinkedList->start->next;
free(node);
}
singlyLinkedList->end=NULL;
singlyLinkedList->size=0;
}

void insertIntoSinglyLinkedList(SinglyLinkedList *singlyLinkedList,int index,void *ptr,bool *success)
{
SinglyLinkedListNode *node,*p1,*p2;
int x;
if(success) *success=false;
if(singlyLinkedList==NULL) return;
if(index<0 || index>singlyLinkedList->size) return;
if(index==singlyLinkedList->size)
{
addToSinglyLinkedList(singlyLinkedList,ptr,success);
return;
}
node=(SinglyLinkedListNode *)malloc(sizeof(SinglyLinkedListNode));
if(node==NULL) return;
node->ptr=ptr;
node->next=NULL;
if(index==0)
{
node->next=singlyLinkedList->start;
singlyLinkedList->start=node;
singlyLinkedList->size++;
if(success) *success=true;
return;
}
p1=singlyLinkedList->start;
x=0;
while(x<index)
{
p2=p1;
p1=p1->next;
x++;
}
node->next=p1;
p2->next=node;
singlyLinkedList->size++;
if(success) *success=true;
}

void * removeFromSinglyLinkedList(SinglyLinkedList *singlyLinkedList,int index,bool *success)
{
void *ptr;
SinglyLinkedListNode *p1,*p2;
int x;

if(success) *success=false;
if(singlyLinkedList==NULL) return NULL;
if(index<0 || index>=singlyLinkedList->size) return NULL;
p1=singlyLinkedList->start;
x=0;
while(x<index)
{
p2=p1;
p1=p1->next;
x++;
}
ptr=p1->ptr;
if(p1==singlyLinkedList->start && p1==singlyLinkedList->end)
{
singlyLinkedList->start=NULL;
singlyLinkedList->end=NULL;
}
else if(p1==singlyLinkedList->start)
{
singlyLinkedList->start=singlyLinkedList->start->next;
}
else if(p1==singlyLinkedList->end)
{
singlyLinkedList->end=p2;
singlyLinkedList->end->next=NULL;
}
else
{
p2->next=p1->next;
}
free(p1);
singlyLinkedList->size--;
if(success) *success=true;
return ptr;
}

int getSizeOfSinglyLinkedList(SinglyLinkedList *singlyLinkedList)
{
if(singlyLinkedList==NULL) return 0;
return singlyLinkedList->size;
}

void * getFromSinglyLinkedList(SinglyLinkedList *singlyLinkedList,int index,bool *success)
{
SinglyLinkedListNode *node;
int x;
if(success) *success=false;
if(singlyLinkedList==NULL) return NULL;
if(index<0 || index>=singlyLinkedList->size) return NULL;
x=0;
node=singlyLinkedList->start;
while(x<index)
{
node=node->next;
x++;
}
if(success) *success=true;
return node->ptr;
}

void appendToSinglyLinkedList(SinglyLinkedList *targetSinglyLinkedList,SinglyLinkedList *sourceSinglyLinkedList,bool *success)
{
SinglyLinkedListNode *node,*s,*e,*t;
bool done;
if(success) *success=false;
if(targetSinglyLinkedList==NULL) return;
if(sourceSinglyLinkedList==NULL || sourceSinglyLinkedList->size==0)
{
if(success) *success=true;
return;
}
s=NULL;
e=NULL;
done=true;
t=sourceSinglyLinkedList->start;
while(t!=NULL)
{
node=(SinglyLinkedListNode *)malloc(sizeof(SinglyLinkedListNode));
if(node==NULL)
{
done=false;
break;
}
node->ptr=t->ptr;
node->next=NULL;
if(s==NULL)
{
s=node;
e=node;
}
else
{
e->next=node;
e=node;
}
t=t->next;
}
if(done==false)
{
while(s!=NULL)
{
node=s;
s=s->next;
free(node);
}
}
if(targetSinglyLinkedList->start==NULL)
{
targetSinglyLinkedList->start=s;
targetSinglyLinkedList->end=e;
targetSinglyLinkedList->size=sourceSinglyLinkedList->size;
}
else
{
targetSinglyLinkedList->end->next=s;
targetSinglyLinkedList->end=e;
targetSinglyLinkedList->size+=sourceSinglyLinkedList->size;
}
if(success) *success=true;
}

SinglyLinkedListIterator getSinglyLinkedListIterator(SinglyLinkedList *singlyLinkedList,bool *success)
{
SinglyLinkedListIterator singlyLinkedListIterator;
singlyLinkedListIterator.node=NULL;
if(success) *success=false;
if(singlyLinkedList==NULL) return singlyLinkedListIterator;
if(singlyLinkedList->start==NULL)
{
if(success) *success=true;
return singlyLinkedListIterator;
}
if(success) *success=true;
singlyLinkedListIterator.node=singlyLinkedList->start;
return singlyLinkedListIterator;
}

bool hasNextInSinglyLinkedList(SinglyLinkedListIterator *singlyLinkedListIterator)
{
if(singlyLinkedListIterator==NULL) return false;
if(singlyLinkedListIterator->node==NULL) return false;
return true;
}

void * getNextElementFromSinglyLinkedList(SinglyLinkedListIterator *singlyLinkedListIterator,bool *success)
{
void *ptr=NULL;
if(success) *success=false;
if(singlyLinkedListIterator==NULL) return ptr;
ptr=singlyLinkedListIterator->node->ptr;
singlyLinkedListIterator->node=singlyLinkedListIterator->node->next;
if(success) *success=true;
return ptr;
}
#endif