// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <string>
#include "Player.h"
#include <vector>

using namespace std;

class SimplePlayer : public Player {
  private:
  string name;
  vector<Card> own_cards; // to store cards I have

  public:
  SimplePlayer(const string &name_in) : name(name_in) {}

  //EFFECTS returns player's name
  virtual const std::string & get_name() const {
    return name;
  }

  //REQUIRES player has less than MAX_HAND_SIZE cards
  //EFFECTS  adds Card c to Player's hand
  virtual void add_card(const Card &c) {
    assert(own_cards.size() < MAX_HAND_SIZE);

    
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
  // Invalid strategy if we get here
  assert(false);
  return nullptr;
}

//EFFECTS: Prints player's name to os
std::ostream & operator<<(std::ostream &os, const Player &p) {
  assert(false);
}