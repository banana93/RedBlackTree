#include <stdio.h>
#include "unity.h"
#include "RedBlackTree.h"
#include "Node.h"
#include "InitNode.h"
#include "CustomAssertions.h"
#include "Rotations.h"
#include "CException.h"

Node node1, node2, node3, node4, node5, node6, node7, node8, node10, node12, node13, node15, node17, node18, node20, node30;

void setUp(void){
	resetNode(&node1, 1);
	resetNode(&node2, 2);
	resetNode(&node3, 3);
	resetNode(&node4, 4);
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
  
  _delRedBlackTree(&root, &node1);
  
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

/**
 *        root                               root 
 *         |                                  |
 *         v                                  v
 *        2(b)           remove 1            5(b)
 *       /   \         ------------>        /   \
 *     1(b)   5(r)                        2(b)   6(b)
 *           /   \                           \
 *         3(b)  6(b)                        3(r)
 */
void test_delRedBlackTree_remove_1_from_tree_with_2_1_5_3_6_nodes(void)
{
  setNode(&node1, NULL, NULL, 'b');
  setNode(&node3, NULL, NULL, 'b');
  setNode(&node6, NULL, NULL, 'b');
  setNode(&node5, &node3, &node6, 'r');
  setNode(&node2, &node1, &node5, 'b');
  Node *root = &node2;
  
  delRedBlackTree(&root, &node1);
  
  TEST_ASSERT_EQUAL_PTR(root, &node5);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node3);
  TEST_ASSERT_EQUAL_NODE(NULL, &node3, 'b', &node2);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node6);
  TEST_ASSERT_EQUAL_NODE(&node2, &node6, 'b', &node5);
}

/**
 *        root                             root
 *         |                                |
 *         v                                v
 *        2(b)           remove 3          2(b)
 *       /   \         ------------->     /   \
 *     1(b)   5(r)                      1(b)   5(b)
 *           /   \                                \
 *         3(b)  6(b)                            6(r)
 */
void test_delRedBlackTree_remove_3_from_tree_with_2_1_5_3_6_nodes(void)
{
  setNode(&node1, NULL, NULL, 'b');
  setNode(&node3, NULL, NULL, 'b');
  setNode(&node6, NULL, NULL, 'b');
  setNode(&node5, &node3, &node6, 'r');
  setNode(&node2, &node1, &node5, 'b');
  Node *root = &node2;
  
  delRedBlackTree(&root, &node3);
  
  TEST_ASSERT_EQUAL_PTR(root, &node2);
  TEST_ASSERT_EQUAL_NODE(&node1, &node5, 'b', &node2);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node1);
  TEST_ASSERT_EQUAL_NODE(NULL, &node6, 'b', &node5);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node6);
} 

/**
 *        root                             root
 *         |                                |
 *         v                                v
 *        2(b)           remove 6          2(b)
 *       /   \         ------------->     /   \
 *     1(b)   5(r)                      1(b)   5(b)
 *           /   \                            /
 *         3(b)  6(b)                       3(r)   
 */
void test_delRedBlackTree_remove_6_from_tree_with_2_1_5_3_6_nodes(void)
{
  setNode(&node1, NULL, NULL, 'b');
  setNode(&node3, NULL, NULL, 'b');
  setNode(&node6, NULL, NULL, 'b');
  setNode(&node5, &node3, &node6, 'r');
  setNode(&node2, &node1, &node5, 'b');
  Node *root = &node2;
  
  delRedBlackTree(&root, &node6);
  
  TEST_ASSERT_EQUAL_PTR(root, &node2);
  TEST_ASSERT_EQUAL_NODE(&node1, &node5, 'b', &node2);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node1);
  TEST_ASSERT_EQUAL_NODE(&node3, NULL, 'b', &node5);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node3);
} 

/**
 *         root                              root
 *          |                                 |
 *          v                                 v
 *         5(b)          remove 6            2(b)
 *        /    \       ------------>        /    \
 *      2(r)   6(b)                      1(b)    5(b)
 *     /   \                                     /
 *  1(b)   3(b)                                3(r)
 */
void test_delRedBlackTree_remove_6_from_tree_with_1_2_3_5_6_nodes(void)
{
  setNode(&node1, NULL, NULL, 'b');
  setNode(&node3, NULL, NULL, 'b');
  setNode(&node6, NULL, NULL, 'b');
  setNode(&node2, &node1, &node3, 'r');
  setNode(&node5, &node2, &node6, 'b');
  Node *root = &node5;
  
  delRedBlackTree(&root, &node6);
  
  TEST_ASSERT_EQUAL_PTR(root, &node2);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node1);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node3);
  TEST_ASSERT_EQUAL_NODE(&node3, NULL, 'b', &node5);
  TEST_ASSERT_EQUAL_NODE(&node1, &node5, 'b', &node2);
}

/**
 *         root                              root
 *          |                                 |
 *          v                                 v
 *         5(b)          remove 1            5(b)
 *        /    \       ------------>        /    \
 *      2(r)   6(b)                      2(b)    6(b)
 *     /   \                                \      
 *  1(b)   3(b)                             3(r)  
 */
void test_delRedBlackTree_remove_1_from_tree_with_1_2_3_5_6_nodes(void)
{
  setNode(&node1, NULL, NULL, 'b');
  setNode(&node3, NULL, NULL, 'b');
  setNode(&node6, NULL, NULL, 'b');
  setNode(&node2, &node1, &node3, 'r');
  setNode(&node5, &node2, &node6, 'b');
  Node *root = &node5;
  
  delRedBlackTree(&root, &node1);
  
  TEST_ASSERT_EQUAL_PTR(root, &node5);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node6);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node3);
  TEST_ASSERT_EQUAL_NODE(NULL, &node3, 'b', &node2);
  TEST_ASSERT_EQUAL_NODE(&node2, &node6, 'b', &node5);
}

/**
 *         root                              root
 *          |                                 |
 *          v                                 v
 *         5(b)          remove 3            5(b)
 *        /    \       ------------>        /    \
 *      2(r)   6(b)                      2(b)    6(b)
 *     /   \                            /      
 *  1(b)   3(b)                       1(r)     
 */
void test_delRedBlackTree_remove_3_from_tree_with_1_2_3_5_6_nodes(void)
{
  setNode(&node1, NULL, NULL, 'b');
  setNode(&node3, NULL, NULL, 'b');
  setNode(&node6, NULL, NULL, 'b');
  setNode(&node2, &node1, &node3, 'r');
  setNode(&node5, &node2, &node6, 'b');
  Node *root = &node5;
  
  delRedBlackTree(&root, &node3);
  
  TEST_ASSERT_EQUAL_PTR(root, &node5);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node6);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node1);
  TEST_ASSERT_EQUAL_NODE(&node1, NULL, 'b', &node2);
  TEST_ASSERT_EQUAL_NODE(&node2, &node6, 'b', &node5);
}

/**
 *           root                                 root 
 *            |                                    |
 *            v                                    v
 *           4(b)                                 4(b)
 *         /     \           remove 1           /     \
 *       2(r)     6(r)     ----------->       2(b)    6(r)
 *      /   \    /   \                           \    /   \
 *    1(b) 3(b) 5(b) 7(b)                       3(r) 5(b)  7(b)
 */
void test_delRedBlackTree_remove_1_from_tree_with_4_2_1_3_6_5_7_nodes(void)
{
  setNode(&node1, NULL, NULL, 'b');
  setNode(&node3, NULL, NULL, 'b');
  setNode(&node5, NULL, NULL, 'b');
  setNode(&node7, NULL, NULL, 'b');
  setNode(&node2, &node1, &node3, 'r');
  setNode(&node6, &node5, &node7, 'r');
  setNode(&node4, &node2, &node6, 'b');
  Node *root = &node4;
  
  delRedBlackTree(&root, &node1);
  
  TEST_ASSERT_EQUAL_PTR(root, &node4);
  TEST_ASSERT_EQUAL_NODE(NULL, &node3, 'b', &node2);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node3);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node5);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node7);
  TEST_ASSERT_EQUAL_NODE(&node5, &node7, 'r', &node6);
  TEST_ASSERT_EQUAL_NODE(&node2, &node6, 'b', &node4);
}

/**
 *           root                                 root 
 *            |                                    |
 *            v                                    v
 *           4(b)                                 4(b)
 *         /     \           remove 3           /     \
 *       2(r)     6(r)     ----------->       2(b)    6(r)
 *      /   \    /   \                       /       /   \
 *    1(b) 3(b) 5(b) 7(b)                  1(r)    5(b)  7(b)
 */
void test_delRedBlackTree_remove_3_from_tree_with_4_2_1_3_6_5_7_nodes(void) 
{
  setNode(&node1, NULL, NULL, 'b');
  setNode(&node3, NULL, NULL, 'b');
  setNode(&node5, NULL, NULL, 'b');
  setNode(&node7, NULL, NULL, 'b');
  setNode(&node2, &node1, &node3, 'r');
  setNode(&node6, &node5, &node7, 'r');
  setNode(&node4, &node2, &node6, 'b');
  Node *root = &node4;
  
  delRedBlackTree(&root, &node3);
  
  TEST_ASSERT_EQUAL_PTR(root, &node4);
  TEST_ASSERT_EQUAL_NODE(&node1, NULL, 'b', &node2);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node1);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node5);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node7);
  TEST_ASSERT_EQUAL_NODE(&node5, &node7, 'r', &node6);
  TEST_ASSERT_EQUAL_NODE(&node2, &node6, 'b', &node4);
}

/**
 *           root                                 root 
 *            |                                    |
 *            v                                    v
 *           4(b)                                 4(b)
 *         /     \           remove 5           /     \
 *       2(r)     6(r)     ----------->       2(r)    6(b)
 *      /   \    /   \                       /   \       \
 *    1(b) 3(b) 5(b) 7(b)                  1(b) 3(b)     7(r)
 */
void test_delRedBlackTree_remove_5_from_tree_with_4_2_1_3_6_5_7_nodes(void) 
{
  setNode(&node1, NULL, NULL, 'b');
  setNode(&node3, NULL, NULL, 'b');
  setNode(&node5, NULL, NULL, 'b');
  setNode(&node7, NULL, NULL, 'b');
  setNode(&node2, &node1, &node3, 'r');
  setNode(&node6, &node5, &node7, 'r');
  setNode(&node4, &node2, &node6, 'b');
  Node *root = &node4;
  
  delRedBlackTree(&root, &node5);
  
  TEST_ASSERT_EQUAL_PTR(root, &node4);
  TEST_ASSERT_EQUAL_NODE(&node1, &node3, 'r', &node2);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node7);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node1);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node3);
  TEST_ASSERT_EQUAL_NODE(NULL, &node7, 'b', &node6);
  TEST_ASSERT_EQUAL_NODE(&node2, &node6, 'b', &node4);
}

/**
 *           root                                 root 
 *            |                                    |
 *            v                                    v
 *           4(b)                                 4(b)
 *         /     \           remove 7           /      \
 *       2(r)     6(r)     ----------->       2(r)     6(b)
 *      /   \    /   \                       /   \    /  
 *    1(b) 3(b) 5(b) 7(b)                  1(b) 3(b) 5(r)    
 */
void test_delRedBlackTree_remove_7_from_tree_with_4_2_1_3_6_5_7_nodes(void) 
{
  setNode(&node1, NULL, NULL, 'b');
  setNode(&node3, NULL, NULL, 'b');
  setNode(&node5, NULL, NULL, 'b');
  setNode(&node7, NULL, NULL, 'b');
  setNode(&node2, &node1, &node3, 'r');
  setNode(&node6, &node5, &node7, 'r');
  setNode(&node4, &node2, &node6, 'b');
  Node *root = &node4;
  
  delRedBlackTree(&root, &node7);
  
  TEST_ASSERT_EQUAL_PTR(root, &node4);
  TEST_ASSERT_EQUAL_NODE(&node1, &node3, 'r', &node2);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node5);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node1);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node3);
  TEST_ASSERT_EQUAL_NODE(&node5, NULL, 'b', &node6);
  TEST_ASSERT_EQUAL_NODE(&node2, &node6, 'b', &node4);
}

/**
 *         parent                       parent
 *           |         successor          \\
 *           v             2               v
 *         2(b)      ------------>         -
 *        /   \
 *       -     - 
 *
 */
void test_removeNextLargerSuccessor_remove_2_from_the_tree_with_2_node(void)
{
  setNode(&node2, NULL, NULL, 'b');
  Node *parent = &node2;
  Node *removeNode;
  
  removeNode = removeNextLargerSuccessor(&parent);
  TEST_ASSERT_NULL(parent);
  TEST_ASSERT_EQUAL(1, isDoubleBlack(&parent, removeNode));
}

/**
 *       parent                         parent
 *         |                              |
 *         v         successor            v
 *       2(b)           1               2(b)
 *      /         ------------>
 *   1(r)
 */
void test_removeNextLargerSuccessor_remove_1_from_the_tree_with_2_1_nodes(void)
{
  setNode(&node1, NULL, NULL, 'r');
  setNode(&node2, &node1, NULL, 'b');
  Node *parent = &node2;
  Node *removeNode;
  
  removeNode = removeNextLargerSuccessor(&parent);
  TEST_ASSERT_EQUAL_PTR(&node1, removeNode);
  TEST_ASSERT_EQUAL_PTR(parent, &node2);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node2);
}

/**
 *       parent                         parent
 *         |                              |
 *         v          successor           v
 *       2(b)             2             3(b)
 *           \      -------------->
 *           3(r)
 */
void test_removeNextLargerSuccessor_remove_3_from_the_tree_with_2_3_nodes(void)
{
  setNode(&node3, NULL, NULL, 'r');
  setNode(&node2, NULL, &node3, 'b');
  Node *parent = &node2;
  Node *removeNode;
  
  removeNode = removeNextLargerSuccessor(&parent);
  TEST_ASSERT_EQUAL_PTR(&node2, removeNode);
  TEST_ASSERT_EQUAL_PTR(parent, &node3);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node3);
}

/**
 *       parent                            parent
 *         |             successor           |
 *         v                 1               v
 *        2(b)         ------------>       2(b)
 *       /   \                                \  
 *     1(r)  3(r)                             3(r)
 */
void test_removeNextLargerSuccessor_remove_3_from_the_tree_with_2_1_3_nodes(void)
{
  setNode(&node1, NULL, NULL, 'r');
  setNode(&node3, NULL, NULL, 'r');
  setNode(&node2, &node1, &node3, 'b');
  Node *parent = &node2;
  Node *removeNode;
  
  removeNode = removeNextLargerSuccessor(&parent);
  TEST_ASSERT_EQUAL_PTR(&node1, removeNode);
  TEST_ASSERT_EQUAL_PTR(parent, &node2);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node3);
  TEST_ASSERT_EQUAL_NODE(NULL, &node3, 'b', &node2);
}

/**
 *      parent                          parent
 *        |                               |
 *        v                               v
 *      12(b)          successor        12(b)
 *     /    \              1           /    \
 *   5(b)    18(b)    ---------->    5(b)   18(b)
 *  /   \    /   \                  /   \   /   \
 * 1(r)  - 13(r)  -                -    - 13(r)  -
 */
void test_removeNextLargerSuccessor_remove_1_from_the_tree_with_1_5_12_13_18_nodes(void)
{
  setNode(&node1, NULL, NULL, 'r');
  setNode(&node13, NULL, NULL, 'r');
  setNode(&node5, &node1, NULL, 'b');
  setNode(&node18, &node13, NULL, 'b');
  setNode(&node12, &node5, &node18, 'b');
  Node *parent = &node12;
  Node *removeNode;
  
  removeNode = removeNextLargerSuccessor(&parent);
  TEST_ASSERT_EQUAL_PTR(&node1, removeNode);
  TEST_ASSERT_EQUAL_PTR(parent, &node12);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node13);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node5);
  TEST_ASSERT_EQUAL_NODE(&node13, NULL, 'b', &node18);
  TEST_ASSERT_EQUAL_NODE(&node5, &node18, 'b', &node12);
}