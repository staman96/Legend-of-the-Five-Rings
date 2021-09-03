#include <bits/stdc++.h>
#include "Follower.h"

using std::fflush;
using std::cout;
using std::endl;

Follower::Follower()
:GreenCard(){

};

Follower::~Follower(){

};

void Follower::printCard(){
    cout << "Cost:"<< this->cost
        <<" Follower:\"" << this->name
        << "\" ATK_Bonus:"<< this->attackBonus
        << " DEF_Bonus:" << this->defenceBonus 
        << " EFF_Bonus:" << this->effectBonus 
        << " Effect_Cost:" << this->effectCost 
        << " Honour_required:" << this->minimumHonour 
        << endl;
}

int Follower::getType(){ //getType for the type converter
    return 3;
};