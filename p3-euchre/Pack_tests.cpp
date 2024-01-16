// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Pack.h"
#include "unit_test_framework.h"

#include <iostream>
using namespace std;

TEST(test_pack_default_ctor) {
    Pack pack;
    Card first = pack.deal_one();
    ASSERT_EQUAL(Card::RANK_NINE, first.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, first.get_suit());
}

// Add more tests here
TEST(test_pack_reset) {
  Pack pack;
  pack.deal_one();
  pack.reset();
  Card first_card = pack.deal_one();
  ASSERT_EQUAL(first_card, Card(Card::RANK_NINE, Card::SUIT_SPADES));
}

TEST(test_pack_empty) {
  Pack pack;
  int PACK_SIZE = 24;
  for (int i = 0; i < PACK_SIZE-1; ++i) {
    pack.deal_one();
    ASSERT_FALSE(pack.empty());
  }
  pack.deal_one();
  ASSERT_TRUE(pack.empty());
}

TEST(test_pack_shuffle) {
  Pack pack;
  Pack new_pack;
  for (int i = 0; i < 20; ++i) {
    new_pack.shuffle();
  }
  // ASSERT_EQUAL(new_pack, pack);
  for (int k = 0; k < 24; ++k) {
    ASSERT_EQUAL(new_pack.deal_one(), pack.deal_one());
  }
}

TEST_MAIN()
