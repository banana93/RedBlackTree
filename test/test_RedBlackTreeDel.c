#include <stdio.h>
#include "unity.h"
#include "RedBlackTree.h"
#include "Node.h"
#include "InitNode.h"
#include "CustomAssertions.h"
#include "Rotations.h"
#include "CException.h"

Node node1, node2, node3, node5, node6, node7, node8, node10, node12, node13, node15, node17, node18, node20, node30;

void setUp(void){
	resetNode(&node1, 1);
	resetNode(&node2, 2);
	resetNode(&node3, 3);
	resetNode(&node5, 5);
	resetNode(&node6, 6);
	resetNode(&node7, 7);
	resetNode(&node8, 8);
	resetNode(&node10, 10);
	resetNode(&node12, 12);
	resetNode(&node13, 13);
	resetNode(&node15, 15);
	resetNode(&node17, 17);
	resetNode(&node18, 18);
	resetNode(&node20, 20);
	resetNode(&node30, 30);
}

void tearDown(void){}

/** 2-node case
 *          root                      
 *           |      remove 2          
 *           v    ------------->  Throw ERR_NODE_UNAVAILABLE  
 *          1(b)                     
 */
void test_delRedBlackTree_remove_2_from_tree_with_root_1_should_throw_ERR_NODE_UNAVAILABLE(void)
{
  CEXCEPTION_T err;
  setNode(&node1, NULL, NULL, 'b');
  Node *root = &node1;
  
  Try
  {
    delRedBlackTree(&root, &node2);
    TEST_FAIL_MESSAGE("Expected ERR_NODE_UNAVAILABLE to be thrown");
  }
  Catch(err)
  {
    TEST_ASSERT_EQUAL_PTR(root, &node1);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node1);
  }
}

/** 2-node case
 *          root                     root 
 *           |      remove 1          |
 *           v    ------------->      v
 *          1(b)                     NULL
 */
void test_delRedBlackTree_remove_1_from_tree_with_root_1(void)
{
  setNode(&node1, NULL, NULL, 'b');
  Node *root = &node1;
  
  delRedBlackTree(&root, &node1);
  
  TEST_ASSERT_EQUAL_PTR(root, NULL);
}

/** 2-node case
 *       root                        root 
 *        |                           |
 *        v        remove 2           v
 *       1(b)    ------------>       1(b)
 *          \ 
 *          2(r)
 */
void test_delRedBlackTree_remove_2_from_tree_with_1_2_nodes(void)
{
  setNode(&node2, NULL, NULL, 'r');
  setNode(&node1, NULL, &node2, 'b');
  Node *root = &node1;
  
  delRedBlackTree(&root, &node2);
  
  TEST_ASSERT_EQUAL_PTR(root, &node1);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node1);
}

/** 2-node case
 *         root                       root
 *          |                          |
 *          v       remove 1           v
 *         2(b)    --------->        2(b)
 *        /
 *      1(r)
 */
void test_delRedBlackTree_remove_1_from_tree_with_2_1_nodes(void)
{
  setNode(&node1, NULL, NULL, 'r');
  setNode(&node2, &node1, NULL, 'b');
  Node *root = &node2;
  
  delRedBlackTree(&root, &node1);
  
  TEST_ASSERT_EQUAL_PTR(root, &node2);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node2);
}

/**
 *      root                       root
 *       |                          |
 *       v          remove 1        v
 *      2(b)        --------->     2(b)
 *     /   \                      /    \
 *   1(r)   3(r)                 -      3(r)
 */
void test_delRedBlackTree_remove_1_from_tree_with_2_1_3_nodes(void)
{
  setNode(&node1, NULL, NULL, 'r');
  setNode(&node3, NULL, NULL, 'r');
  setNode(&node2, &node1, &node3, 'b');
  Node *root = &node2;
  
  delRedBlackTree(&root, &node1);
  
  TEST_ASSERT_EQUAL_PTR(root, &node2);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node3);
  TEST_ASSERT_EQUAL_NODE(NULL, &node3, 'b', &node2);
}

/**
 *       root                         root 
 *        |                            |
 *        v          remove 3          v
 *       2(b)       ----------->      2(b)
 *      /    \                       /    \
 *    1(r)    3(r)                 1(r)    -
 */
void test_delRedBlackTree_remove_3_from_tree_with_2_1_3_nodes(void)
{
  setNode(&node1, NULL, NULL, 'r');
  setNode(&node3, NULL, NULL, 'r');
  setNode(&node2, &node1, &node3, 'b');
  Node *root = &node2;
  
  delRedBlackTree(&root, &node3);
  
  TEST_ASSERT_EQUAL_PTR(root, &node2);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node1);
  TEST_ASSERT_EQUAL_NODE(&node1, NULL, 'b', &node2);
}