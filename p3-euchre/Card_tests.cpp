// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::RANK_ACE, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit());
}

// Add more test cases here

// Test ctor, get rank, and get suit
TEST(test_card_ctor2) {
    Card c2(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(Card::RANK_ACE, c2.get_rank());
    ASSERT_EQUAL(Card::SUIT_DIAMONDS, c2.get_suit());
}

TEST(test_card_ctor_df) {
    // Test default ctor case
    Card c_df = Card();
    ASSERT_EQUAL(c_df.get_rank(), Card::RANK_TWO);
    ASSERT_EQUAL(c_df.get_suit(), Card::SUIT_SPADES);
    ASSERT_EQUAL(c_df.get_suit(Card::SUIT_DIAMONDS), Card::SUIT_SPADES);
}

TEST(test_card_get_suit_trump) {
    Card jack_heart = Card(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_EQUAL(jack_heart.get_rank(), Card::RANK_JACK);
    ASSERT_EQUAL(jack_heart.get_suit(), Card::SUIT_HEARTS);
    ASSERT_EQUAL(jack_heart.get_suit(Card::SUIT_DIAMONDS), Card::SUIT_DIAMONDS);
}

TEST(test_is_face_or_ace) {
    Card sK(Card::RANK_KING, Card::SUIT_SPADES);
    Card sA(Card::RANK_ACE, Card::SUIT_SPADES);
    Card sJ(Card::RANK_JACK, Card::SUIT_SPADES);
    Card hJ(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card cJ(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card dJ(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card sQ(Card::RANK_QUEEN, Card::SUIT_SPADES);
    Card s8(Card::RANK_EIGHT, Card::SUIT_SPADES);
    Card s3(Card::RANK_THREE, Card::SUIT_SPADES);
    Card s2(Card::RANK_TWO, Card::SUIT_SPADES);
    Card s4(Card::RANK_FOUR, Card::SUIT_SPADES);
    ASSERT_TRUE(sK.is_face_or_ace());
    ASSERT_TRUE(sA.is_face_or_ace());
    ASSERT_TRUE(sJ.is_face_or_ace());
    ASSERT_TRUE(dJ.is_face_or_ace());
    ASSERT_TRUE(cJ.is_face_or_ace());
    ASSERT_TRUE(hJ.is_face_or_ace());
    ASSERT_TRUE(sQ.is_face_or_ace());
    ASSERT_FALSE(s8.is_face_or_ace());
    ASSERT_FALSE(s3.is_face_or_ace());
    ASSERT_FALSE(s2.is_face_or_ace());
    ASSERT_FALSE(s4.is_face_or_ace());
}

TEST(is_right_bower) {
    string trumpS = Card::SUIT_SPADES;
    string trumpD = Card::SUIT_DIAMONDS;
    string trumpH = Card::SUIT_HEARTS;
    string trumpC = Card::SUIT_CLUBS;
    Card sK(Card::RANK_KING, Card::SUIT_SPADES);
    Card sA(Card::RANK_ACE, Card::SUIT_SPADES);
    Card sQ(Card::RANK_QUEEN, Card::SUIT_SPADES);
    Card dA(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    Card dJ(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card hJ(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card cJ(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card sJ(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_FALSE(sK.is_right_bower(trumpS));
    ASSERT_FALSE(sA.is_right_bower(trumpS));
    ASSERT_TRUE(sJ.is_right_bower(trumpS));
    ASSERT_FALSE(sQ.is_right_bower(trumpS));
    ASSERT_FALSE(dA.is_right_bower(trumpS));
    ASSERT_TRUE(dJ.is_right_bower(trumpD));
    ASSERT_TRUE(hJ.is_right_bower(trumpH));
    ASSERT_FALSE(hJ.is_right_bower(trumpD));
    ASSERT_TRUE(cJ.is_right_bower(trumpC));
    ASSERT_FALSE(cJ.is_right_bower(trumpD));
}

TEST(is_left_bower) {
    string trumpS = Card::SUIT_SPADES;
    string trumpD = Card::SUIT_DIAMONDS;
    string trumpH = Card::SUIT_HEARTS;
    string trumpC = Card::SUIT_CLUBS;
    Card sK(Card::RANK_KING, Card::SUIT_SPADES);
    Card sA(Card::RANK_ACE, Card::SUIT_SPADES);
    Card sJ(Card::RANK_JACK, Card::SUIT_SPADES);
    Card sQ(Card::RANK_QUEEN, Card::SUIT_SPADES);
    Card dA(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    Card dJ(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card hJ(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card cJ(Card::RANK_JACK, Card::SUIT_CLUBS);
    ASSERT_FALSE(sK.is_left_bower(trumpS));
    ASSERT_FALSE(sA.is_left_bower(trumpS));
    ASSERT_TRUE(sJ.is_left_bower(trumpC));
    ASSERT_FALSE(sJ.is_left_bower(trumpS));
    ASSERT_FALSE(sJ.is_left_bower(trumpH));
    ASSERT_FALSE(sJ.is_left_bower(trumpD));
    ASSERT_FALSE(sQ.is_left_bower(trumpS));
    ASSERT_FALSE(dA.is_left_bower(trumpS));
    ASSERT_TRUE(cJ.is_left_bower(trumpS));
    ASSERT_FALSE(cJ.is_left_bower(trumpH));
    ASSERT_FALSE(cJ.is_left_bower(trumpD));
    ASSERT_FALSE(cJ.is_left_bower(trumpC));
    ASSERT_TRUE(dJ.is_left_bower(trumpH));
    ASSERT_FALSE(dJ.is_left_bower(trumpD));
    ASSERT_FALSE(dJ.is_left_bower(trumpS));
    ASSERT_FALSE(dJ.is_left_bower(trumpC));
    ASSERT_TRUE(hJ.is_left_bower(trumpD));
    ASSERT_FALSE(hJ.is_left_bower(trumpS));
    ASSERT_FALSE(hJ.is_left_bower(trumpH));
    ASSERT_FALSE(hJ.is_left_bower(trumpC));

    Card cJ_other(Card::RANK_JACK, Suit_next(Card::SUIT_CLUBS));
    ASSERT_TRUE(cJ_other.is_left_bower(trumpC));
    Card sJ_other(Card::RANK_JACK, Suit_next(Card::SUIT_SPADES));
    ASSERT_TRUE(sJ_other.is_left_bower(trumpS));
    Card hJ_other(Card::RANK_JACK, Suit_next(Card::SUIT_HEARTS));
    ASSERT_TRUE(hJ_other.is_left_bower(trumpH));

}

TEST(is_trump) {
    string trump = Card::SUIT_SPADES;
    Card sK(Card::RANK_KING, Card::SUIT_SPADES);
    Card sA(Card::RANK_ACE, Card::SUIT_SPADES);
    Card sQ(Card::RANK_QUEEN, Card::SUIT_SPADES);
    Card sJ(Card::RANK_JACK, Card::SUIT_SPADES);
    Card s2(Card::RANK_TWO, Card::SUIT_SPADES);
    Card cJ(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card dJ(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card dA(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    
    ASSERT_TRUE(sK.is_trump(trump));
    ASSERT_TRUE(sA.is_trump(trump));
    ASSERT_TRUE(sQ.is_trump(trump));
    ASSERT_TRUE(sJ.is_trump(trump));
    ASSERT_TRUE(s2.is_trump(trump));
    ASSERT_TRUE(cJ.is_trump(trump))
    ASSERT_FALSE(dJ.is_trump(trump));
    ASSERT_FALSE(dA.is_trump(trump));
    
}

TEST(test_operators) {
    Card sK(Card::RANK_KING, Card::SUIT_SPADES);
    Card sA(Card::RANK_ACE, Card::SUIT_SPADES);
    Card sJ(Card::RANK_JACK, Card::SUIT_SPADES);
    Card sJ_2(Card::RANK_JACK, Card::SUIT_SPADES);
    Card sQ(Card::RANK_QUEEN, Card::SUIT_SPADES);
    Card dA(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    Card dK(Card::RANK_KING, Card::SUIT_DIAMONDS);
    Card s2(Card::RANK_TWO, Card::SUIT_SPADES);
    Card cA(Card::RANK_ACE, Card::SUIT_CLUBS);
    Card c8(Card::RANK_EIGHT, Card::SUIT_CLUBS);
    Card hA(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card hK(Card::RANK_KING, Card::SUIT_HEARTS);
    ASSERT_TRUE( sK > sQ);
    ASSERT_TRUE( sK >= sK);
    ASSERT_TRUE( sK <= sK);
    ASSERT_FALSE(sA < sA);
    ASSERT_FALSE(sA > sA);
    ASSERT_FALSE(sA < sK);
    ASSERT_TRUE(sA != sK);
    ASSERT_FALSE(sK != sK);
    ASSERT_TRUE(sJ == sJ);
    ASSERT_TRUE(sJ == sJ_2);
    ASSERT_FALSE(sJ != sJ_2);
    ASSERT_TRUE(dK > sK);
    ASSERT_FALSE(dK == sK);
    ASSERT_TRUE(dK != sK);
    ASSERT_FALSE(dA < sK);
    ASSERT_TRUE(dA > s2);
    ASSERT_TRUE(dA > cA);
    ASSERT_TRUE(dA >= cA);
    ASSERT_TRUE(dA > hA);
    ASSERT_FALSE(dA <= hA);
    ASSERT_FALSE(hK >= dK);
    ASSERT_TRUE(dK <= cA);
    ASSERT_TRUE(dK < hA);
    ASSERT_TRUE(c8 < hA);
    ASSERT_FALSE(c8 >= hA);
}


TEST(test_card_less_trump) {
    string trumpS = Card::SUIT_SPADES;
    string trumpD = Card::SUIT_DIAMONDS;
    string trumpH = Card::SUIT_HEARTS;
    string trumpC = Card::SUIT_CLUBS;
    
    Card sA(Card::RANK_ACE, Card::SUIT_SPADES);
    Card sK(Card::RANK_KING, Card::SUIT_SPADES);
    Card sQ(Card::RANK_QUEEN, Card::SUIT_SPADES);
    Card sJ(Card::RANK_JACK, Card::SUIT_SPADES);
    Card s9(Card::RANK_NINE, Card::SUIT_SPADES);
    Card dA(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    Card dK(Card::RANK_KING, Card::SUIT_DIAMONDS);
    Card dJ(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card d9(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card d2(Card::RANK_TWO, Card::SUIT_DIAMONDS);
    Card cK(Card::RANK_KING, Card::SUIT_CLUBS);
    Card cA(Card::RANK_ACE, Card::SUIT_CLUBS);
    Card cJ(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card hA(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card hJ(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card hQ(Card::RANK_QUEEN, Card::SUIT_HEARTS);

    // Test trump case
    ASSERT_TRUE(Card_less(cJ, sJ, trumpS));
    ASSERT_FALSE(Card_less(sJ, cJ, trumpS));
    ASSERT_TRUE(Card_less(sA, cJ, trumpS));
    ASSERT_FALSE(Card_less(cJ, s9, trumpS));
    // Test trump vs other suit
    ASSERT_FALSE(Card_less(sA, dA, trumpS));
    ASSERT_FALSE(Card_less(s9, hA, trumpS));
    ASSERT_FALSE(Card_less(s9, d9, trumpS));
    // Test other suit
    ASSERT_FALSE(Card_less(dA, cA, trumpS));
    ASSERT_FALSE(Card_less(hA, cK,trumpS));


    
    ASSERT_TRUE(Card_less(sK,sA,trumpC));
    ASSERT_FALSE(Card_less(sA,sK,trumpC));
    ASSERT_TRUE(Card_less(sK, cK, trumpC));
    ASSERT_FALSE(Card_less(cK, sK, trumpC));
    ASSERT_FALSE(Card_less(cJ, cK, trumpC));
    ASSERT_TRUE(Card_less(cK, cJ, trumpC));
    ASSERT_FALSE(Card_less(dA, sQ, trumpC));
    ASSERT_TRUE(Card_less(d2, dK, trumpC));
    ASSERT_TRUE(Card_less(sJ, cJ, trumpC));
    ASSERT_FALSE(Card_less(cJ, sJ, trumpC));
    ASSERT_TRUE(Card_less(hJ, sJ, trumpC));
    ASSERT_FALSE(Card_less(dJ, hJ, trumpC));
    ASSERT_TRUE(Card_less(sK, sA, trumpS));
    ASSERT_FALSE(Card_less(d2, sQ, trumpD));
    ASSERT_FALSE(Card_less(hQ, sQ, trumpD));
    ASSERT_FALSE(Card_less(sJ, sJ, trumpS));
    ASSERT_FALSE(Card_less(sJ, sJ, trumpD));
    ASSERT_FALSE(Card_less(sA, dA, trumpS));
    ASSERT_FALSE(Card_less(hJ, sJ, trumpD));
    ASSERT_TRUE(Card_less(hJ, dA, trumpS));
    ASSERT_TRUE(Card_less(cJ, sJ, trumpS));
    ASSERT_TRUE(Card_less(hJ, dJ, trumpD));
    
    
}


TEST(test_card_less_trump_led) {
    string trumpS = Card::SUIT_SPADES;
    string trumpD = Card::SUIT_DIAMONDS;
    string trumpH = Card::SUIT_HEARTS;
    string trumpC = Card::SUIT_CLUBS;

    Card ledD(Card::RANK_TWO, Card::SUIT_DIAMONDS);
    Card ledH(Card::RANK_TWO,Card::SUIT_HEARTS);
    Card ledC(Card::RANK_TWO,Card::SUIT_CLUBS);
    Card ledS(Card::RANK_TWO,Card::SUIT_SPADES);
    
    Card sK(Card::RANK_KING, Card::SUIT_SPADES);
    Card sA(Card::RANK_ACE, Card::SUIT_SPADES);
    Card sQ(Card::RANK_QUEEN, Card::SUIT_SPADES);
    Card sJ(Card::RANK_JACK, Card::SUIT_SPADES);
    Card s9(Card::RANK_NINE, Card::SUIT_SPADES);
    Card s3(Card::RANK_TWO, Card::SUIT_SPADES);
    Card s2(Card::RANK_TWO, Card::SUIT_SPADES);
    
    Card cA(Card::RANK_ACE, Card::SUIT_CLUBS);
    Card cK(Card::RANK_KING, Card::SUIT_CLUBS);
    Card cJ(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card c9(Card::RANK_NINE, Card::SUIT_CLUBS);
    
    Card dA(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    Card dK(Card::RANK_KING, Card::SUIT_DIAMONDS);
    Card dJ(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card d2(Card::RANK_TWO, Card::SUIT_DIAMONDS);

    Card hA(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card hK(Card::RANK_KING, Card::SUIT_HEARTS);
    Card hJ(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card h9(Card::RANK_NINE, Card::SUIT_HEARTS);

    // Test trump
    ASSERT_FALSE(Card_less(cJ, dJ, ledH, trumpS));
    ASSERT_FALSE(Card_less(sJ, hJ, ledH, trumpS));
    ASSERT_FALSE(Card_less(sJ, sA, ledH, trumpS));
    ASSERT_FALSE(Card_less(cJ, cA, ledH, trumpS));

    // Test led
    ASSERT_FALSE(Card_less(hJ, dJ, ledH, trumpS));
    ASSERT_FALSE(Card_less(h9, c9, ledH, trumpS));
    ASSERT_FALSE(Card_less(h9, cK, ledH, trumpS));

    // Test trump vs led
    ASSERT_FALSE(Card_less(sK, hK, ledH, trumpS));
    ASSERT_FALSE(Card_less(s9, hK, ledH, trumpS));
    ASSERT_FALSE(Card_less(cJ, hA, ledH, trumpS));

    ASSERT_FALSE(Card_less(sA,sK,ledD,trumpC));
    ASSERT_TRUE(Card_less(sK, cK, ledD, trumpC));
    ASSERT_FALSE(Card_less(cK, sK, ledD, trumpC));
    ASSERT_FALSE(Card_less(cJ, cK, ledD, trumpC));
    ASSERT_FALSE(Card_less(sJ,cJ , ledC, trumpS));
    ASSERT_TRUE(Card_less(cK, cJ, ledD, trumpC));
    ASSERT_FALSE(Card_less(dA, sQ, ledD, trumpC));
    ASSERT_TRUE(Card_less(d2, dK, ledD, trumpC));
    ASSERT_FALSE(Card_less(d2, sQ, ledD, trumpC));
    ASSERT_TRUE(Card_less(sK, hK, ledD, trumpC));
    ASSERT_FALSE(Card_less(hK, sK, ledD, trumpC));
    ASSERT_TRUE(Card_less(d2, dA, ledD, trumpD));
    ASSERT_TRUE(Card_less(cK, sA, ledD, trumpH));
    ASSERT_TRUE(Card_less(sJ, dJ, ledH, trumpH));
    ASSERT_FALSE(Card_less(cK, sK, ledH, trumpH));
    ASSERT_FALSE(Card_less(hK, dK, ledH, trumpS));
    ASSERT_FALSE(Card_less(hK, cK, ledC, trumpH));
    ASSERT_FALSE(Card_less(sA, sK, ledS, trumpS));
    ASSERT_FALSE(Card_less(sJ, cJ, ledC, trumpS));
    ASSERT_FALSE(Card_less(sJ, sJ, ledS,trumpS));
    ASSERT_TRUE(Card_less(sJ, cJ, ledS, trumpC));
    ASSERT_FALSE(Card_less(sJ, cK, ledS, trumpC));
    ASSERT_FALSE(Card_less(cJ, cK, ledC, trumpC));
}

TEST(test_card_less_trump_led_mk) {
    
    string trumpH = Card::SUIT_HEARTS;

    Card ledH(Card::RANK_JACK, Card::SUIT_HEARTS);
    
    Card cA(Card::RANK_ACE, Card::SUIT_CLUBS);
    Card dJ(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card hJ(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card h9(Card::RANK_NINE, Card::SUIT_HEARTS);
    Card hA(Card::RANK_ACE, Card::SUIT_HEARTS);

    // Test trump
    ASSERT_EQUAL(dJ.get_suit(trumpH), trumpH);
    ASSERT_FALSE(Card_less(dJ, hA, ledH, trumpH));

}


TEST_MAIN()

