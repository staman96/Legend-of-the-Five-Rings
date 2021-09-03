#include <bits/stdc++.h>
#include <cstring>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "Card.h"
#include "Personality.h"
#include "../TypeConverter.h"
#include "Item.h"
#include "Follower.h"

using std::fflush;
using std::cout;
using std::endl;

Personality::Personality()
:BlackCard(), isDead(0){
   
};

Personality::~Personality(){
    list <GreenCard *> :: iterator it1;
    for(it1 = gc.begin(); it1 != gc.end(); ++it1){
        delete *it1;
    }
    this->gc.clear();
};

int Personality::getAttack(){
    return this->attack;
};

void Personality::setAttack(int hon){
    this->honour = hon;
};

int Personality::getHonour(){
    return this->honour;
};

void Personality::setHonour(int hon){
    this->honour = hon;
};

int Personality::getDefense(){
    return this->defense;
};

void Personality::setDefense(int def){
    this->defense = def;
};

bool Personality::getIsdead(){
    return this->isDead;
};

void Personality::setIsdead(bool dead){
    this->isDead = dead;
};

list <GreenCard *> & Personality::getFolItem(){
    return this->gc;
};

void Personality::addcard(GreenCard* added){
    this->gc.push_back(added);
    
}

int Personality::totalATK(){ //Total attack of the personality and its followers and items

    int add = attack;
    list <GreenCard*> :: iterator it1;
    for(it1 = gc.begin(); it1 != gc.end(); ++it1){
        add = add + (*it1)->getATKbon(); 
    }
    return add;
}

int Personality::totalDEF(){ //Total deffence of the personality and its followers and items

    int add = defense;
    list <GreenCard*> :: iterator it1;
    for(it1 = gc.begin(); it1 != gc.end(); ++it1){
        add = add + (*it1)->getDEFbon(); 
    }
    return add;
}

int Personality::totalCards(){ //Total cards of followers and items. Each personality can have up to 10 cards
    return this->gc.size();
};

void Personality::printGreenCards(){
    list <GreenCard*> :: iterator it1;
    int counter = 1;
    for(it1 = gc.begin(); it1 != gc.end(); ++it1){
        cout << "       card_no: " << counter++ << " ";
        (*it1)->printCard();
    }
};

int Personality::sacrificeGreenCard(int index){


    /*if index is not valid return -1*/
    if( index < 0 || index >= this->gc.size()) return -1;

    int ATKval;
    list <GreenCard *> :: iterator it;
    it = this->gc.begin();
    advance(it,index);
    ATKval = (*it)->getATKbon();
    delete *it;
    this->gc.remove(*it);
    cout << "Green card's attack value to be reduced " << ATKval << endl;
    return ATKval;
};

int Personality::getType(){ //getType for the type converter
    return 1;
}

void Personality::printCard(){
    cout << "Cost:" << this->cost
        << " Personality:\"" << this->name
        << "\" Tapped:" << (char*)(this->isTapped == 1 ? "YES" : "NO") 
        << " Revealed:" << (char*)(this->isRevealed == 1 ? "YES" : "NO")
        << " Attack:" << this->attack
        << " Defence:" << this->defense
        << " Honour:" << this->honour
        << " TOTALS| ATK: " << this->totalATK() 
        << " DEF: " << this->totalDEF()
        << endl;
    this->printGreenCards();
};

bool Personality::performSeppuku(){
    this->honour--;
    if(this->honour == 0) return true; 
    this->updateItems();
    return false;
};

void Personality::updateItems(){
    Item * item;
    Follower * follower;
    bool removal = true;
    /*check green cards*/
    list <GreenCard *> :: iterator it1;
    for(it1 = gc.begin(); it1 != gc.end(); ++it1){
        item = NULL;
        follower = NULL;
        /*find items*/
        TypeConverter::getCorrectType(*it1, follower, item);
        if (item != NULL){
            /*update durability*/
            item->setdur(item->getdur()-1);
        }
    }
    /*check for 0 durabilities*/
    do{
        removal = false;
        for(it1 = gc.begin(); it1 != gc.end(); ++it1){
            item = NULL;
            follower = NULL;
            /*find items*/
            TypeConverter::getCorrectType(*it1, follower, item);
            if (item != NULL){
                /*destroy item if durability reaches 0*/
                if (item->getdur() == 0){
                    delete item;
                    this->gc.remove(*it1);
                    removal = true;
                    break;
                }
            }
        }
    }while(removal);
};