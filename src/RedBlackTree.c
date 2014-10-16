#include <stdio.h>
#include "RedBlackTree.h"
#include "ErrorCode.h"
#include "Rotations.h"
#include "Node.h"

void addRedBlackTree(Node **nodePtr, Node *newNode)
{
  _addRedBlackTree(nodePtr, newNode);
  (*nodePtr)->color = 'b';
  
}

void _addRedBlackTree(Node **nodePtr, Node *newNode)
{
  if(*nodePtr == NULL)
  {
    *nodePtr = newNode;
    return;
  }
 
  if(newNode->data < (*nodePtr)->data)
  {
    _addRedBlackTree(&(*nodePtr)->left, newNode);
    
    if((*nodePtr)->left->left != NULL)
    {
      if((*nodePtr)->left->color == 'r' && (*nodePtr)->left->left->color == 'r')
      {
        rightRotate(&(*nodePtr));
        (*nodePtr)->right->color = 'r';
      }
    } else if((*nodePtr)->left->right != NULL) {
        if((*nodePtr)->left->color == 'r' && (*nodePtr)->left->right->color == 'r')
        {
          leftRightRotate(&(*nodePtr));
          (*nodePtr)->right->color = 'r';
        }
      }
  }
  
  else
    _addRedBlackTree(&(*nodePtr)->right, newNode);  
}