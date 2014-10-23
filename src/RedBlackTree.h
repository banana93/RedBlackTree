#ifndef RedBlackTree_H
#define RedBlackTree_H

#include "Rotations.h"
#include "Node.h"
#include "InitNode.h"

void addRedBlackTree(Node **nodePtr, Node *newNode);
void _addRedBlackTree(Node **nodePtr, Node *newNode);
void solveViolationForNewNodeLessThan(Node **nodePtr);
void solveViolationForNewNodeMoreThan(Node **nodePtr);
void solveViolationFor4NodeLessThan(Node **nodePtr);
void solveViolationFor4NodeMoreThan(Node **nodePtr);

#endif // RedBlackTree_H
