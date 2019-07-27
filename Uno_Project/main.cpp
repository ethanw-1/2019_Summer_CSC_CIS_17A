
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <cstring>
#include "UnoCard.h"
#include "UnoDeck.h"

using namespace std;

void UnoCard::setValue(int value) {
    this->value = value;
}

void UnoCard::setColor(string color) {
    this->color = color;
}

int UnoCard::getValue() {
    return this->value = value;
}

string UnoCard::getColor() {
    return this->color = color;
}

UnoCard::UnoCard(int value, string color) {
	this->color = color;
	this->value = value;
}

UnoCard::UnoCard() {

}

//19 Red, 19 Green, 19 Blue, 19 Yellow
//76 Number Cards, 8 Reverse Cards, 8 Skip Cards, 
//8 Draw Two Cards, 4 Draw 4, 4 Wild

//class ReverseCards : public UnoCard {
//};

//class SkipCards : public UnoCard {
//};

//class DrawTwoCards : public UnoCard {
//};

//class WildCards : public UnoCard {
//};



UnoDeck::UnoDeck() {
    this->deck = new UnoCard*[108];
    cardCount = 0;
	this->index = 0;
    // initialize the deck here
}

void UnoDeck::shuffle() {
    for (int i = 0; i < 76; i++) {
        int random = i + (rand() % (76 - i));
        swap(deck[i], deck[random]);
    }
}

UnoCard* UnoDeck::deal() {
	index++;
	cardCount--;
	return this->deck[this->index - 1];
}

UnoCard* UnoDeck::dealCardAt(int i) {
	UnoCard* temp = getCardAt(i - 1);
	deck[i - 1] = deck[cardCount - 1];
	deck[cardCount - 1] = nullptr;
	cardCount--;
	return temp;
}

void UnoDeck::addCard(UnoCard* unoCard) {
	this->deck[cardCount] = unoCard;
	cardCount++;
}

UnoCard** UnoDeck::getDeck() {
    return this->deck;
}

UnoCard* UnoDeck::getTopCard() {
	return this->deck[this->cardCount - 1];
}

UnoCard* UnoDeck::getCardAt(int i) {
	return deck[i];
}

void UnoDeck::printHand() {
    for (int i = 0; i < cardCount; i++) {
        cout << i + 1 << ". " << this->getCardAt(i)->getColor() << this->getCardAt(i)->getValue() << endl;
    }
}

bool UnoDeck::checkHand(UnoDeck* discard_deck) {

    for (int i = 0; i < cardCount; i++) {
		if (this->getCardAt(i)->getColor() == discard_deck->getTopCard()->getColor() || this->getCardAt(i)->getValue() == discard_deck->getTopCard()->getValue()) {
			return true;
		}
    }
    return false;

}

bool UnoDeck::checkPlace(int place, UnoDeck* discard_deck) {
    if (this->getCardAt(place - 1)->getColor() == discard_deck->getTopCard()->getColor() || this->getCardAt(place - 1)->getValue() == discard_deck->getTopCard()->getValue()) {
        return true;
    }
    return false;
}

void UnoDeck::placeCard(int place, int discard_deck_index, UnoDeck* discard_deck) {
    discard_deck->getCardAt(discard_deck_index)->setColor(this->getCardAt(place)->getColor());

}

int UnoDeck::getIndex() {
	return index;
}

bool UnoDeck::isEmpty() {
	return cardCount == 0;
}

UnoDeck::~UnoDeck() {
	for (int i = 0; i < 108; i++) {
		delete deck[i];
	}
    delete[] deck;
}


///////////////////////////////////////////////////////////////////////////

int main() {

    UnoDeck* deck = new UnoDeck();
   

    int value = 0;
    string color = "Red ";

    for (int i = 0; i < 76; i++) { //Sets the values for starting deck

        if (i == 10 || i == 29 || i == 48 || i == 67)
            value = 1;
        if (i == 19 || i == 38 || i == 57 || i == 76)
            value = 0;

        if (i > 18) {
            color = "Green ";
            if (i > 18 + 19) {
                color = "Blue ";
                if (i > 18 + 19 + 19) {
                    color = "Yellow ";
                }
            }
        }
		deck->addCard(new UnoCard(value, color));
        value++;

    }

    deck->shuffle();


    UnoDeck* player1_hand = new UnoDeck();
    UnoDeck* player2_hand = new UnoDeck();
    UnoDeck* discard_deck = new UnoDeck();


    bool restart = true;
    bool check = 0;


	for (int i = 0; i < 7; i++) {
		player1_hand->addCard(deck->deal());
		player2_hand->addCard(deck->deal());
	}
    int place;
    
    int discard_deck_index = 0;
    int deck_index = 14;
    int player1_hand_index = 7;
    int player2_hand_index = 7;


    discard_deck->addCard(new UnoCard(deck->getDeck()[14]->getValue(), deck->getDeck()[14]->getColor()));

    // cout << discard_deck->getDeck()[discard_deck_index]->getColor() << discard_deck->getDeck()[discard_deck_index]->getValue() << " is starting card" << endl << endl;


    ///////////////// Player 1
	while (true) {
		cout << endl << discard_deck->getTopCard()->getColor() << discard_deck->getTopCard()->getValue() << " is live card" << endl << endl;

		if (player1_hand->checkHand(discard_deck) == true) {
			player1_hand->printHand();
			cout << endl << "Player 1, which card do you want to play? " << endl;
			cin >> place;
			if (place == -1)
				break;

			check = player1_hand->checkPlace(place, discard_deck);
			while (check == 0) {
				cout << "Invalid value, Enter new card" << endl;
				cin >> place;
				check = player1_hand->checkPlace(place, discard_deck);
			}

			discard_deck->addCard(player1_hand->dealCardAt(place));
			player1_hand->printHand();
		}
		else {

			cout << endl << "Player 1, no valid cards. +1 to your deck" << endl << endl;

			player1_hand->addCard(deck->deal());
		}

		if (player1_hand->isEmpty()) {
			cout << "Player 1 wins!" << endl;
			break;
		}


		///////////////// Player 2

		cout << discard_deck->getTopCard()->getColor() << discard_deck->getTopCard()->getValue() << " is live card" << endl << endl;


		if (player2_hand->checkHand(discard_deck) == true) {
			player2_hand->printHand();
			cout << endl << "Player 2, which card do you want to play? " << endl;
			cin >> place;
			if (place == -1)
				break;

			check = player2_hand->checkPlace(place, discard_deck);
			while (check == 0) {
				cout << "Invalid value, Enter new card" << endl;
				cin >> place;
				check = player2_hand->checkPlace(place, discard_deck);
			}

			discard_deck->addCard(player2_hand->dealCardAt(place));
			player2_hand->printHand();
		}
		else {

			cout << endl << "Player 2, no valid cards. +1 to your deck" << endl << endl;

			player2_hand->addCard(deck->deal());
		}
		if (player2_hand->isEmpty()) {
			cout << "Player 2 wins!" << endl;
			break;
		}
	}



    delete discard_deck;
    delete player1_hand;    
    delete player2_hand;
    delete deck;
    
    return 0;
}

