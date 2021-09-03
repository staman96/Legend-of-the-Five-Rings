#include <cstring>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "BlackCards.h"

using namespace std;

/********************** Personalities ***********************/

Attacker::Attacker(string str)//Seperate classes for each Personality. Stats according to .txt files
:Personality(){
    this->name = str;
    this->cost = 5;
    this->attack = 3;
    this->defense = 2;
    this->honour = 2;
};

Defender::Defender(string str)
:Personality(){
    this->name = str;
    this->cost = 5;
    this->attack = 2;
    this->defense = 3;
    this->honour = 2;
};

Shogun::Shogun(string str)
:Personality(){
    this->name = str;
    this->cost = 15;
    this->attack = 10;
    this->defense = 5;
    this->honour = 8;
};

Chancellor::Chancellor(string str)
:Personality(){
    this->name = str;
    this->cost = 15;
    this->attack = 5;
    this->defense = 10;
    this->honour = 8;
};

Champion::Champion(string str)
:Personality(){
    this->name = str;
    this->cost = 30;
    this->attack = 20;
    this->defense = 20;
    this->honour = 12;
};

////////////////////////////  Holdings ////////////////////////////

GiftsandFavour::GiftsandFavour(string str)//Seperate classes for each Holding. Stats according to .txt files
:Holding(){
    this->name = str;
    this->cost = 2;
    this->harvestValue = 2;
    this->upperHolding = NULL;
    this->subHolding = NULL;
};

Plain::Plain(string str)
:Holding(){
    this->name = str;
    this->cost = 2;
    this->harvestValue = 2;
    this->upperHolding = NULL;
    this->subHolding = NULL;
};

Farms::Farms(string str)
:Holding(){
    this->name = str;
    this->cost = 3;
    this->harvestValue = 4;
    this->upperHolding = NULL;
    this->subHolding = NULL;
};

Mine::Mine(string str)
:Holding(){
    this->name = str;
    this->cost = 5;
    this->harvestValue = 3;
    this->upperHolding = NULL;
    this->subHolding = NULL;
};

GoldMine::GoldMine(string str)
:Holding(){
    this->name = str;
    this->cost = 7;
    this->harvestValue = 5;
    this->upperHolding = NULL;
    this->subHolding = NULL;
};


CrystalMine::CrystalMine(string str)
:Holding(){
    this->name = str;
    this->cost = 12;
    this->harvestValue = 6;
    this->upperHolding = NULL;
    this->subHolding = NULL;
};

