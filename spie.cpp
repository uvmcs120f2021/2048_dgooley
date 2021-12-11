#include "spie.h"
#include <time.h>
using namespace std;

SPIE_Game() {
    srand(time(NULL));
    winning_numbers.clear();
    add_winning_number();
    add_winning_number();
}

bool SPIE_Game::add_winning_number() {
    if (winning_numbers.size() == MAX_NUMBERS) {
        return false;
    }
    int new_number = rand() % MAX_NUMBERS + 1;
    for (int i = 0; i < winning_numbers.size(); ++i) {
        if (new_number == winning_numbers[i]) {
            // Number is already a winning number.
            // Must choose a new number and start again.
            new_number = rand() % MAX_NUMBERS + 1;
            i = -1;
        }
    }
    return true;
}

char SPIE_Game::get_player_choice(ostream &outs, istream &ins) {
    char choice;
    print_options(outs);
    ins >> choice;
    while (choice != ('s' || 'p' || 'i' || 'e')) {
        outs << endl << "Invalid option. " << endl;
        print_options(outs);
        ins >> choice;
    }
}

bool SPIE_Game::matches_winning_number(int roll) const {
    for (int w = 0; w < winning_numbers.size(); ++w) {
        if (roll == winning_numbers[w]) {
            return true;
        }
    }
    return false;
}

void SPIE_Game::print_options(ostream &outs) {
    outs << "Press (s) to scramble, (p) to play, (i) for info, or (e) to exit: ";
}

void SPIE_Game::print_rules(ostream &outs) {
    outs << "Rules of SPIE Game:" << endl;
    outs << "If you roll the dice and match a winning number, you will get five points." << endl;
    outs << "If you roll the dice and do not match the winning numbers, you will lose one point." << endl;
    outs << "If you roll a 12 or a 2, a winning number will be added." << endl;
    outs << "If you scramble, you will roll the dice five times. If any of your dice rolls match a winning number, that number will be replaced in the winning numbers list" << endl;
    outs << "If you run out of points, you lose." << endl;
}

void SPIE_Game::print_winning_numbers(ostream &outs) const {
    outs << "The winning numbers are: ";
    for (int i = 0; i < winning_numbers.size(); ++i) {
        outs << winning_numbers[i];
        if (i < winning_numbers.size() - 1) {
            outs << ", ";
        }
    }
    outs << endl;
}

int SPIE_Game::roll_dice() {
    return (rand() % 6) + (rand() % 6);
}

void SPIE_Game::scramble(ostream &outs) {
    vector<int> dice_rolls;
    outs << "You rolled: ";
    for (int i = 0; i < 5; ++i) {
        dice_rolls.push_back(roll_dice());
        outs << dice_rolls[i];
        if (i < 4) {
            outs << ", ";
        }
    }
    outs << endl;

    int replacements = 0;
    for (int w = 0; w < winning_numbers.size(); ++w) {
        for (int r = 0; r < dice_rolls.size(); ++r) {
            if (dice_rolls[r] == winning_numbers[w]) {
                winning_numbers.erase(winning_numbers.begin() + w);
                ++replacements;
            }
        }
    }

    outs << "You replaced " << replacements << " winning numbers!" << endl;

    for (int i = 0; i < replacements; ++i) {
        add_winning_number();
    }

    print_winning_numbers(outs);
}