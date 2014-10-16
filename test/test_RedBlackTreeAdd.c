#include <stdio.h>
#include "unity.h"
#include "RedBlackTree.h"
#include "Node.h"
#include "InitNode.h"
#include "CustomAssertions.h"
#include "Rotations.h"

Node node1, node5, node6, node7, node8, node10, node13, node15, node17, node20, node30;

void setUp(void){
	resetNode(&node1, 1);
	resetNode(&node5, 5);
	resetNode(&node6, 6);
	resetNode(&node7, 7);
	resetNode(&node8, 8);
	resetNode(&node10, 10);
	resetNode(&node13, 13);
	resetNode(&node15, 15);
	resetNode(&node17, 17);
	resetNode(&node20, 20);
	resetNode(&node30, 30);
}

void tearDown(void){}

/**
 *          root                 root
 *           |                    |                   
 *           v     add 10         v
 *          NULL  --------->     10                  
 */
void xtest_addRedBlackTree_add_10_to_empty_tree(void)
{
	setNode(&node10, NULL, NULL, 'r');
  Node *root = NULL;
  
  addRedBlackTree(&root, &node10);
	
	TEST_ASSERT_EQUAL_PTR(root, &node10);
	TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node10);
}

/**
 *        root                     root
 *         |       add 5            |
 *         v   ------------->       v
 *        10                       10(b)
 *                                / 
 *                              5(r)
 */
void xtest_addRedBlackTree_add_5_to_tree_with_root_10(void)
{
  setNode(&node10, NULL, NULL, 'b');
  setNode(&node5, NULL, NULL, 'r');
  Node *root = &node10;
  
  addRedBlackTree(&root, &node5);
  
  TEST_ASSERT_EQUAL_PTR(root, &node10);
  //                     left    right color  node
  TEST_ASSERT_EQUAL_NODE(&node5, NULL, 'b', &node10);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node5);
}

/**
 *        root                     root
 *         |       add 13            |
 *         v   ------------->       v
 *        10                       10(b)
 *                                   \ 
 *                                   13(r)
 */
void xtest_addRedBlackTree_add_13_to_tree_with_root_10(void)
{
  setNode(&node10, NULL, NULL, 'b');
  setNode(&node13, NULL, NULL, 'r');
  Node *root = &node10;
  
  addRedBlackTree(&root, &node13);
  
  TEST_ASSERT_EQUAL_PTR(root, &node10);
  //                     left    right color  node
  TEST_ASSERT_EQUAL_NODE(NULL, &node13, 'b', &node10);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node13);
}

/**
 *        root                 root                 root 
 *         |                    |                    |
 *         v                    v      rotate        v
 *        10(b)    add 5       10      right         7(b)
 *       /  \    -------->    /  \    --------->    /  \
 *     7(r)                 7                     5(r)  10(r)
 *                         /
 *                        5
 */
void test_addRedBlackTree_add_5_to_a_tree_with_root_10_and_left_child_7(void)
{
  setNode(&node7, NULL, NULL, 'r');
  setNode(&node5, NULL, NULL, 'r');
  setNode(&node10, &node7, NULL, 'b');
  Node *root = &node10;
  
  addRedBlackTree(&root, &node5);
  
  TEST_ASSERT_EQUAL_PTR(root, &node7);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node10);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node5);
  TEST_ASSERT_EQUAL_NODE(&node5, &node10, 'b', &node7);
}

/**
 *         root                  root                     root                 root
 *          |                     |                        |                    |
 *          v                     v       rotate           v      rotate        v   
 *        10(b)    add 8         10(b)     left           10(b)    right       8(b)
 *        /  \   ---------->     /  \    ---------->      /  \  ---------->   /   \
 *      7(r)                   7(r)                     8(r)                7(r)  10(r)
 *                             /  \                    /
 *                                8(r)               7(r)
 */
void test_addRedBlackTree_add_8_to_a_tree_withroot_10_and_left_child_7(void)
{
  setNode(&node7, NULL, NULL, 'r');
  setNode(&node8, NULL, NULL, 'r');
  setNode(&node10, &node7, NULL, 'b');
  Node *root = &node10;
  
  addRedBlackTree(&root, &node8);
  
  TEST_ASSERT_EQUAL_PTR(root, &node8);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node10);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node7);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node8);
}