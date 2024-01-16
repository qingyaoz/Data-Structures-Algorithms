// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <string>
#include "Card.h"
// add any necessary #include or using directives here

// rank and suit names -- do not remove these
constexpr const char* const Card::RANK_TWO;
constexpr const char* const Card::RANK_THREE;
constexpr const char* const Card::RANK_FOUR;
constexpr const char* const Card::RANK_FIVE;
constexpr const char* const Card::RANK_SIX;
constexpr const char* const Card::RANK_SEVEN;
constexpr const char* const Card::RANK_EIGHT;
constexpr const char* const Card::RANK_NINE;
constexpr const char* const Card::RANK_TEN;
constexpr const char* const Card::RANK_JACK;
constexpr const char* const Card::RANK_QUEEN;
constexpr const char* const Card::RANK_KING;
constexpr const char* const Card::RANK_ACE;
constexpr const char* const Card::SUIT_SPADES;
constexpr const char* const Card::SUIT_HEARTS;
constexpr const char* const Card::SUIT_CLUBS;
constexpr const char* const Card::SUIT_DIAMONDS;

// add your code below


// NOTE: We HIGHLY recommend you check out the operator overloading
// tutorial in the project spec before implementing
// the following operator overload functions:
//   operator<<
//   operator<
//   operator<=
//   operator>
//   operator>=
//   operator==
//   operator!=

//EFFECTS Initializes Card to the Two of Spades
Card::Card() {
    rank = RANK_TWO;
    suit = SUIT_SPADES;
}

//REQUIRES rank is one of "Two", "Three", "Four", "Five", "Six", "Seven",
//  "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"
//  suit is one of "Spades", "Hearts", "Clubs", "Diamonds"
//EFFECTS Initializes Card to specified rank and suit
Card::Card(const std::string &rank_in, const std::string &suit_in) {
    rank = rank_in;
    suit = suit_in;
}

//EFFECTS Returns the rank
std::string Card::get_rank() const{
    return rank;
}

//EFFECTS Returns the suit.  Does not consider trump.
std::string Card::get_suit() const{
    return suit;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns the suit
//HINT: the left bower is the trump suit!
std::string Card::get_suit(const std::string &trump) const{
    if (is_left_bower(trump)) {
        return trump;
    }
    return suit;
    }

//EFFECTS Returns true if card is a face card (Jack, Queen, King or Ace)
bool Card::is_face_or_ace() const{
    if (get_rank() == RANK_JACK  ||
        get_rank() == RANK_QUEEN ||
        get_rank() == RANK_KING  ||
        get_rank() == RANK_ACE) {
        return true;
    }
    return false;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if card is the Jack of the trump suit
bool Card::is_right_bower(const std::string &trump) const{
    if(get_rank() == RANK_JACK && get_suit() == trump) {
        return true;
    }
    else {
        return false;
    }
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if card is the Jack of the next suit
bool Card::is_left_bower(const std::string &trump) const{
    if(rank != RANK_JACK) {
        return false;
    }
    else {
        if(suit == SUIT_SPADES) {
            return trump == SUIT_CLUBS;
        }
        else if (suit == SUIT_CLUBS) {
            return trump == SUIT_SPADES;
        }
        else if (suit == SUIT_HEARTS) {
            return trump == SUIT_DIAMONDS;
        }
        else {
            return trump == SUIT_HEARTS ;
        }
    }
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if the card is a trump card.  All cards of the trump
// suit are trump cards.  The left bower is also a trump card.
bool Card::is_trump(const std::string &trump) const{
    if(is_left_bower(trump)) {
        return true;
    }
    return suit == trump;
}

//EFFECTS Returen a num index of rank to compare two rank
int rank_index (const std::string &rank) {
    for (int index = 0; index < NUM_RANKS; index++) {
        if (RANK_NAMES_BY_WEIGHT[index] == rank) {
            return index;
        }
    }
    return -1;
}

//EFFECTS Returen a num index of suit to compare two suit
int suit_index (const std::string &suit) {
    for (int index = 0; index < NUM_SUITS; index++) {
        if (SUIT_NAMES_BY_WEIGHT[index] == suit) {
            return index;
        }
    }
    return -1;
}

//EFFECTS Returns true if lhs is lower value than rhs.
//  Does not consider trump.
bool operator<(const Card &lhs, const Card &rhs) {
    if (rank_index(lhs.get_rank()) < rank_index(rhs.get_rank())) {
        return true;
    }
    else if (rank_index(lhs.get_rank()) == rank_index(rhs.get_rank())) {
        if (suit_index(lhs.get_suit()) < suit_index(rhs.get_suit())) {
            return true;
        }
        else return false;
    }
    else return false;
}

//EFFECTS Returns true if lhs is lower value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator<=(const Card &lhs, const Card &rhs) {
    if (rank_index(lhs.get_rank()) < rank_index(rhs.get_rank())) {
        return true;
    }
    else if (rank_index(lhs.get_rank()) == rank_index(rhs.get_rank())) {
        return(suit_index(lhs.get_suit()) <= suit_index(rhs.get_suit()));
    } else return false;
}

//EFFECTS Returns true if lhs is higher value than rhs.
//  Does not consider trump.
bool operator>(const Card &lhs, const Card &rhs) {
    if (rank_index(lhs.get_rank()) > rank_index(rhs.get_rank())) {
        return true;
    }
    else if (rank_index(lhs.get_rank()) == rank_index(rhs.get_rank())) {
        if (suit_index(lhs.get_suit()) > suit_index(rhs.get_suit())) {
            return true;
        }
        else return false;
    }
    else return false;
}

//EFFECTS Returns true if lhs is higher value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator>=(const Card &lhs, const Card &rhs) {
    if (rank_index(lhs.get_rank()) > rank_index(rhs.get_rank())) {
       return true;
    } else if (rank_index(lhs.get_rank()) == rank_index(rhs.get_rank())) {
        return (suit_index(lhs.get_suit()) >= suit_index(rhs.get_suit()));
    }
    else return false;
}

//EFFECTS Returns true if lhs is same card as rhs.
//  Does not consider trump.
bool operator==(const Card &lhs, const Card &rhs) {
    if (rank_index(lhs.get_rank()) == rank_index(rhs.get_rank()) &&
        suit_index(lhs.get_suit()) == suit_index(rhs.get_suit())) {
        return true;
    }
    else return false;
}

//EFFECTS Returns true if lhs is not the same card as rhs.
//  Does not consider trump.
bool operator!=(const Card &lhs, const Card &rhs) {
    if (rank_index(lhs.get_rank()) != rank_index(rhs.get_rank()) ||
        suit_index(lhs.get_suit()) != suit_index(rhs.get_suit())) {
        return true;
    }
    else return false;
}

//REQUIRES suit is a valid suit
//EFFECTS returns the next suit, which is the suit of the same color
std::string Suit_next(const std::string &suit) {
    if (suit == Card::SUIT_SPADES) {
        return Card::SUIT_CLUBS;
    }
    else if (suit == Card::SUIT_CLUBS) {
        return Card::SUIT_SPADES;
    }
    else if (suit == Card::SUIT_HEARTS) {
        return Card::SUIT_DIAMONDS;
    }
    else return Card::SUIT_HEARTS;
}

//EFFECTS Prints Card to stream, for example "Two of Spades"
std::ostream & operator<<(std::ostream &os, const Card &card) {
    os << card.get_rank()<< " of " << card.get_suit();
    return os;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses trump to determine
// order, as described in the spec.
 
// a <  b
bool Card_less(const Card &a, const Card &b, const std::string &trump) {
    if (a.is_right_bower(trump) == false &&
          b.is_right_bower(trump)) {
        return true;
      }
      else if (a.is_right_bower(trump) == false &&
               b.is_right_bower(trump) == false &&
               b.is_left_bower(trump)) {
        return true;
      }
      else if (a.is_right_bower(trump) == false &&
                a.is_left_bower(trump) == false &&
                b.is_right_bower(trump) == false &&
                b.is_left_bower(trump) == false)  {
            if (b.get_suit() == trump &&
               a.get_suit() != trump) {
                     return true;
                 }
            else if (suit_index(b.get_suit()) == suit_index(a.get_suit()) &&
                     b.get_suit() == trump) {
                if (rank_index(a.get_rank()) < rank_index(b.get_rank())) {
                    return true;
                }
                else return false;
            }
            else if (suit_index(b.get_suit()) == suit_index(a.get_suit()) &&
                     b.get_suit() != trump) {
                if (rank_index(a.get_rank()) < rank_index(b.get_rank())) {
                    return true;
                }
                else if (rank_index(a.get_rank()) == rank_index(b.get_rank()) &&
                         suit_index(a.get_suit()) < suit_index(b.get_suit())) {
                    return true;
                }
                else return false;
            }
            else if (suit_index(b.get_suit()) != suit_index(a.get_suit()) && b.get_suit() != trump && a.get_suit()!= trump){
                if (rank_index(b.get_rank()) >  rank_index(a.get_rank())) {
                    return true;
                }
                else if (rank_index(b.get_rank()) == rank_index(a.get_rank())) {
                    if (suit_index(b.get_suit()) > suit_index(a.get_suit())) {
                        return true;
                    }
                    else return false;
                }
                else return false;
            }
            else return false;
      }
    else return false;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses both the trump suit
//  and the suit led to determine order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const Card &led_card,
               const std::string &trump) {
    if (a.is_right_bower(trump) == false &&
          b.is_right_bower(trump)) {
          return true;
      }
      else if (a.is_right_bower(trump) == false &&
               b.is_right_bower(trump) == false &&
               b.is_left_bower(trump)) {
          return true;
      }
      else if (a.is_right_bower(trump) == false &&
                a.is_left_bower(trump) == false &&
                b.is_right_bower(trump) == false &&
               b.is_left_bower(trump) == false) {
          if(b.get_suit() == trump &&
             a.get_suit() != trump){
              return true;
          }
          else if(b.get_suit() != trump && a.get_suit() != trump){
              if (suit_index(b.get_suit()) == suit_index(led_card.get_suit()) &&
                  suit_index(b.get_suit()) != suit_index(a.get_suit())) {
                  return true;
              }
              else if (suit_index(b.get_suit()) == suit_index(led_card.get_suit()) &&
                       suit_index(b.get_suit()) == suit_index(a.get_suit())) {
                  if (rank_index(b.get_rank()) > rank_index(a.get_rank())) {
                      return true;
                  }
                  else return false;
              }
              else if (suit_index(b.get_suit()) != suit_index(led_card.get_suit()) &&
                       suit_index(b.get_suit()) == suit_index(a.get_suit())) {
                  if (rank_index(b.get_rank()) > rank_index(a.get_rank())) {
                      return true;
                  }
                  else if (rank_index(b.get_rank()) == rank_index(a.get_rank())) {
                      if (suit_index(b.get_suit()) > suit_index(a.get_suit())) {
                          return true;
                      }
                      else return false;
                  }
                  else return false;
              }
              else if (suit_index(b.get_suit()) != suit_index(led_card.get_suit()) &&
                       suit_index(b.get_suit()) != suit_index(a.get_suit()) &&
                       suit_index(a.get_suit()) != suit_index(led_card.get_suit())) {
                  if(rank_index(b.get_rank()) > rank_index(a.get_rank())) {
                      return true;
                  }
                  else if (rank_index(b.get_rank()) == rank_index(a.get_rank())) {
                      if (suit_index(b.get_suit()) > suit_index(a.get_suit())) {
                          return true;
                      }
                      else return false;
                  }
                  else return false;
              }
              else return false;
      }
          else if (b.get_suit() == trump && a.get_suit() == trump) {
              if (rank_index(b.get_rank())> rank_index(a.get_rank())) {
                  return true;
              }
              else return false;
              
          }
          
           else   return false;
      }
       else return false;
}

