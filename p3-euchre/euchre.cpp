// Project UID 1d9f47bfc76643019cfbf037641defe1
#include "Player.h"
#include "Pack.h"

#include <fstream>
#include <iostream>
#include <cstring>
#include <cassert>
using namespace std;

class Game {
    private:
    std::vector<Player*> players;
    Pack pack;
    int end_points = 0;
    bool shuffle_or_not;
    int hands = 0;
    // first for players 0 & 2, second for players 1 & 3
    int rec_points[2] = {0, 0}; 
    // team with higher points
    int potential_winner;

    // REQUIRES: Valid pack
    // MODIFIES: Pack order
    // EFFECTS: Shuffle pack as required.
    void shuffle() {
        if (shuffle_or_not) {
            pack.shuffle();
        }
        pack.reset();
    }

    // REQUIRES: Input a index of dealer, [0, 4)
    // MODIFIES: pack, players' hand added
    // EFFECTS: Deal 3-2-3-2 cards then 2-3-2-3 cards. (odd: 2+1; even: 2+0)
    //          The player to the left of the dealer receives the first batch.
    void deal(const int dealer_in) {
        assert(dealer_in >= 0 && dealer_in < 4);

        for (int deal_one = 1; deal_one < 5; ++deal_one) {
            for (int num_card = 1; num_card <= (2 + deal_one%2); ++num_card) {
                players[(deal_one+dealer_in)%4]->add_card(pack.deal_one());
            }
        }

        for (int deal_two = 1; deal_two < 5; ++deal_two) {
            for (int num_card = 1; num_card <= 2+(deal_two+1)%2; ++num_card) {
                players[(deal_two+dealer_in)%4]->add_card(pack.deal_one());
            }
        }

        cout << players[dealer_in]->get_name() << " deals" << endl;
    }

    // REQUIRES: Input a valid upcard, index of dealer
    // MODIFIES: order_up (0 or 1), order_up_suit
    // EFFECTS: Finish a hand and output results.
    void make_trump(const Card upcard, const int dealer,
                    int &order_up, string &order_up_suit) {
        assert(dealer < 4);

        bool second_round = true;
        for (int i = 1; i < 5; ++i) {
            int position = (dealer + i) % 4;
            if (players[position]->make_trump(upcard, position == dealer,
                                              1, order_up_suit)) {
                order_up = position % 2;
                second_round = false;
                cout << players[position]->get_name() 
                     << " orders up " << order_up_suit << endl;
                
                //  the dealer is given the option
                players[dealer]->add_and_discard(upcard);
                break;
            } else {
                cout << players[position]->get_name() << " passes" << endl;
            }
        }

        if (second_round) {
            for (int i = 1; i < 5; ++i) {
                int position = (dealer + i) % 4;
                if (players[position]->make_trump(upcard, position == dealer,
                                                  2, order_up_suit)) {
                    order_up = position % 2;
                    cout << players[position]->get_name() 
                         << " orders up " << order_up_suit << endl;
                    break;
                } else {
                    cout << players[position]->get_name() << " passes" << endl;
                }
            }
        }
        cout << "\n";
    }

    // REQUIRES: Input a valid learder, trump
    // MODIFIES: num of tricks, leader
    // EFFECTS: 
    void trick_taking(int * trick_num, int &leader, string trump/* ... */) {
        assert(leader < 4);

        Card leading = players[leader]->lead_card(trump);
        cout << leading << " led by " << players[leader]->get_name() << endl;
       
        int won_trick = leader;
        Card higher_value = leading;

        for (int i = 1; i < 4; ++i) {
            Card played_card = players[(leader+i) % 4]->play_card(leading, trump);
            cout << played_card << " played by " 
                 << players[(leader+i) % 4]->get_name() << endl;
            if (Card_less(higher_value, played_card, leading, trump)) {
                higher_value = played_card;
                won_trick = (leader+i) % 4;
            }
        }

        cout << players[won_trick]->get_name() << " takes the trick" << endl;
        cout << "\n";
        trick_num[won_trick % 2] += 1;
        leader = won_trick;
    }

    // REQUIRES: Input a valid array[2] of trick numbers, index of who order up: 0 or 1
    // MODIFIES: rec_points, lead team
    // EFFECTS: Award points to the winner of hand, output results of this hand.
    void scoring_and_results(const int* trick_num, const int order_up) {
        assert(trick_num[0] <= 5 || trick_num[1] <= 5);
        assert(order_up < 2);

        int winner;
        if (trick_num[0] > trick_num[1]) {
            winner = 0;
        } else {
            winner = 1;
        }

        cout << players[winner]->get_name() << " and " 
             << players[winner+2]->get_name() << " win the hand" << endl;

        
        if (winner == order_up) {
            if (trick_num[order_up] == 5) {
                rec_points[winner] += 2;
                cout << "march!" << endl;
            } else {
                rec_points[winner] += 1;
            }
        } else {
            rec_points[winner] += 2;
            cout << "euchred!" << endl;
        }

        cout << players[0]->get_name() << " and " << players[2]->get_name() 
             << " have " << rec_points[0] << " points" << endl;
        cout << players[1]->get_name() << " and " << players[3]->get_name() 
             << " have " << rec_points[1] << " points" << endl;
        cout << "\n"; // Could "endl" be used here? lobster/test can't?

        // who win the hand may not be in the lead, since points are cumulative
        // what happens if equal points? *******
        if (rec_points[0] >= rec_points[1]) {
            potential_winner = 0;
        } else {
            potential_winner = 1;
        }
    }

    // REQUIRES: Input a index of dealer, [0, 4)
    // MODIFIES: rec_points
    // EFFECTS: Finish a hand and output results.
    void play_hand() {
        int dealer = hands % 4;
        int trick_num[2] = {0, 0};
        int order_up; // 0 or 1
        string order_up_suit;
        // Trick Taking: for the first trick, the eldest hand leads.
        int leader = (dealer + 1) % 4;

        cout << "Hand " << hands << endl;
        shuffle();
        deal(dealer); // is deal(hands % 4) okay?
        Card upcard = pack.deal_one();
        cout << upcard << " turned up" << endl;

        // Pass by reference, cause we need new infor about order_up
        make_trump(upcard, dealer, order_up, order_up_suit); 
        
        // Once the trump has been determined, five tricks are played.
        for (int i = 0; i < 5; ++i) {
            trick_taking(trick_num, leader, order_up_suit);
        }
        
        scoring_and_results(trick_num, order_up);
    }
    // ...

    public:
    Game(Pack pack_in, bool shuffle_in, int points_in, vector<Player*> players_in) {
        pack = pack_in;
        shuffle_or_not = shuffle_in;
        end_points = points_in;
        players = players_in;
    }

    void play() {
        while (rec_points[potential_winner] < end_points) {
            play_hand();
            hands++;
        }

        cout << players[potential_winner]->get_name() << " and "
             << players[potential_winner+2]->get_name() << " win!" << endl;
    }
};


// MODIFIES: Delete player in players
// EFFECTS: players will be empty
void see_you(vector<Player*> players) {
    for (size_t i = 0; i < players.size(); ++i) {
        delete players[i];
    }
}

int main(int argc, char **argv){

    // ********************* Prepare Game *********************
    bool shuffle_in;
    int points_in;
    vector<Player*> players_in;

    // Error Checking: Arguments number, point range, shuffle card 
    if ((argc != 12) || (stoi(argv[3]) < 1 || stoi(argv[3]) > 100)) {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
             << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
             << "NAME4 TYPE4" << endl;
        exit(1);
    } else {
        points_in = stoi(argv[3]);
    }

    ifstream fin;
    fin.open(argv[1]);
    // Error Checking: Open file
    if(!fin.is_open()) {
        cout << "Error opening " << argv[1] << endl;
        exit(1);
    }
    Pack pack_in(fin);

    // Input shuffle status & Error Checking
    if (strcmp(argv[2], "shuffle") == 0) {
        shuffle_in = true;
    } else if (strcmp(argv[2], "noshuffle") == 0) {
        shuffle_in = false;
    } else {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
             << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
             << "NAME4 TYPE4" << endl;
        exit(1);
    }

    // Input Players & Error Checking: Player type
    for (int i = 5; i < 12; i = i + 2) {
        if (strcmp(argv[i], "Simple") == 1 && strcmp(argv[i], "Human") == 1) {
            cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
             << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
             << "NAME4 TYPE4" << endl;
            exit(1);
        } else {
            Player *new_player = Player_factory(argv[i-1], argv[i]);
            players_in.push_back(new_player);
        }
    }
    
    
    // ********************* Begin Game *********************
    
    // First, print the executable and all arguments on the first line.
    for (int i = 0; i < 12; ++i) {
        cout << argv[i] << " ";
    }
    cout << endl;
    Game ready_go(pack_in, shuffle_in, points_in, players_in);
    ready_go.play();

    see_you(players_in); // delete 
}
