/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   UnoCard.h
 * Author: Ethan
 *
 * Created on July 25, 2019, 7:07 PM
 */


#ifndef UnoCard_H
#define UnoCard_H

#include <string>
#include <iostream>
using namespace std;

class UnoCard {
    int value;
    string color;
    

public:
    UnoCard(int, string);
    UnoCard();
    void setValue(int value);
    void setColor(string color);

    int getValue();
    string getColor();
    

};





#endif /* UnoCard_H */

