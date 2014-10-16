#include <stdio.h>
#include "RedBlackTree.h"
#include "ErrorCode.h"

void addRedBlackTree(Node **nodePtr, Node *newNode)
{
  _addRedBlackTree(nodePtr, newNode);
  (*nodePtr)->color = 'b';
  
}

void _addRedBlackTree(Node **nodePtr, Node *newNode)
{
  if(*nodePtr == NULL)
    *nodePtr = newNode;
  
  else
  {
    if(newNode->data <= (*nodePtr)->data)
      (*nodePtr)->left = newNode;
    else  
      (*nodePtr)->right = newNode;
  }
}