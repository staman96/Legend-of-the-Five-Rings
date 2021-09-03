#include <bits/stdc++.h>
#include <cstring>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "Card.h"
#include "Holding.h"


using std::fflush;
using std::cout;
using std::endl;
using std::string;


/*****************************  Holding  ****************************/

Holding::Holding()
:BlackCard(){
    this->upperHolding = NULL;
    this->subHolding = NULL;
};

Holding::~Holding(){
   
}; 

int Holding::getvalue(){
    return this->harvestValue;
}

int Holding::gettotalvalue() //total value that comes if the hoding is part of a chain
{
    int value=this->getvalue();
    if (value==3) //for mines
    {
        if (this->upperHolding!=NULL)
        {
            value=value+2;
        }
    }
    else if (value==5) //for gold mines
    {
        if ( (this->upperHolding!=NULL) && (this->subHolding!=NULL) )
        {
            value=value + 2*(value);
        }
        else if ( (this->upperHolding==NULL) && (this->subHolding!=NULL) )
        {
            value=value+4;
        }
        else if ( (this->upperHolding!=NULL) && (this->subHolding==NULL) )
        {
            value=value+5;
        }
    }
    else if (value==6) //for crystal mines
    {
        if (this->subHolding!=NULL) 
        {
            if (this->getSubHol()->subHolding!=NULL)
            {
                value=value + 3*(value);
            }
            else
            {
                value=2*(value);
            }   
        }
    }
    return value; 
}

Holding *& Holding::getUpperHol(){
    return this->upperHolding;
};

Holding *& Holding::getSubHol(){
    return this->subHolding;
};

void Holding::printCard(){
    cout << "Cost:" << this->cost
        << " Holding:\"" << this->name
        << "\" Tapped:" << (char*)(this->isTapped == 1 ? "YES" : "NO") 
        << " Revealed:" << (char*)(this->isRevealed == 1 ? "YES" : "NO")
        << " Harvest:" << this->harvestValue
        << " Total_Harvest:" << this->gettotalvalue()
        << endl; 
};

int Holding::getType(){ //getType for the type converter
    return 2;
};

void Holding::setvalue(int value){
    this->harvestValue = value;
};

/************************** StrongHold ************************/

Stronghold::Stronghold()
:Holding(), honour(5), money(5), initialDefense(5){
    this->name = "";
    this->harvestValue = this->money;
};

Stronghold::~Stronghold(){
    
};

int Stronghold::getHon(){
    return this->honour;
};

void Stronghold::setHon(int hon){
    this->honour = hon;
};

int Stronghold::getMoney(){
    return money;
};

void Stronghold::setMoney(int mon){
    this->money = mon;
};

int Stronghold::getInitialD(){
    return this->initialDefense;
};

void Stronghold::setInitialD(int initdeff){
    this->initialDefense = initdeff;
};

int Stronghold::getType(){
    return 5;
};
