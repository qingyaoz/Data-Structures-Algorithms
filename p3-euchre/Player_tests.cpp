// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "unit_test_framework.h"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

// Add more tests here
TEST(test_player_ctor) {
    Player * robot = Player_factory("Robot", "Simple");
    ASSERT_EQUAL("Robot", robot->get_name());
    ostringstream oss1;
    oss1 << * robot;
    ASSERT_EQUAL(oss1.str(), "Robot");

    Player * katherine = Player_factory("Katherine", "Human");
    ASSERT_EQUAL("Katherine", katherine->get_name());
    ostringstream oss2;
    oss2 << * katherine;
    ASSERT_EQUAL(oss2.str(), "Katherine");

    delete robot;
    delete katherine;
}

// ******************* MAKE_TRUMP TEST CASES *******************
TEST(test_player_make_trump_r1_1c) {
    // Create players
    Player * robot = Player_factory("Robot", "Simple");

    robot->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));

    Card upcard(Card::RANK_ACE, Card::SUIT_SPADES);
    string order_up_suit;

    bool expected_d = robot->make_trump(upcard, true, 1, order_up_suit);
    ASSERT_FALSE(expected_d);
    ASSERT_EQUAL(order_up_suit, "");


    bool expected_nd = robot->make_trump(upcard, false, 1, order_up_suit);
    ASSERT_FALSE(expected_nd);
    ASSERT_EQUAL(order_up_suit, ""); // order_up_suit has not been changed
    
    delete robot;
}

TEST(test_player_make_trump_r1_1c_left_b) {
    // Create players
    Player * robot = Player_factory("Robot", "Simple");

    robot->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));

    Card upcard(Card::RANK_ACE, Card::SUIT_SPADES);
    string order_up_suit;

    bool expected_d = robot->make_trump(upcard, true, 1, order_up_suit);
    ASSERT_FALSE(expected_d);
    ASSERT_EQUAL(order_up_suit, "");


    bool expected_nd = robot->make_trump(upcard, false, 1, order_up_suit);
    ASSERT_FALSE(expected_nd);
    ASSERT_EQUAL(order_up_suit, ""); // order_up_suit has not been changed
    
    delete robot;
}

TEST(test_player_make_trump_r1_2c_normalup) {
    // Create players
    Player * robot = Player_factory("Robot", "Simple");

    robot->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
    robot->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));

    Card upcard(Card::RANK_ACE, Card::SUIT_SPADES);
    string order_up_suit;

    bool expected_d = robot->make_trump(upcard, true, 1, order_up_suit);
    ASSERT_TRUE(expected_d);
    ASSERT_EQUAL(order_up_suit, Card::SUIT_SPADES);

    order_up_suit = "";
    bool expected_nd = robot->make_trump(upcard, false, 1, order_up_suit);
    ASSERT_TRUE(expected_nd);
    ASSERT_EQUAL(order_up_suit, Card::SUIT_SPADES);
    
    delete robot;
}

TEST(test_player_make_trump_r1_2c_normalno) {
    // Create players
    Player * robot = Player_factory("Robot", "Simple");

    robot->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
    robot->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));

    Card upcard(Card::RANK_ACE, Card::SUIT_SPADES);
    string order_up_suit;

    bool expected_d = robot->make_trump(upcard, true, 1, order_up_suit);
    ASSERT_FALSE(expected_d);
    ASSERT_EQUAL(order_up_suit, "");

    bool expected_nd = robot->make_trump(upcard, false, 1, order_up_suit);
    ASSERT_FALSE(expected_nd);
    ASSERT_EQUAL(order_up_suit, "");
    
    delete robot;
}

TEST(test_player_make_trump_r1_2c_left_b) {
    // Create players
    Player * robot = Player_factory("Robot", "Simple");

    robot->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
    robot->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));

    Card upcard(Card::RANK_ACE, Card::SUIT_SPADES);
    string order_up_suit;

    bool expected_d = robot->make_trump(upcard, true, 1, order_up_suit);
    ASSERT_TRUE(expected_d);
    ASSERT_EQUAL(order_up_suit, Card::SUIT_SPADES);

    order_up_suit = "";
    bool expected_nd = robot->make_trump(upcard, false, 1, order_up_suit);
    ASSERT_TRUE(expected_nd);
    ASSERT_EQUAL(order_up_suit, Card::SUIT_SPADES);
    
    delete robot;
}

TEST(test_player_make_trump_r1_2c_right_b) {
    // Create players
    Player * robot = Player_factory("Robot", "Simple");

    robot->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
    robot->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));

    Card upcard(Card::RANK_ACE, Card::SUIT_SPADES);
    string order_up_suit;

    bool expected_d = robot->make_trump(upcard, true, 1, order_up_suit);
    ASSERT_TRUE(expected_d);
    ASSERT_EQUAL(order_up_suit, Card::SUIT_SPADES);

    order_up_suit = "";
    bool expected_nd = robot->make_trump(upcard, false, 1, order_up_suit);
    ASSERT_TRUE(expected_nd);
    ASSERT_EQUAL(order_up_suit, Card::SUIT_SPADES);
    
    delete robot;
}

TEST(test_player_make_trump_r1_5c_left_b) {
    // Create players
    Player * robot = Player_factory("Robot", "Simple");

    robot->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    robot->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    robot->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
    robot->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
    robot->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));

    Card upcard(Card::RANK_ACE, Card::SUIT_SPADES);
    string order_up_suit;

    bool expected_d = robot->make_trump(upcard, true, 1, order_up_suit);
    ASSERT_TRUE(expected_d);
    ASSERT_EQUAL(order_up_suit, Card::SUIT_SPADES);

    order_up_suit = "";
    bool expected_nd = robot->make_trump(upcard, false, 1, order_up_suit);
    ASSERT_TRUE(expected_nd);
    ASSERT_EQUAL(order_up_suit, Card::SUIT_SPADES);
    
    delete robot;
}

TEST(test_player_make_trump_r1_5c_right_b) {
    // Create players
    Player * robot = Player_factory("Robot", "Simple");

    robot->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    robot->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    robot->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
    robot->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
    robot->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));

    Card upcard(Card::RANK_ACE, Card::SUIT_SPADES);
    string order_up_suit;

    bool expected_d = robot->make_trump(upcard, true, 1, order_up_suit);
    ASSERT_TRUE(expected_d);
    ASSERT_EQUAL(order_up_suit, Card::SUIT_SPADES);

    order_up_suit = "";
    bool expected_nd = robot->make_trump(upcard, false, 1, order_up_suit);
    ASSERT_TRUE(expected_nd);
    ASSERT_EQUAL(order_up_suit, Card::SUIT_SPADES);
    
    delete robot;
}

TEST(test_player_make_trump_r1_5c_no) {
    // Create players
    Player * robot = Player_factory("Robot", "Simple");

    robot->add_card(Card(Card::RANK_EIGHT, Card::SUIT_SPADES));
    robot->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    robot->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    robot->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
    robot->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));

    Card upcard(Card::RANK_ACE, Card::SUIT_SPADES);
    string order_up_suit;

    bool expected_d = robot->make_trump(upcard, true, 1, order_up_suit);
    ASSERT_FALSE(expected_d);
    ASSERT_EQUAL(order_up_suit, "");

    bool expected_nd = robot->make_trump(upcard, false, 1, order_up_suit);
    ASSERT_FALSE(expected_nd);
    ASSERT_EQUAL(order_up_suit, "");
    
    delete robot;
}

TEST(test_player_make_trump_r2_no_fordealer) {
    // Create players
    Player * robot = Player_factory("Robot", "Simple");

    robot->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
    robot->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));


    Card upcard(Card::RANK_ACE, Card::SUIT_SPADES);
    string order_up_suit;

    bool expected_nd = robot->make_trump(upcard, false, 2, order_up_suit);
    ASSERT_FALSE(expected_nd);
    ASSERT_EQUAL(order_up_suit, ""); // order_up_suit has not been changed
    

    bool expected_d = robot->make_trump(upcard, true, 2, order_up_suit);
    ASSERT_TRUE(expected_d);
    ASSERT_EQUAL(order_up_suit, Card::SUIT_CLUBS);

    delete robot;
}

TEST(test_player_make_trump_r2_2c_left_b) {
    // Create players
    Player * robot = Player_factory("Robot", "Simple");

    robot->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
    robot->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));

    Card upcard(Card::RANK_ACE, Card::SUIT_SPADES);
    string order_up_suit;

    bool expected_nd = robot->make_trump(upcard, false, 2, order_up_suit);
    ASSERT_TRUE(expected_nd);
    ASSERT_EQUAL(order_up_suit, Suit_next(Card::SUIT_SPADES));
    
    delete robot;
}

TEST(test_player_make_trump_r2_2c_right_b) {
    // Create players
    Player * robot = Player_factory("Robot", "Simple");

    robot->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
    robot->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));

    Card upcard(Card::RANK_ACE, Card::SUIT_SPADES);
    string order_up_suit;

    bool expected_nd = robot->make_trump(upcard, false, 2, order_up_suit);
    ASSERT_TRUE(expected_nd);
    ASSERT_EQUAL(order_up_suit, Suit_next(Card::SUIT_SPADES));
    
    delete robot;
}

TEST(test_player_make_trump_r2_2c_only_upsuit) {
    // Create players
    Player * robot = Player_factory("Robot", "Simple");

    robot->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
    robot->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));

    Card upcard(Card::RANK_ACE, Card::SUIT_SPADES);
    string order_up_suit;

    bool expected_nd = robot->make_trump(upcard, false, 2, order_up_suit);
    ASSERT_FALSE(expected_nd);
    ASSERT_EQUAL(order_up_suit, "");
    
    delete robot;
}

TEST(test_player_make_trump_r2_5c) {
    // Create players
    Player * robot = Player_factory("Robot", "Simple");

    robot->add_card(Card(Card::RANK_EIGHT, Card::SUIT_SPADES));
    robot->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    robot->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    robot->add_card(Card(Card::RANK_KING, Card::SUIT_CLUBS));
    robot->add_card(Card(Card::RANK_ACE, Card::SUIT_CLUBS));

    Card upcard(Card::RANK_ACE, Card::SUIT_SPADES);
    string order_up_suit;

    bool expected_nd = robot->make_trump(upcard, false, 2, order_up_suit);
    ASSERT_TRUE(expected_nd);
    ASSERT_EQUAL(order_up_suit, Suit_next(Card::SUIT_SPADES));
    
    delete robot;
}

TEST(test_player_make_trump_r2_5c_no) {
    // Create players
    Player * robot = Player_factory("Robot", "Simple");

    robot->add_card(Card(Card::RANK_EIGHT, Card::SUIT_SPADES));
    robot->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    robot->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    robot->add_card(Card(Card::RANK_EIGHT, Card::SUIT_CLUBS));
    robot->add_card(Card(Card::RANK_NINE, Card::SUIT_CLUBS));

    Card upcard(Card::RANK_ACE, Card::SUIT_SPADES);
    string order_up_suit;

    bool expected_nd = robot->make_trump(upcard, false, 2, order_up_suit);
    ASSERT_FALSE(expected_nd);
    ASSERT_EQUAL(order_up_suit, "");
    
    delete robot;
}

// ******************* LEAD_CARD TEST CASES *******************
TEST(test_player_lead_card_nontrump) {
    // Create players
    Player * robot = Player_factory("Robot", "Simple");

    robot->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    robot->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
    robot->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
    robot->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    robot->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));

    string trump = Card::SUIT_HEARTS;
    Card play_card_1 = robot->lead_card(trump);
    ASSERT_EQUAL(play_card_1, Card(Card::RANK_ACE, Card::SUIT_SPADES));
    Card play_card_2 = robot->lead_card(trump);
    ASSERT_EQUAL(play_card_2, Card(Card::RANK_KING, Card::SUIT_SPADES));
    Card play_card_3 = robot->lead_card(trump);
    ASSERT_EQUAL(play_card_3, Card(Card::RANK_JACK, Card::SUIT_CLUBS));
    Card play_card_4 = robot->lead_card(trump);
    ASSERT_EQUAL(play_card_4, Card(Card::RANK_JACK, Card::SUIT_SPADES));
    Card play_card_5 = robot->lead_card(trump);
    ASSERT_EQUAL(play_card_5, Card(Card::RANK_TEN, Card::SUIT_SPADES));
    
    delete robot;
}

TEST(test_player_lead_card_notall_1) {
    // Create players
    Player * robot = Player_factory("Robot", "Simple");

    robot->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    robot->add_card(Card(Card::RANK_FIVE, Card::SUIT_SPADES));
    robot->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
    robot->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));
    robot->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));

    string trump = Card::SUIT_HEARTS;
    Card play_card_1 = robot->lead_card(trump);
    ASSERT_EQUAL(play_card_1, Card(Card::RANK_NINE, Card::SUIT_SPADES));
    Card play_card_2 = robot->lead_card(trump);
    ASSERT_EQUAL(play_card_2, Card(Card::RANK_FIVE, Card::SUIT_SPADES));
    Card play_card_3 = robot->lead_card(trump);
    ASSERT_EQUAL(play_card_3, Card(Card::RANK_JACK, Card::SUIT_HEARTS));
    Card play_card_4 = robot->lead_card(trump);
    ASSERT_EQUAL(play_card_4, Card(Card::RANK_ACE, Card::SUIT_HEARTS));
    Card play_card_5 = robot->lead_card(trump);
    ASSERT_EQUAL(play_card_5, Card(Card::RANK_KING, Card::SUIT_HEARTS));
    
    delete robot;
}

TEST(test_player_lead_card_notall_2) {
    // Create players
    Player * robot = Player_factory("Robot", "Simple");

    robot->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    robot->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
    robot->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
    robot->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));
    robot->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));

    string trump = Card::SUIT_HEARTS;
    Card play_card_1 = robot->lead_card(trump);
    ASSERT_EQUAL(play_card_1, Card(Card::RANK_ACE, Card::SUIT_SPADES));
    Card play_card_2 = robot->lead_card(trump);
    ASSERT_EQUAL(play_card_2, Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
    Card play_card_3 = robot->lead_card(trump);
    ASSERT_EQUAL(play_card_3, Card(Card::RANK_JACK, Card::SUIT_HEARTS));
    Card play_card_4 = robot->lead_card(trump);
    ASSERT_EQUAL(play_card_4, Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
    Card play_card_5 = robot->lead_card(trump);
    ASSERT_EQUAL(play_card_5, Card(Card::RANK_ACE, Card::SUIT_HEARTS));
    
    delete robot;
}

TEST(test_player_lead_card_alltrump) {
    // Create players
    Player * robot = Player_factory("Robot", "Simple");

    robot->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));
    robot->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
    robot->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
    robot->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
    robot->add_card(Card(Card::RANK_NINE, Card::SUIT_HEARTS));

    string trump = Card::SUIT_HEARTS;
    Card play_card_1 = robot->lead_card(trump);
    ASSERT_EQUAL(play_card_1, Card(Card::RANK_JACK, Card::SUIT_HEARTS));
    Card play_card_2 = robot->lead_card(trump);
    ASSERT_EQUAL(play_card_2, Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
    Card play_card_3 = robot->lead_card(trump);
    ASSERT_EQUAL(play_card_3, Card(Card::RANK_ACE, Card::SUIT_HEARTS));
    Card play_card_4 = robot->lead_card(trump);
    ASSERT_EQUAL(play_card_4, Card(Card::RANK_KING, Card::SUIT_HEARTS));
    Card play_card_5 = robot->lead_card(trump);
    ASSERT_EQUAL(play_card_5, Card(Card::RANK_NINE, Card::SUIT_HEARTS));
    
    delete robot;
}

// ******************* PLAY_CARD TEST CASES *******************
// suit = trump & no suit
TEST(test_player_play_card_set_nosuit) {
    // Create players
    Player * robot = Player_factory("Robot", "Simple");

    robot->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    robot->add_card(Card(Card::RANK_ACE, Card::SUIT_CLUBS));
    robot->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
    robot->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    robot->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
    
    Card led_card(Card::RANK_JACK, Card::SUIT_HEARTS);
    string trump = Card::SUIT_HEARTS;

    Card play_card_1 = robot->play_card(led_card, trump);
    ASSERT_EQUAL(play_card_1, Card(Card::RANK_NINE, Card::SUIT_SPADES));
    Card play_card_2 = robot->play_card(led_card, trump);
    ASSERT_EQUAL(play_card_2, Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
    Card play_card_3 = robot->play_card(led_card, trump);
    ASSERT_EQUAL(play_card_3, Card(Card::RANK_JACK, Card::SUIT_SPADES));
    Card play_card_4 = robot->play_card(led_card, trump);
    ASSERT_EQUAL(play_card_4, Card(Card::RANK_ACE, Card::SUIT_SPADES));
    Card play_card_5 = robot->play_card(led_card, trump);
    ASSERT_EQUAL(play_card_5, Card(Card::RANK_ACE, Card::SUIT_CLUBS));
    
    delete robot;
}

TEST(test_player_play_card_set_suit) {
    // Create players
    Player * robot = Player_factory("Robot", "Simple");

    robot->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    robot->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
    robot->add_card(Card(Card::RANK_NINE, Card::SUIT_HEARTS));
    robot->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));
    robot->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));

    Card led_card(Card::RANK_JACK, Card::SUIT_HEARTS);
    string trump = Card::SUIT_HEARTS;

    Card play_card_1 = robot->play_card(led_card, trump);
    ASSERT_EQUAL(play_card_1, Card(Card::RANK_JACK, Card::SUIT_HEARTS));
    Card play_card_2 = robot->play_card(led_card, trump);
    ASSERT_EQUAL(play_card_2, Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
    Card play_card_3 = robot->play_card(led_card, trump);
    ASSERT_EQUAL(play_card_3, Card(Card::RANK_ACE, Card::SUIT_HEARTS));
    Card play_card_4 = robot->play_card(led_card, trump);
    ASSERT_EQUAL(play_card_4, Card(Card::RANK_NINE, Card::SUIT_HEARTS));
    Card play_card_5 = robot->play_card(led_card, trump);
    ASSERT_EQUAL(play_card_5, Card(Card::RANK_ACE, Card::SUIT_SPADES));
    
    delete robot;
}

//suit != trump, no suit cards, have trump cards
TEST(test_player_play_card_snt_ns_t) {
    // Create players
    Player * robot = Player_factory("Robot", "Simple");

    robot->add_card(Card(Card::RANK_ACE, Card::SUIT_CLUBS));
    robot->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
    robot->add_card(Card(Card::RANK_NINE, Card::SUIT_HEARTS));
    robot->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));
    robot->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
    
    Card led_card(Card::RANK_JACK, Card::SUIT_SPADES);
    string trump = Card::SUIT_HEARTS;

    Card play_card_1 = robot->play_card(led_card, trump);
    ASSERT_EQUAL(play_card_1, Card(Card::RANK_ACE, Card::SUIT_CLUBS));
    Card play_card_2 = robot->play_card(led_card, trump);
    ASSERT_EQUAL(play_card_2, Card(Card::RANK_NINE, Card::SUIT_HEARTS));
    Card play_card_3 = robot->play_card(led_card, trump);
    ASSERT_EQUAL(play_card_3, Card(Card::RANK_ACE, Card::SUIT_HEARTS));
    Card play_card_4 = robot->play_card(led_card, trump);
    ASSERT_EQUAL(play_card_4, Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
    Card play_card_5 = robot->play_card(led_card, trump);
    ASSERT_EQUAL(play_card_5, Card(Card::RANK_JACK, Card::SUIT_HEARTS));
    
    delete robot;
}

//suit != trump, have suit cards, no trump cards
TEST(test_player_play_card_snt_s_nt) {
    // Create players
    Player * robot = Player_factory("Robot", "Simple");

    robot->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
    robot->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
    robot->add_card(Card(Card::RANK_NINE, Card::SUIT_HEARTS));
    robot->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    robot->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));
    
    Card led_card(Card::RANK_JACK, Card::SUIT_SPADES);
    string trump = Card::SUIT_DIAMONDS;

    Card play_card_1 = robot->play_card(led_card, trump);
    ASSERT_EQUAL(play_card_1, Card(Card::RANK_ACE, Card::SUIT_SPADES));
    Card play_card_2 = robot->play_card(led_card, trump);
    ASSERT_EQUAL(play_card_2, Card(Card::RANK_JACK, Card::SUIT_SPADES));
    Card play_card_3 = robot->play_card(led_card, trump);
    ASSERT_EQUAL(play_card_3, Card(Card::RANK_NINE, Card::SUIT_HEARTS));
    Card play_card_4 = robot->play_card(led_card, trump);
    ASSERT_EQUAL(play_card_4, Card(Card::RANK_JACK, Card::SUIT_CLUBS));
    Card play_card_5 = robot->play_card(led_card, trump);
    ASSERT_EQUAL(play_card_5, Card(Card::RANK_ACE, Card::SUIT_HEARTS));
    
    delete robot;
}

//suit != trump, have suit cards, have trump cards
TEST(test_player_play_card_snt_s_t) {
    // Create players
    Player * robot = Player_factory("Robot", "Simple");

    robot->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
    robot->add_card(Card(Card::RANK_ACE, Card::SUIT_CLUBS));
    robot->add_card(Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));
    robot->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
    robot->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));
    
    Card led_card(Card::RANK_JACK, Card::SUIT_HEARTS);
    string trump = Card::SUIT_CLUBS;

    Card play_card_1 = robot->play_card(led_card, trump);
    ASSERT_EQUAL(play_card_1, Card(Card::RANK_ACE, Card::SUIT_HEARTS));
    Card play_card_2 = robot->play_card(led_card, trump);
    ASSERT_EQUAL(play_card_2, Card(Card::RANK_JACK, Card::SUIT_HEARTS));

    robot->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
    robot->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));

    Card play_card_sp = robot->play_card(led_card, trump);
    ASSERT_EQUAL(play_card_sp, Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));

    Card play_card_3 = robot->play_card(led_card, trump);
    ASSERT_EQUAL(play_card_3, Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));
    Card play_card_4 = robot->play_card(led_card, trump);
    ASSERT_EQUAL(play_card_4, Card(Card::RANK_ACE, Card::SUIT_CLUBS));
    Card play_card_5 = robot->play_card(led_card, trump);
    ASSERT_EQUAL(play_card_5, Card(Card::RANK_JACK, Card::SUIT_SPADES));
    Card play_card_6 = robot->play_card(led_card, trump);
    ASSERT_EQUAL(play_card_6, Card(Card::RANK_JACK, Card::SUIT_CLUBS));
    
    delete robot;
}

// ******************* ADD_AND_DISCARD TEST CASES *******************
// Use play_card to test
// trump always not the suit of cards, to make sure play the lowest value card

TEST(test_player_add_and_discard_smallest_up) {
    // Create players
    Player * robot = Player_factory("Robot", "Simple");

    robot->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
    robot->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
    robot->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
    robot->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
    robot->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

    Card upcard(Card::RANK_NINE, Card::SUIT_SPADES);
    string trump = Card::SUIT_SPADES;
    robot->add_and_discard(upcard); //discard ten
    Card highest_1 = robot->play_card(upcard, trump);
    ASSERT_EQUAL(highest_1, Card(Card::RANK_JACK, Card::SUIT_SPADES));

    Card ledcard(Card::RANK_NINE, Card::SUIT_HEARTS);
    robot->add_and_discard(upcard); //discard upcard
    Card lowest_1 = robot->play_card(ledcard, trump);
    ASSERT_EQUAL(lowest_1, Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
    delete robot;
}

TEST(test_player_add_and_discard_smallrank_up) {
    // Create players
    Player * robot = Player_factory("Robot", "Simple");

    robot->add_card(Card(Card::RANK_TEN, Card::SUIT_CLUBS));
    robot->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
    robot->add_card(Card(Card::RANK_QUEEN, Card::SUIT_CLUBS));
    robot->add_card(Card(Card::RANK_KING, Card::SUIT_CLUBS));
    robot->add_card(Card(Card::RANK_ACE, Card::SUIT_CLUBS));

    Card upcard(Card::RANK_NINE, Card::SUIT_SPADES);
    string trump = Card::SUIT_SPADES;
    robot->add_and_discard(upcard); //discard ten
    Card highest_1 = robot->play_card(upcard, trump);
    ASSERT_EQUAL(highest_1, Card(Card::RANK_JACK, Card::SUIT_CLUBS));

    Card highest_2 = robot->play_card(upcard, trump);
    ASSERT_EQUAL(highest_2, Card(Card::RANK_NINE, Card::SUIT_SPADES));

    Card ledcard(Card::RANK_NINE, Card::SUIT_HEARTS);
    Card lowest_1 = robot->play_card(ledcard, trump);
    ASSERT_EQUAL(lowest_1, Card(Card::RANK_QUEEN, Card::SUIT_CLUBS));
    delete robot;
}

TEST(test_player_add_and_discard_left) {
    // Create players
    Player * robot = Player_factory("Robot", "Simple");

    robot->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));

    Card upcard(Card::RANK_ACE, Card::SUIT_CLUBS);
    string trump = Card::SUIT_CLUBS;

    robot->add_and_discard(upcard); //discard upcard
    Card highest_1 = robot->play_card(upcard, trump);
    ASSERT_EQUAL(highest_1, Card(Card::RANK_JACK, Card::SUIT_SPADES));

    delete robot;
}

TEST(test_player_add_and_discard_right) {
    // Create players
    Player * robot = Player_factory("Robot", "Simple");

    robot->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));

    Card upcard(Card::RANK_ACE, Card::SUIT_SPADES);
    string trump = Card::SUIT_SPADES;

    robot->add_and_discard(upcard); //discard upcard
    Card highest_1 = robot->play_card(upcard, trump);
    ASSERT_EQUAL(highest_1, Card(Card::RANK_JACK, Card::SUIT_SPADES));

    delete robot;
}

TEST(test_player_add_and_discard_left_right) {
    // Create players
    Player * robot = Player_factory("Robot", "Simple");

    robot->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));

    Card upcard(Card::RANK_JACK, Card::SUIT_SPADES);
    string trump = Card::SUIT_SPADES;

    robot->add_and_discard(upcard); //discard cJ
    Card highest_1 = robot->play_card(upcard, trump);
    ASSERT_EQUAL(highest_1, Card(Card::RANK_JACK, Card::SUIT_SPADES));

    delete robot;
}

TEST(test_player_add_and_discard_normal_bigup) {
    // Create players
    Player * robot = Player_factory("Robot", "Simple");

    robot->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));

    Card upcard(Card::RANK_JACK, Card::SUIT_HEARTS);
    string trump = Card::SUIT_HEARTS;

    robot->add_and_discard(upcard); //discard dJ
    Card highest_1 = robot->play_card(upcard, trump);
    ASSERT_EQUAL(highest_1, Card(Card::RANK_JACK, Card::SUIT_HEARTS));

    delete robot;
}

TEST(test_player_add_and_discard_normal_smallup) {
    // Create players
    Player * robot = Player_factory("Robot", "Simple");

    robot->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));

    Card upcard(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    string trump = Card::SUIT_DIAMONDS;

    robot->add_and_discard(upcard); //discard upcard
    Card highest_1 = robot->play_card(upcard, trump);
    ASSERT_EQUAL(highest_1, Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));

    delete robot;
}

TEST_MAIN()
