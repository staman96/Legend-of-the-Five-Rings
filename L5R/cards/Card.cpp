#include <cstring>
#include <stdlib.h>
#include <bits/stdc++.h>
#include "Card.h"

using std::fflush;
using std::string;
using std::cout;
using std::endl;

/*******************************  Card  *****************************/
Card::Card(){
    this-> isTapped = 0;
};

Card::~Card(){

};

string Card::getname(){
    return this->name;
};

int Card::getcost(){
    return this->cost;
};

bool Card::getistap(){
    return isTapped;
};

void Card::setname(string nm){
    this->name = nm;
};

void Card::setcost(int cst){
    this->cost = cst;
};

void Card::setistap(bool tapped){
    this->isTapped = tapped;
};

/**************************************** GreenCard *****************************/

GreenCard::GreenCard()
:Card(){

};

GreenCard::~GreenCard(){

};

int GreenCard::getATKbon(){
    return this->attackBonus;
};

int GreenCard::getDEFbon(){
    return this->defenceBonus;
};

int GreenCard::getMINhon(){
    return this->minimumHonour;
};

int GreenCard::getEFFbon(){
    return this->effectBonus;
};

int GreenCard::getEFFcost(){
    return this->effectCost;
};

string GreenCard::getTXT(){
    return this->cardText;
};

void GreenCard::setATKbon(int atbon){
    this->attackBonus = atbon;
};

void GreenCard::setDEFbon(int dfbon){
    this->defenceBonus = dfbon;;
};

void GreenCard::setMINhon(int minhon){
    this->minimumHonour = minhon;
};

void GreenCard::setEFFbon(int efbon){
    this->effectBonus = efbon;
};

void GreenCard::setEFFcost(int effcost){
    this->effectCost = effcost;
};

void GreenCard::setTXT(string txt){
    this->cardText = txt;
};

/************************************** BlackCard ******************************/

BlackCard::BlackCard()
:Card(){
    this->isRevealed = 0;
};

BlackCard::~BlackCard(){

};

bool BlackCard::getisrev(){
    return isRevealed;
};

void BlackCard::setisrev(bool revealed){
    this->isRevealed = revealed;
};