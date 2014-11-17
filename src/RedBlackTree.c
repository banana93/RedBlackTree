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
    solveAddViolationForNewNodeLessThan(&(*nodePtr)); // this function purpose is to solve the violation for those new node data that is less than the nodePtr data
    solveAddViolationFor4NodeLessThan(&(*nodePtr));
  }
  
  else
  {
    _addRedBlackTree(&(*nodePtr)->right, newNode); 
    solveAddViolationForNewNodeMoreThan(&(*nodePtr)); // this function purpose is to solve the violation for those new node data that is more than the nodePtr data
    solveAddViolationFor4NodeMoreThan(&(*nodePtr));
  }
}

void solveAddViolationForNewNodeLessThan(Node **nodePtr)
{
  if((*nodePtr)->left->left != NULL) {
    if(((*nodePtr)->left->color == 'r' && (*nodePtr)->left->left->color == 'r' && (*nodePtr)->right == NULL) ||
       ((*nodePtr)->left->color == 'r' && (*nodePtr)->left->left->color == 'r' && (*nodePtr)->right->color == 'b')) {
     
      rightRotate(&(*nodePtr));
      (*nodePtr)->right->color = 'r';
    
    }
  } else if((*nodePtr)->left->right != NULL) {
      if(((*nodePtr)->left->color == 'r' && (*nodePtr)->left->right->color == 'r' && (*nodePtr)->right == NULL) ||
        ((*nodePtr)->left->color == 'r' && (*nodePtr)->left->right->color == 'r' && (*nodePtr)->right->color == 'b')) {
       
        leftRightRotate(&(*nodePtr));
        (*nodePtr)->right->color = 'r';
      
      }
    } 
}

void solveAddViolationForNewNodeMoreThan(Node **nodePtr)
{
  if((*nodePtr)->right->right != NULL) {
    if(((*nodePtr)->right->color == 'r' && (*nodePtr)->right->right->color == 'r' && (*nodePtr)->left == NULL) ||
      ((*nodePtr)->right->color == 'r' && (*nodePtr)->right->right->color == 'r' && (*nodePtr)->left->color == 'b')){
      
      leftRotate(&(*nodePtr));
      (*nodePtr)->left->color = 'r';
    
    } 
  } else if ((*nodePtr)->right->left != NULL) {
      if(((*nodePtr)->right->color == 'r' && (*nodePtr)->right->left->color == 'r' && (*nodePtr)->left == NULL) || 
        ((*nodePtr)->right->color == 'r' && (*nodePtr)->right->left->color == 'r' && (*nodePtr)->left->color == 'b')){
       
        rightLeftRotate(&(*nodePtr));
        (*nodePtr)->left->color = 'r';
      
      }
   }
}  

void solveAddViolationFor4NodeLessThan(Node **nodePtr)
{
  if((*nodePtr)->left->left != NULL && (*nodePtr)->right != NULL) {
    if((*nodePtr)->left->color == 'r' && (*nodePtr)->right->color == 'r' && (*nodePtr)->left->left->color == 'r') {
     
      (*nodePtr)->left->color = 'b';
      (*nodePtr)->right->color = 'b';
      (*nodePtr)->color = 'r';
    
    }
  } else if((*nodePtr)->left->right != NULL && (*nodePtr)->right != NULL) {
      if((*nodePtr)->left->color == 'r' && (*nodePtr)->right->color == 'r' && (*nodePtr)->left->right->color == 'r') {
      
        (*nodePtr)->left->color = 'b';
        (*nodePtr)->right->color = 'b';
        (*nodePtr)->color = 'r';
      
      }
    }
}

void solveAddViolationFor4NodeMoreThan(Node **nodePtr)
{
  if((*nodePtr)->right->left != NULL && (*nodePtr)->left != NULL) {
    if((*nodePtr)->right->color == 'r' && (*nodePtr)->left->color == 'r' && (*nodePtr)->right->left->color == 'r') {
      
      (*nodePtr)->left->color = 'b';
      (*nodePtr)->right->color = 'b';
      (*nodePtr)->color = 'r';
    
    } 
  } else if((*nodePtr)->right->right != NULL && (*nodePtr)->left != NULL) {
      if((*nodePtr)->right->color == 'r' && (*nodePtr)->left->color == 'r' && (*nodePtr)->right->right->color == 'r') {
      
        (*nodePtr)->left->color = 'b';
        (*nodePtr)->right->color = 'b';
        (*nodePtr)->color = 'r';
        
      }
    }
}

Node *delRedBlackTree(Node **nodePtr, Node *delNode)
{
  Node *node = _delRedBlackTree(nodePtr, delNode);
  
  if((*nodePtr) != NULL)
    (*nodePtr)->color = 'b';
  
  return node;
}
/*
Node *_delRedBlackTreeX(Node **nodePtr, Node *delNode)
{
  Node *tempNode = *nodePtr;
  Node *node;
  
  if(tempNode == NULL)
    Throw(ERR_NODE_UNAVAILABLE);
  
  if(tempNode->data == delNode->data) {
    *nodePtr = NULL;
    return tempNode;
  } else if(tempNode->data < delNode->data) {
      node = _delRedBlackTree(&tempNode->right, delNode); 
    } else if (tempNode->data > delNode->data) { 
        node = _delRedBlackTree(&tempNode->left, delNode);
      }

    if(nodePtr != NULL) {
      solveRemoveViolationFor3Nodes(nodePtr);
      solveRemoveViolationFor4Nodes(nodePtr);
    }
    
  return node;
}

void solveRemoveViolationFor3Nodes(Node **nodePtr)
{
  if((*nodePtr)->left == NULL && (*nodePtr)->right != NULL) {
    if((*nodePtr)->right->right != NULL && (*nodePtr)->right->left != NULL) {
     
      leftRotate(&(*nodePtr));
      (*nodePtr)->left->right->color = 'r';
    
    }
  } else if((*nodePtr)->left != NULL && (*nodePtr)->right == NULL) {
      if((*nodePtr)->left->left != NULL && (*nodePtr)->left->right != NULL) {
        
        rightRotate(&(*nodePtr));
        (*nodePtr)->right->left->color = 'r';
      
      }
    } else if((*nodePtr)->left != NULL && (*nodePtr)->right != NULL) {
        if((*nodePtr)->left->left == NULL && (*nodePtr)->right->right != NULL && (*nodePtr)->right->left == NULL) {
    
          (*nodePtr)->right->color = 'b';
          (*nodePtr)->right->right->color = 'r';
      
        } else if((*nodePtr)->left->left == NULL && (*nodePtr)->right->right == NULL && (*nodePtr)->right->left != NULL) {
          
            (*nodePtr)->right->color = 'b';
            (*nodePtr)->right->left->color = 'r';
        
          } else if((*nodePtr)->right->right == NULL && (*nodePtr)->left->left == NULL && (*nodePtr)->left->right != NULL) {
              
              (*nodePtr)->left->color = 'b';
              (*nodePtr)->left->right->color = 'r';
            
            } else if ((*nodePtr)->right->right == NULL && (*nodePtr)->left->right == NULL && (*nodePtr)->left->left != NULL) {
                
                (*nodePtr)->left->color = 'b';
                (*nodePtr)->left->left->color = 'r';
              
              }
      } 
}

void solveRemoveViolationFor4Nodes(Node **nodePtr)
{
  if((*nodePtr)->left != NULL && (*nodePtr)->right != NULL) {
    if((*nodePtr)->right->right != NULL && (*nodePtr)->left->left == NULL && (*nodePtr)->left->right != NULL) {
      
      (*nodePtr)->left->color = 'b';
      (*nodePtr)->left->right->color = 'r';
    
    } else if((*nodePtr)->right->right != NULL && (*nodePtr)->left->left != NULL && (*nodePtr)->left->right == NULL) {
      
        (*nodePtr)->left->color = 'b';
        (*nodePtr)->left->left->color = 'r';
      
      } else if((*nodePtr)->left->left != NULL && (*nodePtr)->right->right != NULL && (*nodePtr)->right->left == NULL) {
          
          (*nodePtr)->right->color = 'b';
          (*nodePtr)->right->right->color = 'r';
        
        } else if((*nodePtr)->left->left != NULL && (*nodePtr)->right->right == NULL && (*nodePtr)->right->left != NULL) {
         
            (*nodePtr)->right->color = 'b';
            (*nodePtr)->right->left->color = 'r';
          
          }
  }
}
*/

// New function for _delRedBlackTree //
Node *_delRedBlackTree(Node **nodePtr, Node *delNode)
{
  Node *tempNode = *nodePtr;
  Node *node;
  
  if(tempNode == NULL)
    Throw(ERR_NODE_UNAVAILABLE);
  
  if(tempNode->data == delNode->data) {
    *nodePtr = NULL;
    return tempNode;
  } else if(tempNode->data < delNode->data) {
      node = _delRedBlackTree(&tempNode->right, delNode); 
    } else if (tempNode->data > delNode->data) { 
        node = _delRedBlackTree(&tempNode->left, delNode);
      }
      
  checkCase(nodePtr, delNode);
  
  return node;
}

int isRed(Node **nodePtr)
{
  if((*nodePtr) != NULL) {
    if((*nodePtr)->color == 'r') {
      return 1;
    } else {
        return 0;
      }
  }
}

int isBlack(Node **nodePtr)
{
  if((*nodePtr) != NULL) {
    if((*nodePtr)->color == 'b') {
      return 1;
    } else if((*nodePtr)->color == 'r') {
        return 0;
      }
  } else if((*nodePtr) == NULL) {
        return 1;
    } else {
        return 0;
      }
     
}

int isDoubleBlack(Node **nodePtr, Node *removeNode) 
{
  if((*nodePtr) != NULL && (*nodePtr)->color == 'd'){
      return 1;
  } else if((*nodePtr) == NULL && removeNode->color == 'b'){
        return 1;
    } else {
        return 0;
      }  
}

void checkCase(Node **nodePtr, Node *removeNode)
{
  // Solve Case Right Hand Side 
  if(isDoubleBlack((&(*nodePtr)->left), removeNode)){
    // Case 1
    if((isBlack(&(*nodePtr)->right) && isRed(&(*nodePtr)->right->right)) ||
      (isBlack(&(*nodePtr)->right) && isRed(&(*nodePtr)->right->left)))
        solveCase1RightRemoveViolation(nodePtr, removeNode);
    // Case 2
    else if(isBlack(&(*nodePtr)->right) && isBlack(&(*nodePtr)->right->right) && isBlack(&(*nodePtr)->right->left)) 
        solveCase2RightRemoveViolation(nodePtr, removeNode);
    // Case 3
    else if(isRed(&(*nodePtr)->right))
        solveCase3RightRemoveViolation(nodePtr, removeNode);
  }
  // Solve Case Left Hand Side
  else if(isDoubleBlack((&(*nodePtr)->right), removeNode)){
    // Case 1
    if((isBlack(&(*nodePtr)->left) && isRed(&(*nodePtr)->left->left)) ||
       (isBlack(&(*nodePtr)->left) && isRed(&(*nodePtr)->left->right)))
          solveCase1LeftRemoveViolation(nodePtr, removeNode);
    // Case 2
    else if(isBlack(&(*nodePtr)->left) && isBlack(&(*nodePtr)->left->left) && isBlack(&(*nodePtr)->left->right))
          solveCase2LeftRemoveViolation(nodePtr, removeNode);
    // Case 3
    else if(isRed(&(*nodePtr)->left)) 
          solveCase3LeftRemoveViolation(nodePtr, removeNode);
  }
}

void solveCase1LeftRemoveViolation(Node **nodePtr, Node *removeNode)
{
  Node *tempNode = *nodePtr;
  
  if(isRed(&(*nodePtr)->left->left)) {
    rightRotate(&(*nodePtr));
  } else if(isRed(&(*nodePtr)->left->right)) {
      leftRightRotate(&(*nodePtr));
    }
    
  (*nodePtr)->color = tempNode->color;
  (*nodePtr)->left->color = 'b';
  (*nodePtr)->right->color = 'b';
}
void solveCase1RightRemoveViolation(Node **nodePtr, Node *removeNode)
{
  Node *tempNode = *nodePtr;
  
  if((*nodePtr)->right->right != NULL) {
    leftRotate(&(*nodePtr));
  } else if((*nodePtr)->right->left != NULL) {
      rightLeftRotate(&(*nodePtr));
    }
  
  (*nodePtr)->color = tempNode->color;
  (*nodePtr)->left->color = 'b';
  (*nodePtr)->right->color = 'b';
}

void solveCase2LeftRemoveViolation(Node **nodePtr, Node *removeNode)
{
  if(isBlack(&(*nodePtr)->left->left) && isBlack(&(*nodePtr)->left->right) && (*nodePtr)->color == 'b') {
    (*nodePtr)->color = 'd';
    (*nodePtr)->left->color = 'r';
  } else if(isBlack(&(*nodePtr)->left->left) && isBlack(&(*nodePtr)->left->right) && (*nodePtr)->color == 'r') {
      (*nodePtr)->left->color = 'r';
      (*nodePtr)->color = 'b';
    }
}

void solveCase2RightRemoveViolation(Node **nodePtr, Node *removeNode)
{
  if(isBlack(&(*nodePtr)->right->right) && isBlack(&(*nodePtr)->right->left) && (*nodePtr)->color == 'b') {
    (*nodePtr)->color = 'd';
    (*nodePtr)->right->color = 'r';
    
    // new condition added due to promotion of double black and the nodePtr->left is not NULL
    if((*nodePtr)->left != NULL) 
      (*nodePtr)->left->color = 'b';
  } else if(isBlack(&(*nodePtr)->right->right) && isBlack(&(*nodePtr)->right->left) && (*nodePtr)->color == 'r') {
      (*nodePtr)->right->color = 'r';
      (*nodePtr)->color = 'b';
    }
}

void solveCase3LeftRemoveViolation(Node **nodePtr, Node *removeNode)
{
  rightRotate(&(*nodePtr));
  (*nodePtr)->right->color = 'r';
  (*nodePtr)->color = 'b';
  
  checkCase((&(*nodePtr)->right), removeNode);
}

void solveCase3RightRemoveViolation(Node **nodePtr, Node *removeNode)
{
  leftRotate(&(*nodePtr));
  (*nodePtr)->left->color = 'r';
  (*nodePtr)->color = 'b';
  
  checkCase((&(*nodePtr)->left), removeNode);
}

Node *removeNextLargerSuccessor(Node **nodePtr)
{
  Node *leftNode, *rightNode;
  Node *node = *nodePtr;
  
  if(node->left == NULL && node->right == NULL) {
    node = (*nodePtr);
    (*nodePtr) = NULL;
    return node;
  } else {
      if(node->left != NULL) {
        node = removeNextLargerSuccessor(&node->left);
      } else if(node->right != NULL) {
          rightNode = node->right;
          *nodePtr = rightNode;
          node->right = NULL;
          node->color = 'b';
        }
    } 
     
  checkCase(&(*nodePtr), node);
  
  return node;
  
}