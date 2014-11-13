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

void test_isRed_given_a_node_with_red_color_should_return_1(void) 
{
  int result;
  setNode(&node1, NULL, NULL, 'r');
  Node *root = &node1;
  
  result = isRed(&root);
  TEST_ASSERT_EQUAL(1, result);
}

void test_isRed_given_a_node_with_black_color_should_return_0(void) 
{
  int result;
  setNode(&node1, NULL, NULL, 'b');
  Node *root = &node1;
  
  result = isRed(&root);
  TEST_ASSERT_EQUAL(0, result);
}

void test_isBlack_given_a_node_with_black_color_should_return_1(void)
{
  int result;
  setNode(&node2, NULL, NULL, 'b');
  Node *root = &node2;
  
  result = isBlack(&root);
  TEST_ASSERT_EQUAL(1, result);
}

void test_isBlack_given_a_node_with_red_color_should_return_0(void)
{
  int result;
  setNode(&node2, NULL, NULL, 'r');
  Node *root = &node2;
  
  result = isBlack(&root);
  TEST_ASSERT_EQUAL(0, result);
}

void test_isDoubleBlack_given_a_node_with_double_black_color_should_return_1(void)
{
  int result;
  setNode(&node4, NULL, NULL, 'd');
  Node *root = &node4;
  
  result = isDoubleBlack(&root);
  TEST_ASSERT_EQUAL(1, result);
}

void test_isDoubleBlack_given_a_node_with_black_color_should_return_0(void)
{
  int result;
  setNode(&node4, NULL, NULL, 'b');
  Node *root = &node4;
  
  result = isDoubleBlack(&root);
  TEST_ASSERT_EQUAL(0, result);
}
  
/**
 *          root                         root                     root
 *           |                            |                        |
 *           v                            v        left            v
 *          2(b)          remove 1       2(b)     rotate          4(b)
 *         /   \        ------------>      \     --------->      /   \
 *      1(b)   4(b)                        4(b)               2(b)    5(b)
 *                \                          \
 *                5(r)                       5(r)
 */
void test_delRedBlackTree_remove_1_from_tree_with_1_2_4_5_nodes(void)
{
  setNode(&node1, NULL, NULL, 'b');
  setNode(&node5, NULL, NULL, 'r');
  setNode(&node4, NULL, &node5, 'b');
  setNode(&node2, &node1, &node4, 'b');
  Node *root = &node2;
  Node *result;
  
  result = _delRedBlackTree(&root, &node1);
  
  TEST_ASSERT_EQUAL_PTR(result, &node1);
  TEST_ASSERT_EQUAL_PTR(root, &node4);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node2);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node5);
  TEST_ASSERT_EQUAL_NODE(&node2, &node5, 'b', &node4);
}

/**
 *          root                         root                     root
 *           |                            |        right           |
 *           v                            v        left            v
 *          2(b)          remove 1       2(b)     rotate          4(b)
 *         /   \        ------------>      \     --------->      /   \
 *      1(b)   5(b)                        5(b)               2(b)    5(b)
 *            /                           /  
 *          4(r)                        4(r)    
 */
void test_delRedBlackTree_remove_one_from_tree_with_1_2_4_5_nodes_with_using_right_left_rotation(void)
{
  setNode(&node1, NULL, NULL, 'b');
  setNode(&node4, NULL, NULL, 'r');
  setNode(&node5, &node4, NULL, 'b');
  setNode(&node2, &node1, &node5, 'b');
  Node *root = &node2;
  Node *result;
  
  result = _delRedBlackTree(&root, &node1);
  
  TEST_ASSERT_EQUAL(result, &node1);
  TEST_ASSERT_EQUAL_PTR(root, &node4);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node2);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node5);
  TEST_ASSERT_EQUAL_NODE(&node2, &node5, 'b', &node4);
} 

/**
 *         root                          root                        root         
 *          |                             |                           |
 *          v                             v                           v
 *         4(b)                          4(b)         right         2(b)
 *        /   \         remove 5         /            rotate       /    \
 *      2(b)   5(b)   ------------>   2(b)          --------->   1(b)   4(b)
 *     /                              /
 *   1(r)                           1(r)
 */
void test__delRedBlackTree_remove_5_from_tree_with_1_2_4_5_nodes(void)
{
  setNode(&node1, NULL, NULL, 'r');
  setNode(&node5, NULL, NULL, 'b');
  setNode(&node2, &node1, NULL, 'b');
  setNode(&node4, &node2, &node5, 'b');
  Node *root = &node4;
  Node *result;
  
  result = _delRedBlackTree(&root, &node5);
  
  TEST_ASSERT_EQUAL_PTR(result, &node5);
  TEST_ASSERT_EQUAL_PTR(root, &node2);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node1);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node4);
  TEST_ASSERT_EQUAL_NODE(&node1, &node4, 'b', &node2);
}

/**
 *         root                             root                        root         
 *          |                                |                           |
 *          v                                v          left             v
 *         4(b)                            4(b)         right           3(b)
 *        /   \         remove 5           /           rotate          /   \
 *      2(b)   5(b)  ------------->     2(b)         ------------>   2(b)  4(b)
 *         \                               \
 *         3(r)                            3(r)
 */
void test__delRedBlackTree_remove_five_from_tree_with_1_2_4_5_nodes_with_using_left_right_rotate(void)
{
  setNode(&node3, NULL, NULL, 'r');
  setNode(&node5, NULL, NULL, 'b');
  setNode(&node2, NULL, &node3, 'b');
  setNode(&node4, &node2, &node5, 'b');
  Node *root = &node4;
  Node *result;
  
  result = _delRedBlackTree(&root, &node5);
  
  TEST_ASSERT_EQUAL_PTR(result, &node5);
  TEST_ASSERT_EQUAL_PTR(root, &node3);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node2);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node4);
  TEST_ASSERT_EQUAL_NODE(&node2, &node4, 'b', &node3);
}

/**
 *        root                              root
 *         |                                 |
 *         v                                 v
 *        2(b)         remove 1            2(d)
 *       /   \       ------------>            \
 *     1(b)  3(b)                             3(r)
 */
void test__delRedBlackTree_remove_1_from_tree_with_1_2_3_nodes(void)
{
  setNode(&node1, NULL, NULL, 'b');
  setNode(&node3, NULL, NULL, 'b');
  setNode(&node2, &node1, &node3, 'b');
  Node *root = &node2;
  Node *result;
  
  result = _delRedBlackTree(&root, &node1);
  
  TEST_ASSERT_EQUAL_PTR(root, &node2);
  TEST_ASSERT_EQUAL_PTR(result, &node1);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node3);
  TEST_ASSERT_EQUAL_NODE(NULL, &node3, 'd', &node2);
}

/**
 *        root                              root
 *         |                                 |
 *         v                                 v
 *        2(b)         remove 3            2(d)
 *       /   \       ------------>        /    
 *     1(b)  3(b)                       1(r)     
 */
void test__delRedBlackTree_remove_3_from_tree_with_1_2_3_nodes(void)
{
  setNode(&node1, NULL, NULL, 'b');
  setNode(&node3, NULL, NULL, 'b');
  setNode(&node2, &node1, &node3, 'b');
  Node *root = &node2;
  Node *result;
  
  result = _delRedBlackTree(&root, &node3);
    
  TEST_ASSERT_EQUAL_PTR(root, &node2);
  TEST_ASSERT_EQUAL_PTR(result, &node3);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node1);
  TEST_ASSERT_EQUAL_NODE(&node1, NULL, 'd', &node2);
}

/**
 *        root                              root
 *         |                                 |
 *         v                                 v
 *        2(r)         remove 3            2(b)
 *       /   \       ------------>        /    
 *     1(b)  3(b)                       1(r)     
 */
void test__delRedBlackTree_remove_three_from_tree_with_1_2_3_nodes(void)
{
  setNode(&node1, NULL, NULL, 'b');
  setNode(&node3, NULL, NULL, 'b');
  setNode(&node2, &node1, &node3, 'r');
  Node *root = &node2;
  Node *result;
  
  result = _delRedBlackTree(&root, &node3);
    
  TEST_ASSERT_EQUAL_PTR(root, &node2);
  TEST_ASSERT_EQUAL_PTR(result, &node3);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node1);
  TEST_ASSERT_EQUAL_NODE(&node1, NULL, 'b', &node2);
}

/**
 *        root                              root
 *         |                                 |
 *         v                                 v
 *        2(b)         remove 1            2(b)
 *       /   \       ------------>            \
 *     1(b)  3(b)                             3(r)
 */
void test__delRedBlackTree_remove_one_from_tree_with_1_2_3_nodes(void)
{
  setNode(&node1, NULL, NULL, 'b');
  setNode(&node3, NULL, NULL, 'b');
  setNode(&node2, &node1, &node3, 'r');
  Node *root = &node2;
  Node *result;
  
  result = _delRedBlackTree(&root, &node1);
  
  TEST_ASSERT_EQUAL_PTR(root, &node2);
  TEST_ASSERT_EQUAL_PTR(result, &node1);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node3);
  TEST_ASSERT_EQUAL_NODE(NULL, &node3, 'b', &node2);
}

/**
 *       root                           root                            root
 *        |                              |                               |
 *        v                              v                               v
 *      2(b)                            2(b)            left            4(b)
 *     /   \          remove 1             \           rotate          /    \
 *   1(b)  4(r)      ----------->          4(r)      ------------>   2(b)   5(b)
 *        /   \                           /   \                         \
 *      3(b)  5(b)                      3(b)  5(b)                      3(r)
 */
void test__delRedBlackTree_remove_1_from_tree_with_1_2_3_4_5_nodes(void)
{
  setNode(&node1, NULL, NULL, 'b');
  setNode(&node3, NULL, NULL, 'b');
  setNode(&node5, NULL, NULL, 'b');
  setNode(&node4, &node3, &node5, 'r');
  setNode(&node2, &node1, &node4, 'b');
  Node *root = &node2;
  Node *result;
  
  result = _delRedBlackTree(&root, &node1);
  
  TEST_ASSERT_EQUAL_PTR(root, &node4);
  TEST_ASSERT_EQUAL_PTR(result, &node1);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node5);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node3);
  TEST_ASSERT_EQUAL_NODE(NULL, &node3, 'b', &node2);
  TEST_ASSERT_EQUAL_NODE(&node2, &node5, 'b', &node4);
}

/**
 *         root                         root                        root
 *          |                            |                           |
 *          v                            v                           v
 *         5(b)                         5(b)      rotate           3(b)
 *        /   \        remove 6        /           right          /   \
 *      3(r)  6(b)  ---------------> 3(r)      -------------->  2(b)  5(b)
 *     /   \                        /   \                            /
 *  2(b)   4(b)                   2(b)  4(b)                       4(r)
 */
void test__delRedBlackTree_remove_6_from_tree_with_2_3_4_5_6_nodes(void)
{
  setNode(&node2, NULL, NULL, 'b');
  setNode(&node4, NULL, NULL, 'b');
  setNode(&node6, NULL, NULL, 'b');
  setNode(&node3, &node2, &node4, 'r');
  setNode(&node5, &node3, &node6, 'b');
  Node *root = &node5;
  Node *result;
  
  result = _delRedBlackTree(&root, &node6);
  
  TEST_ASSERT_EQUAL_PTR(root, &node3);
  TEST_ASSERT_EQUAL_PTR(result, &node6);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node4);
  TEST_ASSERT_EQUAL_NODE(&node4, NULL, 'b', &node5);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node2);
  TEST_ASSERT_EQUAL_NODE(&node2, &node5, 'b', &node3);
}

/**
 *        root                             root                              root                          root             
 *         |                                |                                 |                             |
 *         v                                v                                 v                             v
 *        2(b)                             2(b)                              5(b)                         5(b)
 *       /   \           remove 1        //   \          case 3             /   \       case 1           /   \
 *     1(b)  5(r)      ------------>         5(r)     -------------->    2(r)   6(b)  ------------>    3(r)   6(b)
 *          /   \                           /   \                      //   \                         /   \
 *        3(b)  6(b)                      3(b)  6(b)                       3(b)                     2(b)  4(b)
 *           \                               \                                \
 *          4(r)                            4(r)                              4(r)
 */
void test__delRedBlackTree_remove_1_from_tree_with_1_2_3_4_5_6_nodes_by_using_case_3_and_1(void)
{
  setNode(&node4, NULL, NULL, 'r');
  setNode(&node6, NULL, NULL, 'b');
  setNode(&node1, NULL, NULL, 'b');
  setNode(&node3, NULL, &node4, 'b');
  setNode(&node5, &node3, &node6, 'r');
  setNode(&node2, &node1, &node5, 'b');
  Node *root = &node2;
  Node *result;
  
  result = _delRedBlackTree(&root, &node1);
  
  TEST_ASSERT_EQUAL_PTR(root, &node5);
  TEST_ASSERT_EQUAL_PTR(result, &node1);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node2);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node4);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node6);
  TEST_ASSERT_EQUAL_NODE(&node2, &node4, 'r', &node3);
  TEST_ASSERT_EQUAL_NODE(&node3, &node6, 'b', &node5);
}

/* 
 * 
 *           root                 root                      root
 *            |       remove 20    |       rotate left       |  
 *            v      ----->        v      --------->         v
 *           15(b)                15(b)                     5(b)
 *          /  \                /   \\                    /   \
 *       5(r)   20(b)        5(r)   NULL               2(b)   15(b)
 *      /  \                /   \                            /
 *   2(b)  7(b)           2(b)  7(b)                       7(r)
 */
void test_delRedBlackTree_3_node_remove_20_from_tree_with_root_15_root_should_point_to_5()
{
   
    setNode(&node2, NULL, NULL, 'b');
    setNode(&node7, NULL, NULL, 'b');
    setNode(&node20, NULL, NULL, 'b');
    setNode(&node5, &node2, &node7, 'r');
    setNode(&node15, &node5, &node20, 'b');
    Node *root = &node15;
    Node *node;
    
    
    node = delRedBlackTree(&root, &node20);  
    TEST_ASSERT_EQUAL(20 , node->data);
    TEST_ASSERT_EQUAL_NODE(NULL , NULL, 'b', &node2);
    TEST_ASSERT_EQUAL_NODE(NULL , NULL, 'r', &node7);
    TEST_ASSERT_EQUAL(root->data,5);
    TEST_ASSERT_EQUAL_NODE(&node7, NULL, 'b', &node15);
    TEST_ASSERT_EQUAL_NODE(&node2, &node15 , 'b', &node5);
    
}





/* 
 * 
 *           root                 root                      root                      root
 *            |    remove 20       |      case3              |         case1           |
 *            v      ----->        v      --------->         v         ------->        v
 *           15(b)                15(b)                     5(b)                      5(b)
 *          /  \                /   \\                    /   \                     /    \
 *       5(r)   20(b)        5(r)   NULL               2(b)   15(r)               2(b)   7(r)
 *      /  \                /   \                            /                          /   \
 *   2(b)  7(b)           2(b)  7(b)                       7(b)                      6(b)   15(b)
 *        /                    /                          /
 *      6(r)                 6(r)                       6(r)
 *
 */
void test_delRedBlackTree_3_node_combination_test_remove_20_from_tree_with_root_15_root_should_point_to_5()
{
    
    setNode(&node2, NULL, NULL, 'b');
    setNode(&node6, NULL, NULL, 'r');
    setNode(&node7, &node6, NULL, 'b');
    setNode(&node20, NULL, NULL, 'b');
    setNode(&node5, &node2, &node7, 'r');
    setNode(&node15, &node5, &node20, 'b');
    Node *root = &node15;
    Node *node;
   
    node = delRedBlackTree(&root, &node20);  
    TEST_ASSERT_EQUAL(20 , node->data);
    TEST_ASSERT_EQUAL(root->data,5);
    TEST_ASSERT_EQUAL_NODE(NULL , NULL, 'b', &node6);
    TEST_ASSERT_EQUAL_NODE(&node6, &node15, 'r', &node7);
    TEST_ASSERT_EQUAL_NODE(&node2, &node7 , 'b', &node5);
    TEST_ASSERT_EQUAL_NODE(NULL , NULL, 'b', &node2);
        
    TEST_ASSERT_EQUAL_NODE(NULL , NULL, 'b', &node15);
}