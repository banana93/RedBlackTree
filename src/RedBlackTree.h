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
Node *delRedBlackTree(Node **nodePtr, Node *newNode);
Node *_delRedBlackTree(Node **nodePtr, Node *newNode);

#endif // RedBlackTree_H
