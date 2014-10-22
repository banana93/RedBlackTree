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
    solveViolationForNewNodeLessThan(&(*nodePtr)); // this function purpose is to solve the violation for those new node data that is less than the nodePtr data
  }
  
  else
  {
    _addRedBlackTree(&(*nodePtr)->right, newNode); 
    solveViolationForNewNodeMoreThan(&(*nodePtr)); // this function purpose is to solve the violation for those new node data that is more than the nodePtr data
  }
}

void solveViolationForNewNodeLessThan(Node **nodePtr)
{
  if((*nodePtr)->left->left != NULL) {
    if((*nodePtr)->left->color == 'r' && (*nodePtr)->left->left->color == 'r') {
      rightRotate(&(*nodePtr));
      (*nodePtr)->right->color = 'r';
    }
  } else if((*nodePtr)->left->right != NULL) {
      if((*nodePtr)->left->color == 'r' && (*nodePtr)->left->right->color == 'r') {
        leftRightRotate(&(*nodePtr));
        (*nodePtr)->right->color = 'r';
     }
   } 
}

void solveViolationForNewNodeMoreThan(Node **nodePtr)
{
  if((*nodePtr)->right->right != NULL) {
    if((*nodePtr)->right->color == 'r' && (*nodePtr)->right->right->color == 'r') {
      leftRotate(&(*nodePtr));
      (*nodePtr)->left->color = 'r';
    } 
  } else if ((*nodePtr)->right->left != NULL) {
      if((*nodePtr)->right->color == 'r' && (*nodePtr)->right->left->color == 'r') {
        rightLeftRotate(&(*nodePtr));
        (*nodePtr)->left->color = 'r';
      }
   }
}  
