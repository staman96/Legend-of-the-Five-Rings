#include <cstring>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "Item.h"
#include "Card.h"
#include <bits/stdc++.h>

using std::fflush;
using std::cout;
using std::endl;

Item::Item()
:GreenCard(){

};

Item::~Item(){

};

int Item::getdur(){
    return this->durability;
}

void Item::setdur(int dur){
    this->durability = dur;
}

void Item::printCard(){
    cout << "Cost:"<< this->cost
        << " Item:\"" << this->name 
        << "\" Durability:" << this->durability
        << " ATK_Bonus:"<< this->attackBonus
        << " DEF_Bonus:" << this->defenceBonus 
        << " EFF_Bonus:" << this->effectBonus 
        << " Effect_Cost:" << this->effectCost
        << " Honour_required:" << this->minimumHonour
        << endl;
}

int Item::getType(){ //getType for the type converter
    return 4;
};