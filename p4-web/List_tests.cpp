// Project UID c1f28c309e55405daf00c565d57ff9ad

#include "List.h"
#include "unit_test_framework.h"


// Add your test cases here

TEST(test_stub) {
    // Add test code here
    ASSERT_TRUE(true);
}

TEST(test_list_default_ctor) {
    List<int> empty_list;
    ASSERT_TRUE(empty_list.empty());
}
TEST(test_list_default_ctor1) {
    List<int> zero;
    ASSERT_TRUE(zero.empty());
}

TEST(test_list_default_ctor2) {
    List<int> one;
    one.push_front(1);
    ASSERT_FALSE(one.empty());
}

TEST(test_size) {
    List<int> list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    ASSERT_EQUAL(3, list.size());
}

TEST(test_size_1) {
    List<int> list;
    list.push_front(1);
    ASSERT_EQUAL(1, list.size());
}

TEST(test_size_2) {
    List<int> list;
    ASSERT_EQUAL(0,list.size());
}

TEST(test_front) {
    List<int> list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    ASSERT_EQUAL(3, list.front());
}

TEST(test_front_1) {
    List<int> list;
    list.push_front(1);
    ASSERT_EQUAL(1, list.front());
}

TEST(test_back) {
    List<int> list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    ASSERT_EQUAL(1, list.back());
}

TEST(test_back_1) {
    List<int> list;
    list.push_front(1);
    ASSERT_EQUAL(1, list.back());
}
TEST(push_front) {
    List<int> list;
    list.push_front(1);
    ASSERT_EQUAL(1, list.front());
    ASSERT_EQUAL(1, list.back());
    ASSERT_EQUAL(1, list.size());

}

TEST(push_back) {
    List<int> list;
    list.push_back(1);
    ASSERT_EQUAL(1, list.front());
    ASSERT_EQUAL(1, list.back());
    ASSERT_EQUAL(1, list.size());
}
TEST(test_pop_back) {
    List<int> list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    list.pop_back();
    ASSERT_EQUAL(2, list.back());
}


TEST(test_pop_back_1) {
    List<int> list;
    list.push_front(1);
    list.pop_back();
    ASSERT_EQUAL(0, list.size());
}

TEST(test_pop_back_2) {
    List<int> list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    list.pop_back();
    list.pop_back();
    list.pop_back();
    ASSERT_TRUE(list.empty());
}

TEST(test_pop_front) {
    List<int> list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    list.pop_front();
    ASSERT_EQUAL(2, list.front());
}

TEST(test_pop_front_1) {
    List<int> list;
    list.push_front(1);
    list.pop_front();
    ASSERT_TRUE(list.empty());
}

TEST(test_pop_front_2) {
    List<int> list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    list.pop_front();
    list.pop_front();
    list.pop_front();
    ASSERT_EQUAL(1, list.empty());
}

TEST(test_clear) {
    List<int> list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    list.clear();
    ASSERT_EQUAL(0, list.size());
    ASSERT_TRUE(list.empty());
}

TEST(test_list_size) {
    List<int> list;
    list.push_front(1);
    ASSERT_FALSE(list.empty());
    ASSERT_EQUAL(1, list.size());
}

TEST(begin) {
    List<int> list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    ASSERT_EQUAL(*list.begin(), 3);
}

TEST(begin_1) {
    List<int> list;
    list.push_front(1);
    ASSERT_EQUAL(*list.begin(), 1);
}

TEST(test_iterator) {
    List<int> list;
    list.push_front(1);
    list.push_back(2);
    list.push_front(3);
    List<int>::Iterator i;
    int arrList[3] = {3, 1, 2};
    int k = 0;
    for (i = list.begin(); i != list.end(); ++i) {
        ASSERT_EQUAL(arrList[k++], *i);
    }
}

TEST(erase){
    List<int> list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    List<int>::Iterator i = list.begin();
    list.erase(i);
    ASSERT_EQUAL(list.size(),2);
    ASSERT_EQUAL(list.back(), 1);
    ASSERT_EQUAL(list.front(), 2);
    
    i = list.begin();
    ++i;
    list.erase(i);
    ASSERT_EQUAL(list.size(),1);
    ASSERT_EQUAL(list.back(), 2);
    ASSERT_EQUAL(list.front(), 2);
    
    i = list.begin();
    list.erase(i);
    ASSERT_EQUAL(list.size(),0);
    

}
TEST(erase_2){
    List<int> list;
    list.push_front(1);
    List<int>::Iterator i = list.begin();
    list.erase(i);
    ASSERT_EQUAL(0,list.size());
}

TEST(insert) {
    List<int> list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    List<int>::Iterator i = list.begin();
    const int datum = 4;
    list.insert(i, datum);
    ASSERT_EQUAL(list.front(),4);
}


TEST(insert_2) {
    List<int> list;
    List<int>::Iterator i = list.begin();
    list.insert(i, 1);
    ASSERT_EQUAL(list.size(), 1);
    ASSERT_EQUAL(list.front(), 1);
    ASSERT_EQUAL(list.back(), 1);
}

TEST(insert_3) {
    List<int> list;
    List<int>::Iterator i = list.end();
    list.insert(i, 1);
    ASSERT_EQUAL(list.size(), 1);
    ASSERT_EQUAL(list.front(), 1);
    ASSERT_EQUAL(list.back(), 1);
}

TEST(insert_4) {
    List<int> list;
    List<int>::Iterator i = list.begin();
    list.insert(i, 1);
    list.insert(i,2);
    ASSERT_EQUAL(list.size(), 2);
    ASSERT_EQUAL(list.front(), 1);
    ASSERT_EQUAL(list.back(), 2);
}

TEST(insert_5) {
    List<int> list;
    List<int>::Iterator i = list.begin();
    list.insert(i, 1);
    list.insert(i,2); //  1,3,2
    i = list.begin();
        ++i;
    list.insert(i, 3);
    ASSERT_EQUAL(list.size(), 3);
    ASSERT_EQUAL(list.front(), 1);
    ASSERT_EQUAL(list.back(), 2);
}

TEST(ioperator) {
    List<int> list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    List<int>::Iterator i = list.begin();
    ASSERT_EQUAL(*i, 3);
    ++i;
    ASSERT_EQUAL(*i, 2);
}

TEST(ioperator_1) {
    List<int> list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    list.push_back(1);
    list.push_back(3);
    List<int>::Iterator i = list.begin();//3
    List<int>::Iterator k = ++i; //2
    List<int>::Iterator j = ++i; //1
    List<int>::Iterator d = ++i; //1
    List<int>::Iterator e = list.begin();//3
    List<int>::Iterator m = ++i;//
    // list 3,2,1,1,3
    ASSERT_FALSE(k == i);
    ASSERT_EQUAL(*j, 1);
    ASSERT_EQUAL(*d, 1);
    ASSERT_TRUE(*d == *j);
    ASSERT_TRUE(k != j);
    ASSERT_TRUE(*e == *i);
    ASSERT_TRUE(m == i);
}

TEST(opertator) {
    List<int> list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    List<int> copy(list);
    ASSERT_EQUAL(3, copy.size());
    ASSERT_TRUE(*list.begin() == *copy.begin());
    List<int>::Iterator i = list.begin();
    List<int>::Iterator k = copy.begin();
    for(int j = 0; j < copy.size(); j++) {
        ASSERT_EQUAL(*i, *k)
        ++i;
        ++k;
    }
 }

TEST(opertator2) {
    List<int> list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    //3,2,1
    List<int>::Iterator i = list.begin(); //3
    List<int>::Iterator k = ++i; //2
    List<int>::Iterator j = --i; //3
    ASSERT_TRUE(i == j);
    ASSERT_EQUAL(*(++j), 2);
    ASSERT_FALSE(*k == *(--j));
    ASSERT_TRUE(i != k);
 }


TEST(test_i) {
    List<int> list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    List<int>::Iterator i;
    int arr[3] = {3,2,1};
    int k = 0;
    for (i = list.begin(); i != list.end(); ++i) {
        ASSERT_EQUAL(arr[k++], *i);
    }
}

TEST(construttest) {
    List<int> list;
    ASSERT_EQUAL(0, list.size());
    ASSERT_TRUE(list.empty());
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    List<int> copy(list);
    List<int>::Iterator i = list.begin();
    List<int>::Iterator j = copy.begin();
    ASSERT_EQUAL(3, copy.size());
    for (int k = 0; k < copy.size(); k++) {
        ASSERT_EQUAL(*i, *j)
        ++i;
        ++j;
    }
    List<int> cop2;
    cop2.push_back(2);
    cop2 = list;
    i = list.begin();
    j = cop2.begin();
    for (int o = 0;  o < copy.size(); o++) {
        ASSERT_EQUAL(*i, *j)
        ++i;
        ++j;
    }
}

TEST(test_itor) {
    List<int> list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    // 3(k),2(i j),1
    List<int>::Iterator i = list.begin();
    List<int>::Iterator j = ++i;
    List<int>::Iterator k = list.begin();
    //i = 2, j = 2, k =3
    ASSERT_TRUE(i == j);
    ASSERT_FALSE(i == k);
    --i;
    ASSERT_TRUE(i == k);
    ASSERT_FALSE(j == k);
    ++k;
    ASSERT_TRUE(k == j);
}



TEST_MAIN()

