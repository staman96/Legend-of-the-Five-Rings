#include <cstring>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "GreenCards.h"
#include <bits/stdc++.h>

using std::string;
using std::cout;
using std::endl;

/************************** Items *****************************/

Katana::Katana(string str) //Seperate classes for each Item. Stats according to .txt files
:Item(){

    this->name = str;
    this->cost = 0;
    this->attackBonus = 2;
    this->defenceBonus = 0;
    this->minimumHonour = 1;
    this->effectBonus = 1;
    this->effectCost = 2;
    this->durability = 3;
};

Spear::Spear(string str)
:Item(){
    this->name=str;
    this->cost=0;
    this->attackBonus=0;
    this->defenceBonus=2;
    this->minimumHonour=1;
    this->effectBonus=1;
    this->effectCost=2;
    this->durability=3;
};

Bow::Bow(string str)
:Item(){
    this->name=str;
    this->cost=2;
    this->attackBonus=2;
    this->defenceBonus=2;
    this->minimumHonour=2;
    this->effectBonus=3;
    this->effectCost=4;
    this->durability=5;
};

Ninjato::Ninjato(string str)
:Item(){
    this->name=str;
    this->cost=4;
    this->attackBonus=3;
    this->defenceBonus=3;
    this->minimumHonour=3;
    this->effectBonus=2;
    this->effectCost=2;
    this->durability=4;
};

Wakizashi::Wakizashi(string str)
:Item(){
    this->name=str;
    this->cost=8;
    this->attackBonus=5;
    this->defenceBonus=5;
    this->minimumHonour=3;
    this->effectBonus=3;
    this->effectCost=3;
    this->durability=8;
};

/////////////////////////// followers /////////////////////////->

Footsoldier::Footsoldier(string str)//Seperate classes for each Follower. Stats according to .txt files
:Follower(){
    this->name=str;
    this->cost=0;
    this->attackBonus=2;
    this->defenceBonus=0;
    this->minimumHonour=1;
    this->effectBonus=1;
    this->effectCost=2;
};

Archer::Archer(string str)
:Follower(){
    this->name=str;
    this->cost=0;
    this->attackBonus=0;
    this->defenceBonus=2;
    this->minimumHonour=1;
    this->effectBonus=1;
    this->effectCost=2;
};

Sieger::Sieger(string str)
:Follower(){
    this->name=str;
    this->cost=5;
    this->attackBonus=3;
    this->defenceBonus=3;
    this->minimumHonour=2;
    this->effectBonus=2;
    this->effectCost=3;
};

Cavalry::Cavalry(string str)
:Follower(){
    this->name=str;
    this->cost=3;
    this->attackBonus=4;
    this->defenceBonus=2;
    this->minimumHonour=3;
    this->effectBonus=3;
    this->effectCost=4;
};

Atakebune::Atakebune(string str)
:Follower(){
    this->name=str;
    this->cost=3;
    this->attackBonus=2;
    this->defenceBonus=4;
    this->minimumHonour=3;
    this->effectBonus=3;
    this->effectCost=4;
};

Bushido::Bushido(string str)
:Follower(){
    this->name=str;
    this->cost=8;
    this->attackBonus=8;
    this->defenceBonus=8;
    this->minimumHonour=6;
    this->effectBonus=3;
    this->effectCost=8;
};
//