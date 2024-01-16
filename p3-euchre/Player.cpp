// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <string>
#include "Player.h"
#include <vector>
#include <algorithm>

using namespace std;

class SimplePlayer : public Player {
  private:
  string name;
  vector<Card> own_cards; // to store cards I have
  //debug
  void print_hand() const {
  for (size_t i=0; i < own_cards.size(); ++i)
    cout << "Simple player " << name << "'s hand: "
         << "[" << i << "] " << own_cards[i] << "\n";
  }

  public:
  SimplePlayer(const string &name_in) : name(name_in) {}

  //EFFECTS returns player's name
  virtual const std::string & get_name() const {
    return name;
  }

  //REQUIRES player has less than MAX_HAND_SIZE cards
  //EFFECTS  adds Card c to Player's hand
  virtual void add_card(const Card &c) {
    assert(own_cards.size() <= MAX_HAND_SIZE);
    own_cards.push_back(c);
  }

  //REQUIRES round is 1 or 2
  //MODIFIES order_up_suit
  //EFFECTS If Player wishes to order up a trump suit then return true and
  //  change order_up_suit to desired suit.  If Player wishes to pass, then do
  //  not modify order_up_suit and return false.
  virtual bool make_trump(const Card &upcard, bool is_dealer,
                          int round, std::string &order_up_suit) const {
    assert(round == 1 || round == 2);

    // Prepare
    int face_or_A = 0;
    string trump_suit = upcard.get_suit();
    // Check round, implement difference
    if (round == 2) {
      trump_suit = Suit_next(trump_suit);
      // Round 1: Simple Player does not consider whether they are the dealer
      // Round 2: Dealer will always order up the suit with the same color as the upcard
      if (is_dealer) {
        order_up_suit = trump_suit;
        return true;
      }
    }
    // Count
    for (const Card &card: own_cards) {
      if (card.is_face_or_ace() && card.is_trump(trump_suit)) {
        face_or_A = face_or_A + 1;
      }
    }
    // for round 1: >= 2 cards; for round 2: >= 1 cards
    // cards + round should >= 3
    if ((round == 1 && face_or_A >= 2) || (round == 2 && face_or_A >= 1)) {
      order_up_suit = trump_suit;
      return true;
    } else {
      return false;
    }
  }
  
  //REQUIRES Player has at least one card
  //EFFECTS  Player adds one card to hand and removes one card from hand.
  virtual void add_and_discard(const Card &upcard) {
    assert(own_cards.size() >= 1);

    add_card(upcard);
    sort(own_cards.begin(), own_cards.end(), 
        [&](const Card &lhs, const Card &rhs) { // [&]?
            return !Card_less(lhs, rhs, upcard.get_suit());
        });
    own_cards.pop_back();

    // meaningful?
    assert(own_cards.size() <= MAX_HAND_SIZE);
  }

  //REQUIRES Player has at least one card, trump is a valid suit
  //EFFECTS  Leads one Card from Player's hand according to their strategy
  //  "Lead" means to play the first Card in a trick.  The card
  //  is removed the player's hand.
  virtual Card lead_card(const std::string &trump) {

    // Assume only have trump cards
    bool all_trump = true;
    for (const Card &card: own_cards) {
      // As long as one card is not trump, not all trump
      if (card.get_suit() != trump) {
        all_trump = false;
      }
    }

    if (all_trump) {
      sort(own_cards.begin(), own_cards.end(), 
        [&](const Card &lhs, const Card &rhs) {
            return Card_less(lhs, rhs, trump);
        });
    } else {
      sort(own_cards.begin(), own_cards.end(), [&](const Card &lhs, const Card &rhs) {
          if (!lhs.is_trump(trump) && rhs.is_trump(trump)) {return false;}
          else if (lhs.is_trump(trump) && !rhs.is_trump(trump)) {return true;}
            return Card_less(lhs, rhs, trump);
        });
    }
    Card play = own_cards.back();
    own_cards.pop_back();
    return play;
  }

  //REQUIRES Player has at least one card, trump is a valid suit
  //EFFECTS  Plays one Card from Player's hand according to their strategy.
  //  The card is removed from the player's hand.
  virtual Card play_card(const Card &led_card, const std::string &trump) {
    assert(own_cards.size() >= 1);

    string follow_suit = led_card.get_suit(trump);

    // Whether a Simple Player can follow suit
    bool same_suit = false;
    for (const Card &card: own_cards) {
      if (card.get_suit(trump) == follow_suit) {
        same_suit = true;
      }
    }
    
    if (same_suit) {
      // play the highest card that follows suit -> [low -> high]
      sort(own_cards.begin(), own_cards.end(), [&](const Card &lhs, const Card &rhs) {
            if (lhs.get_suit(trump) == led_card.get_suit(trump) && 
            rhs.get_suit(trump) != led_card.get_suit(trump)) {return false;}
            if (lhs.get_suit(trump) != led_card.get_suit(trump) && 
            rhs.get_suit(trump) == led_card.get_suit(trump)) {return true;}
            return Card_less(lhs, rhs, led_card, trump);
        });
    } else {
      // play the lowest card -> [high -> low]
      sort(own_cards.begin(), own_cards.end(), [&](const Card &lhs, const Card &rhs) {
            return !Card_less(lhs, rhs, trump);
        });
    }
    Card play = own_cards.back();
    own_cards.pop_back();
    return play;
  }
};


class HumanPlayer: public Player {
  private:
  string name;
  vector<Card> hand;

  void print_hand() const {
  for (size_t i=0; i < hand.size(); ++i)
    cout << "Human player " << name << "'s hand: "
         << "[" << i << "] " << hand[i] << "\n";
  }

  public:
  HumanPlayer(const string &name_in) : name(name_in) {}

  //EFFECTS returns player's name
  virtual const std::string & get_name() const override {
    return name;
  }

  //REQUIRES player has less than MAX_HAND_SIZE cards
  //EFFECTS  adds Card c to Player's hand
  virtual void add_card(const Card &c) override {
    assert(hand.size() <= MAX_HAND_SIZE);

    hand.push_back(c);
    sort(hand.begin(), hand.end());
  }

  //REQUIRES round is 1 or 2
  //MODIFIES order_up_suit
  //EFFECTS If Player wishes to order up a trump suit then return true and
  //  change order_up_suit to desired suit.  If Player wishes to pass, then do
  //  not modify order_up_suit and return false.
  virtual bool make_trump(const Card &upcard, bool is_dealer,
                          int round, std::string &order_up_suit) const override {
    assert(round == 1 || round == 2);

    string suit_in;

    print_hand();
    cout << "Human player " << name << ", please enter a suit, or \"pass\":\n";
    cin >> suit_in;

    if (suit_in == "pass") {
      return false;
    } else {
      order_up_suit = suit_in;
      return true;
    }
  }

  //REQUIRES Player has at least one card
  //EFFECTS  Player adds one card to hand and removes one card from hand.
  virtual void add_and_discard(const Card &upcard) override {
    assert(hand.size() >= 1);

    int discard_num;

    print_hand();
    cout << "Discard upcard: [-1]\n";
    cout << "Human player " << name << ", please select a card to discard:\n";
    cin >> discard_num;

    if (discard_num != -1) {
      hand.erase(hand.begin() + discard_num);
      hand.push_back(upcard);
    }
    // else: if discard upcard = didn't pick upcard
    sort(hand.begin(), hand.end());
  }

  //REQUIRES Player has at least one card, trump is a valid suit
  //EFFECTS  Leads one Card from Player's hand according to their strategy
  //  "Lead" means to play the first Card in a trick.  The card
  //  is removed the player's hand.
  virtual Card lead_card(const std::string &trump) override {
    assert(hand.size() >= 1);

    int lead_num;

    print_hand();
    cout << "Human player " << name << ", please select a card:\n";
    cin >> lead_num;

    Card play_card = hand[lead_num];
    hand.erase(hand.begin() + lead_num);
    return play_card;
    // Play a card won't affect rank
  }

  //REQUIRES Player has at least one card, trump is a valid suit
  //EFFECTS  Plays one Card from Player's hand according to their strategy.
  //  The card is removed from the player's hand.
  virtual Card play_card(const Card &led_card, const std::string &trump) override {
    assert(hand.size() >= 1);

    int play_num;

    print_hand();
    cout << "Human player " << name << ", please select a card:\n";
    cin >> play_num;

    Card play_card = hand[play_num];
    hand.erase(hand.begin() + play_num);
    return play_card;
    // Play a card won't affect rank
  }
};

//EFFECTS: Returns a pointer to a player with the given name and strategy
//To create an object that won't go out of scope when the function returns,
//use "return new Simple(name)" or "return new Human(name)"
//Don't forget to call "delete" on each Player* after the game is over
Player * Player_factory(const std::string &name, const std::string &strategy) {
  // We need to check the value of strategy and return 
  // the corresponding player type.
  if (strategy == "Simple") {
    // The "new" keyword dynamically allocates an object.
    return new SimplePlayer(name);
  }
  // Repeat for each other type of Player
  if (strategy == "Human") {
    // The "new" keyword dynamically allocates an object.
    return new HumanPlayer(name);
  }
  // Invalid strategy if we get here
  assert(false);
  return nullptr;
}

//EFFECTS: Prints player's name to os
std::ostream & operator<<(std::ostream &os, const Player &p) {
  os << p.get_name();
  return os;
}
