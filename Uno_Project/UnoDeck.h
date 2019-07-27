/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   UnoDeck.h
 * Author: Ethan
 *
 * Created on July 25, 2019, 7:19 PM
 */

#ifndef UNODECK_H
#define UNODECK_H

#include <string>
#include <iostream>
using namespace std;


class UnoDeck {
    UnoCard** deck;
    int cardCount;
    int index;

public:

    UnoDeck();
    void shuffle();
    UnoCard* deal();
	UnoCard* dealCardAt(int i);
    UnoCard** getDeck();
    ~UnoDeck();

    void placeCard(int, int, UnoDeck*);
    void printHand();
    bool checkHand(UnoDeck*);
    bool checkPlace(int, UnoDeck*);
	bool isEmpty();

	int getIndex();

	UnoCard* getTopCard();
	UnoCard* getCardAt(int i);
	void addCard(UnoCard* unoCard);
};



#endif /* UNODECK_H */
