#ifndef RedBlackTree_H
#define RedBlackTree_H

#include "Rotations.h"
#include "Node.h"
#include "InitNode.h"

void addRedBlackTree(Node **nodePtr, Node *newNode);
void _addRedBlackTree(Node **nodePtr, Node *newNode);
void solveAddViolationForNewNodeLessThan(Node **nodePtr);
void solveAddViolationForNewNodeMoreThan(Node **nodePtr);
void solveAddViolationFor4NodeLessThan(Node **nodePtr);
void solveAddViolationFor4NodeMoreThan(Node **nodePtr);
Node *delRedBlackTree(Node **nodePtr, Node *delNode);
Node *_delRedBlackTree(Node **nodePtr, Node *delNode);
void solveRemoveViolationFor3Nodes(Node **nodePtr);
void solveRemoveViolationFor4Nodes(Node **nodePtr);
Node *_delRedBlackTreeX(Node **nodePtr, Node *delNode);
int isRed(Node **nodePtr);
int isBlack(Node **nodePtr);
int isDoubleBlack(Node **nodePtr);
void solveRemoveViolation(Node **nodePtr);

#endif // RedBlackTree_H
