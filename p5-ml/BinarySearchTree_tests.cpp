// Project UID db1f506d06d84ab787baf250c265e24e

#include "BinarySearchTree.h"
#include "unit_test_framework.h"
using namespace std;

TEST(test_stub) {
    // Add your tests here
    ASSERT_TRUE(true);
}

TEST(bst_public_test) {
  BinarySearchTree<int> tree;

  tree.insert(5);

  ASSERT_TRUE(tree.size() == 1);
  ASSERT_TRUE(tree.height() == 1);

  ASSERT_TRUE(tree.find(5) != tree.end());

  tree.insert(7);
  tree.insert(3);

  ASSERT_TRUE(tree.check_sorting_invariant());
  ASSERT_TRUE(*tree.max_element() == 7);
  ASSERT_TRUE(*tree.min_element() == 3);
  ASSERT_TRUE(*tree.min_greater_than(5) == 7);

  cout << "cout << tree.to_string()" << endl;
  cout << tree.to_string() << endl << endl;

  cout << "cout << tree" << endl << "(uses iterators)" << endl;
  cout << tree << endl << endl;

  ostringstream oss_preorder;
  tree.traverse_preorder(oss_preorder);
  cout << "preorder" << endl;
  cout << oss_preorder.str() << endl << endl;
  ASSERT_TRUE(oss_preorder.str() == "5 3 7 ");

  ostringstream oss_inorder;
  tree.traverse_inorder(oss_inorder);
  cout << "inorder" << endl;
  cout << oss_inorder.str() << endl << endl;
  ASSERT_TRUE(oss_inorder.str() == "3 5 7 ");
}

TEST(base_struct_test) {
    BinarySearchTree<int> tree;
    ASSERT_TRUE(tree.empty());
    ASSERT_EQUAL(tree.size(), 0);
    ASSERT_EQUAL(tree.height(), 0);
    tree.insert(12);
    ASSERT_FALSE(tree.empty());
    ASSERT_EQUAL(tree.size(), 1);
    ASSERT_EQUAL(tree.height(), 1);
    tree.insert(7);
    ASSERT_EQUAL(tree.size(), 2);
    ASSERT_EQUAL(tree.height(), 2);
    tree.insert(3);
    ASSERT_EQUAL(tree.size(), 3);
    ASSERT_EQUAL(tree.height(), 3);
    tree.insert(8);
    ASSERT_EQUAL(tree.size(), 4);
    ASSERT_EQUAL(tree.height(), 3);
    tree.insert(15);
    ASSERT_EQUAL(tree.size(), 5);
    ASSERT_EQUAL(tree.height(), 3);
    tree.insert(13);
    ASSERT_EQUAL(tree.size(), 6);
    ASSERT_EQUAL(tree.height(), 3);
    tree.insert(19);
    ASSERT_EQUAL(tree.size(), 7);
    ASSERT_EQUAL(tree.height(), 3);
}


TEST(test_insert) {
    BinarySearchTree<int> tree;
    ASSERT_EQUAL(*tree.insert(12), 12);
    tree.insert(7);
    ASSERT_EQUAL(2,tree.size());
}

TEST(find) {
    BinarySearchTree<int> tree;
    ASSERT_EQUAL(tree.find(12), tree.end());
    tree.insert(12);
    ASSERT_EQUAL(*tree.find(12), 12);
    ASSERT_EQUAL(tree.find(12), tree.begin());
    ASSERT_EQUAL(tree.find(7), tree.end());
    tree.insert(7);
    ASSERT_EQUAL(tree.find(7), tree.begin());
    ASSERT_EQUAL(tree.find(12), ++tree.begin());
    tree.insert(3);
    ASSERT_EQUAL(tree.find(3), tree.begin());
    ASSERT_EQUAL(tree.find(7), ++tree.begin());
    ASSERT_EQUAL(tree.find(12), ++++tree.begin());
    tree.insert(8);
    tree.insert(15);
    tree.insert(13);
    tree.insert(19);
    ASSERT_EQUAL(tree.find(3), tree.begin());
    ASSERT_EQUAL(tree.find(7), ++tree.begin());
    ASSERT_EQUAL(tree.find(12), ++++++tree.begin());
}

TEST(copy) {
    BinarySearchTree<int> tree;
    tree.insert(12);
    tree.insert(7);
    tree.insert(3);
    tree.insert(4);
    tree.insert(15);
    tree.insert(13);
    tree.insert(14);

    BinarySearchTree<int> copy(tree);
    ASSERT_FALSE(copy.empty());
    ASSERT_EQUAL(copy.find(3), copy.begin());
    ASSERT_EQUAL(copy.find(4), ++copy.begin());
    ASSERT_EQUAL(copy.find(7), ++++copy.begin());
    ASSERT_EQUAL(copy.find(12), ++++++copy.begin());
}

TEST(assign) {
    BinarySearchTree<int> tree;
    tree.insert(4);
    tree.insert(7);
    tree.insert(2);
    tree.insert(3);
    tree.insert(5);
    tree.insert(1);
    tree.insert(6);

    BinarySearchTree<int> copy(tree);

    BinarySearchTree<int> assign;
    assign.insert(9);
    assign.insert(10);
    assign.insert(8);
    assign = tree;

    ASSERT_FALSE(copy.empty());
    int leaf = 1;
    auto item1 = tree.begin();
    auto item2 = copy.begin();
    auto item3 = assign.begin();
    
    while (item1 != tree.end()) {
        ASSERT_EQUAL(*item1++, leaf);
        ASSERT_EQUAL(*item2++, leaf);
        ASSERT_EQUAL(*item3++, leaf);
        leaf += 1;
    }
    ASSERT_EQUAL(leaf, 8);
}

TEST(test_min_max) {
    BinarySearchTree<int> tree;
    tree.insert(12);
    ASSERT_EQUAL(*tree.max_element(), 12);
    ASSERT_EQUAL(*tree.min_element(), 12);
    tree.insert(7);
    tree.insert(3);
    ASSERT_EQUAL(*tree.max_element(), 12);
    ASSERT_EQUAL(*tree.min_element(), 3);
    tree.insert(8);
    tree.insert(15);
    tree.insert(13);
    tree.insert(19);
    ASSERT_EQUAL(*tree.max_element(), 19);
    ASSERT_EQUAL(*tree.min_element(), 3);
}

TEST(check_sorting_invariant_impl) {
    BinarySearchTree<int> tree;
    BinarySearchTree<int>::Iterator i;
    ASSERT_TRUE(tree.check_sorting_invariant());
    tree.insert(12);
    ASSERT_TRUE(tree.check_sorting_invariant());
    tree.insert(7);
    tree.insert(3);
    tree.insert(8);
    tree.insert(15);
    tree.insert(13);
    tree.insert(19);
    ASSERT_TRUE(tree.check_sorting_invariant());
    i = tree.find(8);
    *i = 14;
    ASSERT_FALSE(tree.check_sorting_invariant());
    *i = 8;
    ASSERT_TRUE(tree.check_sorting_invariant());
    *i = 2;
    ASSERT_FALSE(tree.check_sorting_invariant());
    *i = 8;
    ASSERT_TRUE(tree.check_sorting_invariant());
    i = tree.find(13);
    *i = 10;
    ASSERT_FALSE(tree.check_sorting_invariant());
    *i = 13;
    ASSERT_TRUE(tree.check_sorting_invariant());
    *i = 16;
    ASSERT_FALSE(tree.check_sorting_invariant());
    *i = 13;
    ASSERT_TRUE(tree.check_sorting_invariant());
    i = tree.find(7);
    *i = 2;
    ASSERT_FALSE(tree.check_sorting_invariant());
    *i = 7;
    ASSERT_TRUE(tree.check_sorting_invariant());
    *i = 12;
    ASSERT_FALSE(tree.check_sorting_invariant());
    *i = 7;
    ASSERT_TRUE(tree.check_sorting_invariant());
    i = tree.find(12);
    *i = 2;
    ASSERT_FALSE(tree.check_sorting_invariant());
    *i = 12;
    ASSERT_TRUE(tree.check_sorting_invariant());
    *i = 16;
    ASSERT_FALSE(tree.check_sorting_invariant());
    
    
    
}

TEST(traverse_inorder_impl) {
    BinarySearchTree<int> tree;
    std::ostringstream os;
    tree.traverse_inorder(os);
    ASSERT_EQUAL(os.str(), "");
    tree.insert(12);
    tree.traverse_inorder(os);
    ASSERT_EQUAL(os.str(), "12 ");
    tree.insert(7);
    os.str("");
    tree.traverse_inorder(os);
    ASSERT_EQUAL(os.str(), "7 12 ");
    tree.insert(3);
    os.str("");
    tree.traverse_inorder(os);
    ASSERT_EQUAL(os.str(), "3 7 12 ");
    tree.insert(8);
    os.str("");
    tree.traverse_inorder(os);
    ASSERT_EQUAL(os.str(), "3 7 8 12 ");
    tree.insert(15);
    os.str("");
    tree.traverse_inorder(os);
    ASSERT_EQUAL(os.str(), "3 7 8 12 15 ");
    tree.insert(13);
    os.str("");
    tree.traverse_inorder(os);
    ASSERT_EQUAL(os.str(), "3 7 8 12 13 15 ");
    tree.insert(19);
    os.str("");
    tree.traverse_inorder(os);
    ASSERT_EQUAL(os.str(), "3 7 8 12 13 15 19 ");
}

TEST(raverse_preorder_impl) {
    BinarySearchTree<int> tree;
    std::ostringstream os;
    tree.traverse_preorder(os);
    ASSERT_EQUAL(os.str(), "");
    tree.insert(12);
    tree.traverse_preorder(os);
    ASSERT_EQUAL(os.str(), "12 ");
    tree.insert(7);
    os.str("");
    tree.traverse_preorder(os);
    ASSERT_EQUAL(os.str(), "12 7 ");
    tree.insert(3);
    os.str("");
    tree.traverse_preorder(os);
    ASSERT_EQUAL(os.str(), "12 7 3 ");
    tree.insert(8);
    os.str("");
    tree.traverse_preorder(os);
    ASSERT_EQUAL(os.str(), "12 7 3 8 ");
    tree.insert(15);
    os.str("");
    tree.traverse_preorder(os);
    ASSERT_EQUAL(os.str(), "12 7 3 8 15 ");
    tree.insert(13);
    os.str("");
    tree.traverse_preorder(os);
    ASSERT_EQUAL(os.str(), "12 7 3 8 15 13 ");
    tree.insert(19);
    os.str("");
    tree.traverse_preorder(os);
    ASSERT_EQUAL(os.str(), "12 7 3 8 15 13 19 ");
}

TEST(min_greater_than) {
    BinarySearchTree<int> tree;
    tree.insert(12);
    ASSERT_EQUAL(tree.min_greater_than(12), tree.end());
    tree.insert(7);
    ASSERT_EQUAL(*tree.min_greater_than(7), 12);
    ASSERT_EQUAL(tree.min_greater_than(12), tree.end());
    tree.insert(3);
    ASSERT_EQUAL(*tree.min_greater_than(3), 7);
    tree.insert(8);
    ASSERT_EQUAL(*tree.min_greater_than(7), 8);
    tree.insert(15);
    ASSERT_EQUAL(*tree.min_greater_than(12), 15);
    tree.insert(1);
    ASSERT_EQUAL(*tree.min_greater_than(1), 3);
}

TEST(non_number_tree) {
    BinarySearchTree<string> tree;
    tree.insert("F");
    tree.insert("D");
    tree.insert("B");
    tree.insert("G");
    ASSERT_EQUAL(tree.height(), 3);
    ASSERT_EQUAL("B", *tree.begin());
    ASSERT_EQUAL("D", *(++tree.begin()));
    ASSERT_EQUAL("F", *(++++tree.begin()));
}

TEST(about_empty){
    BinarySearchTree<string> tree;
    ASSERT_TRUE(tree.empty());
    ASSERT_EQUAL(tree.height(), 0);
    ASSERT_EQUAL(tree.size(), 0);
}

TEST(basic){
    BinarySearchTree<int> tree;
    tree.insert(5);
    ASSERT_FALSE(tree.empty());
    ASSERT_EQUAL(tree.height(), 1);
    ASSERT_EQUAL(tree.size(), 1);

    tree.insert(3);
    ASSERT_FALSE(tree.empty());
    ASSERT_EQUAL(tree.height(), 2);
    ASSERT_EQUAL(tree.size(), 2);

    tree.insert(8);
    ASSERT_FALSE(tree.empty());
    ASSERT_EQUAL(tree.height(), 2);
    ASSERT_EQUAL(tree.size(), 3);

    tree.insert(1);
    ASSERT_FALSE(tree.empty());
    ASSERT_EQUAL(tree.height(), 3);
    ASSERT_EQUAL(tree.size(), 4);

    tree.insert(2);
    ASSERT_FALSE(tree.empty());
    ASSERT_EQUAL(tree.height(), 4);
    ASSERT_EQUAL(tree.size(), 5);

    tree.insert(0);
    ASSERT_FALSE(tree.empty());
    ASSERT_EQUAL(tree.height(), 4);
    ASSERT_EQUAL(tree.size(), 6);
}



TEST_MAIN()

