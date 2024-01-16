// Project UID 1d9f47bfc76643019cfbf037641defe1
#include "Card.h"
#include <array>
#include <string>
#include "Pack.h"

// EFFECTS: Initializes the Pack to be in the following standard order:
//          the cards of the lowest suit arranged from lowest rank to
//          highest rank, followed by the cards of the next lowest suit
//          in order from lowest to highest rank, and so on.
// NOTE: The standard order is the same as that in pack.in.
// NOTE: Do NOT use pack.in in your implementation of this function
Pack::Pack() {
 //   cards = {};
    int i = 0;
    next = 0;
    for (int j = 0; j < NUM_SUITS; j++) {
      for (int k = 7; k < NUM_RANKS; k++) {
        Card card = Card(RANK_NAMES_BY_WEIGHT[k], SUIT_NAMES_BY_WEIGHT[j]);
        cards[i++] = card;
      }
    }
  }

// REQUIRES: pack_input contains a representation of a Pack in the
//           format required by the project specification
// ODIFIES: pack_input
// EFFECTS: Initializes Pack by reading from pack_input.
Pack::Pack(std::istream& pack_input) {
    std::string nouse;
    std::string rank;
    std::string suit;
    next = 0;
    for (int i = 0; pack_input >> rank; i ++) {
        pack_input >> nouse >> suit;
        cards[i] = Card(rank, suit);
    }
}


// REQUIRES: cards remain in the Pack
// EFFECTS: Returns the next card in the pack and increments the next index
Card Pack::deal_one() {
    return cards[(next++) % PACK_SIZE];
}

// EFFECTS: Resets next index to first card in the Pack
void Pack::reset() {
    next = 0;
}

// EFFECTS: Shuffles the Pack and resets the next index. This
//          performs an in shuffle seven times. See
//          https://en.wikipedia.org/wiki/In_shuffle.
void Pack::shuffle() {
    // Card temp[PACK_SIZE];
    for (int i = 0; i < 7; i ++) {
        std::array<Card, PACK_SIZE> temp;
        for (int j = 0; j < PACK_SIZE; j ++) {
            if (j % 2 != 0) {
               temp[j] = cards[(j - 1)/2];
            }
            else if( j % 2 == 0){
                temp[j] = cards[12 + j/2];
            }
        }
        cards = temp;
        reset();
    }
}

// EFFECTS: returns true if there are no more cards left in the pack
bool Pack::empty() const {
    if (next == PACK_SIZE) {
        return true;
    }
    else {
        return false;
    }
}

