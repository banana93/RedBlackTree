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
  caseSelect(nodePtr);
  // solveCase1RemoveViolation(nodePtr);
  // solveCase2RemoveViolation(nodePtr);
  // solveCase3RemoveViolation(nodePtr);
  return node;
}

/*
void solveCase1RemoveViolation(Node **nodePtr)
{ 
  // left hand side 
  if((*nodePtr)->left == NULL && (*nodePtr)->right->right != NULL) {
    if((*nodePtr)->right->color == 'b' && (*nodePtr)->right->right->color == 'r') {
    
      leftRotate(&(*nodePtr));
      (*nodePtr)->left->color = 'b';
      (*nodePtr)->right->color = 'b';
      
    } 
  } else if((*nodePtr)->left == NULL && (*nodePtr)->right->left != NULL) {
      if((*nodePtr)->right->color == 'b' && (*nodePtr)->right->left->color == 'r') {
        
        rightLeftRotate(&(*nodePtr));
        (*nodePtr)->left->color = 'b';
        (*nodePtr)->right->color = 'b';
        (*nodePtr)->color = 'b';
      }
    }
        
  // right hand side
  if((*nodePtr)->right == NULL && (*nodePtr)->left->left != NULL) {
    if((*nodePtr)->left->color == 'b' && (*nodePtr)->left->left->color == 'r') {
      
      rightRotate(&(*nodePtr));
      (*nodePtr)->left->color = 'b';
      (*nodePtr)->right->color = 'b';
    
    }
  } else if((*nodePtr)->right == NULL && (*nodePtr)->left->right != NULL) {
      if((*nodePtr)->left->color == 'b' && (*nodePtr)->left->right->color == 'r') {
        
        leftRightRotate(&(*nodePtr));
        (*nodePtr)->color = 'b';
        (*nodePtr)->left->color = 'b';
        (*nodePtr)->right->color = 'b';
      
      }
     } 
}

void solveCase2RemoveViolation(Node **nodePtr)
{
  if((*nodePtr)->left == NULL && (*nodePtr)->right != NULL) {
    if(((*nodePtr)->color == 'b' && (*nodePtr)->right->color == 'b') ||
       ((*nodePtr)->color == 'r' && (*nodePtr)->right->color == 'b')) {
          
        (*nodePtr)->color = 'b';
        (*nodePtr)->right->color = 'r';
        
    } 
  } else if((*nodePtr)->right == NULL && (*nodePtr)->left != NULL) {
            if(((*nodePtr)->color == 'b' && (*nodePtr)->left->color == 'b') ||
               ((*nodePtr)->color == 'r' && (*nodePtr)->left->color == 'b')) {
              
              (*nodePtr)->color = 'b';
              (*nodePtr)->left->color = 'r';
            
            }
    }
}  

void solveCase3RemoveViolation(Node **nodePtr)
{
  if((*nodePtr)->left == NULL && (*nodePtr)->right->right != NULL && (*nodePtr)->right->left != NULL) {
    if((*nodePtr)->left == NULL && (*nodePtr)->right->color == 'r') {
      
      leftRotate(&(*nodePtr));
      (*nodePtr)->color = 'b';
      (*nodePtr)->left->color = 'r';
    }
  } else if((*nodePtr)->right == NULL && (*nodePtr)->left->left != NULL && (*nodePtr)->left->right != NULL) {
      if((*nodePtr)->right == NULL && (*nodePtr)->left->color == 'r') {
        
        rightRotate(&(*nodePtr));
        (*nodePtr)->color = 'b';
        (*nodePtr)->right->color = 'r';
        
      }
    }
}
*/
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
    } else {
        return 0;
      }
  }   
}

int isDoubleBlack(Node **nodePtr) 
{
  if((*nodePtr) == NULL || (*nodePtr)->color == 'd') {
      return 1;
  } else {
        return 0;
    }
  
}

void caseSelect(Node **nodePtr)
{
  // Solve Case 1 Right Hand Side 
  if((isDoubleBlack(&(*nodePtr)->left) && isBlack(&(*nodePtr)->right) && isRed(&(*nodePtr)->right->right)) ||
    (isDoubleBlack(&(*nodePtr)->left) && isBlack(&(*nodePtr)->right) && isRed(&(*nodePtr)->right->left))) {
    solveCase1RightRemoveViolation(nodePtr);
  } 
  // Solve Case 1 Left Hand Side
  else if((isDoubleBlack(&(*nodePtr)->right) && isBlack(&(*nodePtr)->left) && isRed(&(*nodePtr)->left->left)) ||
         (isDoubleBlack(&(*nodePtr)->right) && isBlack(&(*nodePtr)->left) && isRed(&(*nodePtr)->left->right))) {
      solveCase1LeftRemoveViolation(nodePtr);
  }
  // Solve Case 2 Left Hand Side
  else if(isDoubleBlack(&(*nodePtr)->right) && isBlack(&(*nodePtr)->left)) {
    solveCase2LeftRemoveViolation(nodePtr);
  }
  // Solve Case 2 Right Hand Side
  else if(isDoubleBlack(&(*nodePtr)->left) && isBlack(&(*nodePtr)->right)) {
    solveCase2RightRemoveViolation(nodePtr);
  }
  // Solve Case 3 Right Hand Side
  else if(isDoubleBlack(&(*nodePtr)->left) && isRed(&(*nodePtr)->right)) {
    solveCase3RightRemoveViolation(nodePtr);
  }
  // Solve Case 3 Left Hand Side
  else if(isDoubleBlack(&(*nodePtr)->right) && isRed(&(*nodePtr)->left)) {
    solveCase3LeftRemoveViolation(nodePtr);
  }
}

void solveCase1LeftRemoveViolation(Node **nodePtr)
{
  Node *tempNode = *nodePtr;
  
  if(isDoubleBlack(&(*nodePtr)->right) && isRed(&(*nodePtr)->left->left)) {
    rightRotate(&(*nodePtr));
  } else if(isDoubleBlack(&(*nodePtr)->right) && isRed(&(*nodePtr)->left->right)) {
      leftRightRotate(&(*nodePtr));
    }
    
  (*nodePtr)->left->color = 'b';
  (*nodePtr)->right->color = 'b';
  (*nodePtr)->color = tempNode->color;
}
void solveCase1RightRemoveViolation(Node **nodePtr)
{
  Node *tempNode = *nodePtr;
  
  if(isDoubleBlack(&(*nodePtr)->left) && (*nodePtr)->right->right != NULL) {
    leftRotate(&(*nodePtr));
  } else if(isDoubleBlack(&(*nodePtr)->left) && (*nodePtr)->right->left != NULL) {
      rightLeftRotate(&(*nodePtr));
    }
  
  (*nodePtr)->left->color = 'b';
  (*nodePtr)->right->color = 'b';
  (*nodePtr)->color = tempNode->color;
}

void solveCase2LeftRemoveViolation(Node **nodePtr)
{
  if((*nodePtr)->left->left == NULL && (*nodePtr)->left->right == NULL && (*nodePtr)->color == 'b') {
    (*nodePtr)->left->color = 'r';
    (*nodePtr)->color = 'd';
  } else if((*nodePtr)->left->left == NULL && (*nodePtr)->left->right == NULL && (*nodePtr)->color == 'r') {
      (*nodePtr)->left->color = 'r';
      (*nodePtr)->color = 'b';
    }
}

void solveCase2RightRemoveViolation(Node **nodePtr)
{
  if((*nodePtr)->right->right == NULL && (*nodePtr)->right->left == NULL && (*nodePtr)->color == 'b') {
    (*nodePtr)->right->color = 'r';
    (*nodePtr)->color = 'd';
  } else if((*nodePtr)->right->right == NULL && (*nodePtr)->right->left == NULL && (*nodePtr)->color == 'r') {
      (*nodePtr)->right->color = 'r';
      (*nodePtr)->color = 'b';
    }
}

void solveCase3LeftRemoveViolation(Node **nodePtr)
{
  rightRotate(&(*nodePtr));
  (*nodePtr)->right->color = 'r';
  (*nodePtr)->color = 'b';
  
  if(isDoubleBlack(&(*nodePtr)->right->right) && (*nodePtr)->right->left->left != NULL && (*nodePtr)->right->left->left->color == 'r') {
    solveCase1LeftRemoveViolation(&(*nodePtr)->right);
    (*nodePtr)->right->color = 'r';   
  } else if(isDoubleBlack(&(*nodePtr)->right->left) && (*nodePtr)->right->right->right != NULL && (*nodePtr)->right->right->right->color == 'r') {
      solveCase1RightRemoveViolation(&(*nodePtr)->right);
      (*nodePtr)->right->color = 'r';
    } else if(isDoubleBlack(&(*nodePtr)->right->left) && (*nodePtr)->right->right != NULL) {
        solveCase2RightRemoveViolation(&(*nodePtr)->right);
      } else if(isDoubleBlack(&(*nodePtr)->right->right) && (*nodePtr)->right->left != NULL) {
          solveCase2LeftRemoveViolation(&(*nodePtr)->right);
        }
}

void solveCase3RightRemoveViolation(Node **nodePtr)
{
  leftRotate(&(*nodePtr));
  (*nodePtr)->left->color = 'r';
  (*nodePtr)->color = 'b';
  
  if(isDoubleBlack(&(*nodePtr)->left->left) && (*nodePtr)->left->right->right != NULL && (*nodePtr)->left->right->right->color == 'r') {
    solveCase1RightRemoveViolation(&(*nodePtr)->left);
    (*nodePtr)->left->color = 'r';   
  } else if(isDoubleBlack(&(*nodePtr)->left->right) && (*nodePtr)->left->left->left != NULL && (*nodePtr)->left->left->left->color == 'r') {
      solveCase1LeftRemoveViolation(&(*nodePtr)->left);
      (*nodePtr)->left->color = 'r';
    } else if(isDoubleBlack(&(*nodePtr)->left->left) && (*nodePtr)->left->right != NULL) {
        solveCase2RightRemoveViolation(&(*nodePtr)->left);
      } else if(isDoubleBlack(&(*nodePtr)->left->right) && (*nodePtr)->left->left != NULL) {
          solveCase2LeftRemoveViolation(&(*nodePtr)->left);
        }
}