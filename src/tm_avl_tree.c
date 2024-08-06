#ifndef __TM_AVL_TREE__C
#define __TM_AVL_TREE__C 123
#include<stdlib.h>
#include<tm_avl_tree.h>

AVLTree * createAVLTree(bool *success,int (*predicate)(void *,void *))
{
if(success) *success=false;
AVLTree *avlTree;
avlTree=(AVLTree *)malloc(sizeof(AVLTree));
if(avlTree==NULL || predicate==NULL) return NULL;
avlTree->start=NULL;
avlTree->predicate=predicate;
avlTree->size=0;
if(success) *success=true;
return avlTree; 
}
void destroyAVLTree(AVLTree *avlTree)
{

}
int getSizeOfAVLTree(AVLTree *avlTree)
{
if(avlTree==NULL) return 0;
return avlTree->size;
}

void clearAVLTree(AVLTree *avlTree)
{

}

void insertIntoAVLTree(AVLTree *avlTree,void *ptr,bool *success)
{
Stack *stack;
int succ;
AVLTreeNode *t,*j;
int weight;
if(success) *success=false;
if(avlTree==NULL) return;

if(avlTree->start==NULL)
{
t=(AVLTreeNode *)malloc(sizeof(AVLTreeNode));
if(t==NULL) return;
t->ptr=ptr;
t->left=NULL;
t->right=NULL;
avlTree->start=t;
avlTree->size++;
if(success) *success=true;
return;
}
stack=createStack(&succ);
if(succ==false) return;

j=avlTree->start;
while(1)
{
weight=avlTree->predicate(ptr,j->ptr);
if(weight==0) return;

pushOnStack(stack,j,&succ);
if(succ==false)
{
destroyStack(stack);
return;
}

if(weight<0)
{
if(j->left==NULL)
{
t=(AVLTreeNode *)malloc(sizeof(AVLTreeNode));
if(t==NULL) return;
t->ptr=ptr;
t->left=NULL;
t->right=NULL;
j->left=t;
break;
}
else
{
j=j->left;
}
}
else
{
if(j->right==NULL)
{
t=(AVLTreeNode *)malloc(sizeof(AVLTreeNode));
if(t==NULL) return;
t->ptr=ptr;
t->left=NULL;
t->right=NULL;
j->right=t;
break;
}
else
{
j=j->right;
}
}
}
if(success) *success=true;
avlTree->size++;
balanceAVLTree(avlTree,stack);
destroyStack(stack);
}

void * removeFromAVLTree(AVLTree *avlTree,void *ptr,bool *success)
{
AVLTreeNode *t,*j,*e,*f;
AVLTreeNode **p2p;
void *foundPtr;
int weight;
if(success) *success=false;
if(avlTree==NULL || avlTree->start==NULL) return NULL;

t=avlTree->start;
while(t!=NULL)
{
weight=avlTree->predicate(ptr,t->ptr);
if(weight==0) break;
j=t;
if(weight<0) t=t->left;
else t=t->right;
}
if(t==NULL) return NULL;
foundPtr=t->ptr;

if(t==avlTree->start) p2p=&(avlTree->start);
else if(j->left==t) p2p=&(j->left);
else p2p=&(j->right);

if(t->left==NULL && t->right==NULL) // Leaf Node
{
*p2p=NULL;
}
else
{
if(t->right!=NULL)
{
for(e=t->right;t->left!=NULL;t=t->left)
{
f=e;
}
if(t->right==e)
{
e->left=t->left;
}
else
{
f->left=e->right;
e->left=t->left;
e->right=t->right;
}
*p2p=e;
}
else
{
for(e=t->left;e->right!=NULL;e=e->right)
{
f=e;
}
if(t->left==e)
{
e->right=t->right;
}
else
{
f->right=e->left;
e->left=t->left;
e->right=t->right;
}
*p2p=e;
}
}
free(t);
avlTree->size--;
if(success) *success=true;
return foundPtr;
}

int getHeightOfAVLTree(AVLTreeNode *root)
{
int leftTreeHeight,rightTreeHeight;
if(root==NULL) return 0;
leftTreeHeight=getHeightOfAVLTree(root->left);
rightTreeHeight=getHeightOfAVLTree(root->right);
return (leftTreeHeight>rightTreeHeight) ?  leftTreeHeight+1 : rightTreeHeight+1;
}

void balanceAVLTree(AVLTree *avlTree,Stack *stack)
{
AVLTreeNode **p2p;
AVLTreeNode *root,*rc,*rclc,*lc,*lcrc,*parent;
int lh,rh,diff,succ;
if(stack==NULL) return;
if(isStackEmpty(stack)) return;
while(!isStackEmpty(stack))
{
root=popFromStack(stack,&succ); 
lh=getHeightOfAVLTree(root->left);
rh=getHeightOfAVLTree(root->right);
diff=lh-rh;
if(diff>=-1 && diff<=1) continue;

if(root==avlTree->start)
{
p2p=&(avlTree->start);
}
else 
{
parent=elementAtTopOfStack(stack,&succ);
if(root==parent->left)
{
p2p=&(parent->left);
}
else
{
p2p=&(parent->right);
}
}
if(rh>lh) // right is heavy
{
rc=root->right;
if(getHeightOfAVLTree(rc->left)>getHeightOfAVLTree(rc->right)) // right is left heavy
{
// logic to convert right is left heavy to right is right heavy
rclc=rc->left;
rc->left=rclc->right;
rclc->right=rc;
root->right=rclc;
rc=root->right;
}
// now 100% right is right heavy
root->right=rc->left;
rc->left=root;
*p2p=rc;
}
else // left is heavy
{
lc=root->left;
if(getHeightOfAVLTree(lc->right)>getHeightOfAVLTree(lc->left)) // left is right heavy
{
// logic to convert left is right heavy to left is left heavy
lcrc=lc->right;
lc->right=lcrc->left;
lcrc->left=lc;
root->left=lcrc;
lc=root->left;
}
// now 100% left is left heavy
root->left=lc->right;
lc->right=root;
*p2p=lc;
}
} // stack not empty loop ends
}

void * getFromAVLTree(AVLTree *avlTree,void *ptr,bool *success)
{
AVLTreeNode *t;
int weight;
if(success) *success=false;
if(avlTree==NULL || avlTree->start==NULL) return NULL;
t=avlTree->start;
while(t!=NULL)
{
weight=avlTree->predicate(ptr,t->ptr);
if(weight==0) 
{
if(success) *success=true;
return t->ptr;
}
if(weight<0) t=t->left;
else t=t->right;
}
return NULL;
}

AVLTreeInOrderIterator getAVLTreeInOrderIterator(AVLTree *avlTree,bool *success)
{
int succ;
AVLTreeNode *t;
AVLTreeInOrderIterator avlTreeInOrderIterator;
avlTreeInOrderIterator.node=NULL;
avlTreeInOrderIterator.stack=NULL;
if(success) *success=false;
if(avlTree==NULL) return avlTreeInOrderIterator;
if(avlTree->start==NULL)
{
if(success) *success=true;
return avlTreeInOrderIterator;
}
avlTreeInOrderIterator.stack=createStack(&succ);
if(succ==false) return avlTreeInOrderIterator;

t=avlTree->start;
while(t!=NULL)
{
pushOnStack(avlTreeInOrderIterator.stack,(void *)t,&succ);
if(succ==false)
{
destroyStack(avlTreeInOrderIterator.stack);
avlTreeInOrderIterator.stack=NULL;
return avlTreeInOrderIterator;
}
t=t->left;
}
       // main point line
avlTreeInOrderIterator.node=(AVLTreeNode *)popFromStack(avlTreeInOrderIterator.stack,&succ);
if(success) *success=true;
return avlTreeInOrderIterator;
}

bool hasNextInOrderElementInAVLTree(AVLTreeInOrderIterator *avlTreeInOrderIterator)
{
if(avlTreeInOrderIterator==NULL || avlTreeInOrderIterator->node==NULL) return false;
return true;
}

void * getNextInOrderElementFromAVLTree(AVLTreeInOrderIterator *avlTreeInOrderIterator,bool *success)
{
AVLTreeNode *j,*t;
int succ;
if(success) *success=false;
if(avlTreeInOrderIterator==NULL || avlTreeInOrderIterator->node==NULL) return NULL;

j=avlTreeInOrderIterator->node;
t=j->right;
while(t!=NULL)
{
pushOnStack(avlTreeInOrderIterator->stack,(void *)t,&succ);
if(succ==false)
{
destroyStack(avlTreeInOrderIterator->stack);
avlTreeInOrderIterator->stack=NULL;
avlTreeInOrderIterator->node=NULL;
if(success) *success=true;
return j->ptr;
}
t=t->left;
}

if(isStackEmpty(avlTreeInOrderIterator->stack))
{
destroyStack(avlTreeInOrderIterator->stack);
avlTreeInOrderIterator->stack=NULL;
avlTreeInOrderIterator->node=NULL;
}
else
{
avlTreeInOrderIterator->node=(AVLTreeNode *)popFromStack(avlTreeInOrderIterator->stack,&succ);
}
if(success) *success=true;
return j->ptr;
}

AVLTreePreOrderIterator getAVLTreePreOrderIterator(AVLTree *avlTree,bool *success)
{
int succ;
AVLTreePreOrderIterator avlTreePreOrderIterator;
avlTreePreOrderIterator.node=NULL;
avlTreePreOrderIterator.stack=NULL;
if(success) *success=false;
if(avlTree==NULL) return avlTreePreOrderIterator;
if(avlTree->start==NULL)
{
if(success) *success=true;
return avlTreePreOrderIterator;
}
avlTreePreOrderIterator.stack=createStack(&succ);
if(succ==false) return avlTreePreOrderIterator;

avlTreePreOrderIterator.node=avlTree->start;               // <---- main point line
if(success) *success=true;
return avlTreePreOrderIterator;
}

bool hasNextPreOrderElementInAVLTree(AVLTreePreOrderIterator *avlTreePreOrderIterator)
{
if(avlTreePreOrderIterator==NULL || avlTreePreOrderIterator->node==NULL) return false;
return true;
}

void * getNextPreOrderElementFromAVLTree(AVLTreePreOrderIterator *avlTreePreOrderIterator,bool *success)
{
AVLTreeNode *j;
int succ;
if(success) *success=false;
if(avlTreePreOrderIterator==NULL || avlTreePreOrderIterator->node==NULL) return NULL;

j=avlTreePreOrderIterator->node;

if(j->right!=NULL)
{
pushOnStack(avlTreePreOrderIterator->stack,(void *)j->right,&succ);
if(succ==false)
{
destroyStack(avlTreePreOrderIterator->stack);
avlTreePreOrderIterator->stack=NULL;
avlTreePreOrderIterator->node=NULL;
if(success) *success=true;
return j->ptr;
}
}

if(j->left!=NULL)
{
pushOnStack(avlTreePreOrderIterator->stack,(void *)j->left,&succ);
if(succ==false)
{
destroyStack(avlTreePreOrderIterator->stack);
avlTreePreOrderIterator->stack=NULL;
avlTreePreOrderIterator->node=NULL;
if(success) *success=true;
return j->ptr;
}
}

if(isStackEmpty(avlTreePreOrderIterator->stack))
{
destroyStack(avlTreePreOrderIterator->stack);
avlTreePreOrderIterator->stack=NULL;
avlTreePreOrderIterator->node=NULL;
}
else
{
avlTreePreOrderIterator->node=(AVLTreeNode *)popFromStack(avlTreePreOrderIterator->stack,&succ);
}
if(success) *success=true;
return j->ptr;
}

AVLTreePostOrderIterator getAVLTreePostOrderIterator(AVLTree *avlTree,bool *success)
{
int succ;
AVLTreeNode *t;
AVLTreePostOrderIterator avlTreePostOrderIterator;
avlTreePostOrderIterator.node=NULL;
avlTreePostOrderIterator.stack=NULL;
if(success) *success=false;
if(avlTree==NULL) return avlTreePostOrderIterator;
if(avlTree->start==NULL)
{
if(success) *success=true;
return avlTreePostOrderIterator;
}
avlTreePostOrderIterator.stack=createStack(&succ);
if(succ==false) return avlTreePostOrderIterator;

t=avlTree->start;
while(1)
{
while(t!=NULL)
{
if(t->right!=NULL)
{
pushOnStack(avlTreePostOrderIterator.stack,t->right,&succ);
}
pushOnStack(avlTreePostOrderIterator.stack,t,&succ);
t=t->left;
}
t=popFromStack(avlTreePostOrderIterator.stack,&succ);
if(!isStackEmpty(avlTreePostOrderIterator.stack) && t->right!=NULL && t->right==elementAtTopOfStack(avlTreePostOrderIterator.stack,&succ))
{
popFromStack(avlTreePostOrderIterator.stack,&succ);
pushOnStack(avlTreePostOrderIterator.stack,t,&succ);
t=t->right;
}
else
{
break;
}
}
avlTreePostOrderIterator.node=t;                       // <---- main point line
if(success) *success=true;
return avlTreePostOrderIterator;
}

bool hasNextPostOrderElementInAVLTree(AVLTreePostOrderIterator *avlTreePostOrderIterator)
{
if(avlTreePostOrderIterator==NULL || avlTreePostOrderIterator->node==NULL) return false;
return true;
}

void * getNextPostOrderElementFromAVLTree(AVLTreePostOrderIterator *avlTreePostOrderIterator,bool *success)
{
AVLTreeNode *t,*j;
int succ;
if(success) *success=false;
if(avlTreePostOrderIterator==NULL || avlTreePostOrderIterator->node==NULL) return NULL;

j=avlTreePostOrderIterator->node;
if(isStackEmpty(avlTreePostOrderIterator->stack))
{
avlTreePostOrderIterator->node=NULL;
destroyStack(avlTreePostOrderIterator->stack);
if(success) *success=true;
return j->ptr;
}

t=NULL;
while(1)
{
while(t!=NULL)
{
if(t->right!=NULL)
{
pushOnStack(avlTreePostOrderIterator->stack,t->right,&succ);
}
pushOnStack(avlTreePostOrderIterator->stack,t,&succ);
t=t->left;
}
t=popFromStack(avlTreePostOrderIterator->stack,&succ);
if(!isStackEmpty(avlTreePostOrderIterator->stack) && t->right!=NULL && t->right==elementAtTopOfStack(avlTreePostOrderIterator->stack,&succ))
{
popFromStack(avlTreePostOrderIterator->stack,&succ);
pushOnStack(avlTreePostOrderIterator->stack,t,&succ);
t=t->right;
}
else
{
break;
}
}
avlTreePostOrderIterator->node=t;                       // <---- main point line
if(success) *success=true;
return j->ptr;
}
#endif