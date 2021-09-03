#include <bits/stdc++.h>
#include <cstring>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "Player.h"
#include "TypeConverter.h"
#include "cards/BlackCards.h"
#include "cards/Card.h"
#include "cards/Follower.h"
#include "cards/GreenCards.h"
#include "cards/Holding.h"
#include "cards/Item.h"
#include "cards/Personality.h"
#include "DeckBuilder.h"

using std::fflush;
using std::cout;
using std::cin;
using std::getline;
using std::endl;
using std::list;
using std::streamsize;

Player::Player()
:money(0){

    this->DB = new DeckBuilder();
    this->provinces = NULL;
    this->provinces = new BlackCard*[4];
    this->fort = new Stronghold();
    for (int i = 0; i < 4; i++){

        this->provinces[i] = NULL;
    }

    /*create and shuffle deck*/
    this->fateDeck = this->DB->createFateDeck();
    this->dynastyDeck = this->DB->createDynastyDeck();

    this->DB->deckShuffler(this->getFateDeck());
    this->DB->deckShuffler(this->getDynastyDeck());

    /*init provinces*/
    list <BlackCard*> :: iterator it1;
    for (int j = 0; j < 4; j++){

        it1 = this->dynastyDeck->begin();
        this->provinces[j] = * it1;
        this->dynastyDeck->pop_front();
    }

    /*draw starting hand*/
    for (int i = 0; i < 3; i++) this->drawFateCard();
}

Player::~Player(){
    delete this->fort;

    for (int i = 0; i < 4; i++){

        if(this->provinces[i] != NULL) delete this->provinces[i];
    }
    delete[] provinces;

    if(this->hand.size() > 0){
        list <GreenCard *> :: iterator it1;
        for(it1 = this->hand.begin(); it1 != this->hand.end(); it1++){
            delete *it1;
        }
        this->hand.clear();
    }
    

    if(this->holdings.size() > 0){
        list <Holding *> :: iterator it2;
        for(it2 = this->holdings.begin(); it2 != this->holdings.end(); it2++){
            delete *it2;
        }
        this->holdings.clear();
    }

    if (this->army.size() > 0){
        list <Personality *> :: iterator it3;
        for(it3 = this->army.begin(); it3 != this->army.end(); it3++){
            delete (*it3);
        }
        this->army.clear();
    }

    delete this->DB;
    
}

void Player::setmoney(int mn){
    this->money = mn;
}

int Player::getmoney(){
    return this->money;
}

void Player::untapEverything(){ //untaps all the cards in the starting phase

    this->fort->setistap(0); //the stronghold

    list <GreenCard*> :: iterator it1;
    for(it1 = this->hand.begin(); it1 != this->hand.end(); ++it1){ //in the hand
        (*it1)->setistap(0);
    }

    list <Holding*> :: iterator it2;
    for(it2 = this->holdings.begin(); it2 != this->holdings.end(); ++it2){ //in the holdings
        (*it2)->setistap(0);
    }

    list <Personality*> :: iterator it3;
    for(it3 = this->army.begin(); it3 != this->army.end(); ++it3){ //in the army
        (*it3)->setistap(0);
    }

    for (int i = 0; i < 4; i++){ //and in the provinces
        if(provinces[i]!=NULL){
            this->provinces[i]->setistap(0);
        }
    }
}

void Player::drawFateCard(){ //draws card from th fate deck to the hand

    if( this->fateDeck->size() == 0 ){
        cout << "Fate Deck is empty!" << endl;
        return;
    }
    list <GreenCard*> :: iterator it1;
    it1 = this->fateDeck->begin();
    this->hand.push_front((*it1));
    this->fateDeck->pop_front();
}

void Player::revealProvinces(){ //provinces set to revealed
    for (int i = 0; i < 4; i++){
        if(this->provinces[i] != NULL){
            this->provinces[i]->setisrev(1);
        }
    }
}

void Player::printHand(){

    cout << "HAND: " << endl;
    list <GreenCard*> :: iterator it1;
    int i = 1;
    for(it1 = this->hand.begin(); it1 != this->hand.end(); ++it1){

        cout << "card_no: " << i++ << " ";
        (*it1)->printCard();

    }
    fflush;
}

void Player::printArmy(){

    cout << "ARMY:" << endl;
    list <Personality*> :: iterator it1;
    int i = 1;
    for(it1 = this->army.begin(); it1 != this->army.end(); ++it1){

        cout << "card_no: " << i++ << " ";
        (*it1)->printCard();
    }
    fflush;
}
void Player::printHoldings(){

    cout << "HOLDINGS:" << endl;
    list <Holding*> :: iterator it1;
    int i = 1;
    for(it1 = this->holdings.begin(); it1 != this->holdings.end(); ++it1){

        cout << "card_no: " << i++ << " ";
        (*it1)->printCard();
        
    }
    fflush;
}

void Player::printProvinces(){

    cout << "PROVINCES:" << endl;
    for (int i = 0; i < 4; i++)
    {
        if(this->provinces[i] != NULL)
        {
            cout << "card_no: " << i+1 << " ";
            if( this->provinces[i]->getisrev() ){
                
                this->provinces[i]->printCard();
            }
            else{
                cout << "NOT REVEALED" << endl;
            }
        }
        else{
            cout << "Province " << i+1 << " defeated" << endl;
        }
    }
    fflush;
}

void Player::startingPhase(){

    cout << "In starting phase:" << endl;
    this->untapEverything();
    this->calcMoney();
    this->drawFateCard();
    this->revealProvinces();
    this->printHand();
    this->printProvinces();
}

void Player::placeinArmy(Personality* ps){ //places a black card in the army
    this->army.push_front(ps);
}

void Player::placeinHoldings(Holding* hd){ //places a black card in the holdings
    this->holdings.push_front(hd);
}

void Player::getBlackCard(BlackCard* bc){ //draws a black card from the dynasty deck and puts it in the right list

    Holding * ph = NULL;
    Personality* pp = NULL;
    TypeConverter::getCorrectType(bc,pp,ph);
    if (bc->getType() == 1){
        this->placeinArmy(pp);
    }
    else if (bc->getType() == 2) //if the holding is 
    {
        this->placeinHoldings(ph);
        if ( ph->getvalue() == 3 ){ //mine

            this->chainMine(ph);
        }
        else if ( ph->getvalue() == 5 ){ //or gold mine

            this->chainGoldMine(ph);
        }
        else if ( ph->getvalue() == 6 ){ //or crystal mine checks if it can form a chain with other holdings

            this->chainCrystalMine(ph);
        }
    }
};

void Player::equipPhase()
{
    cout<<"In equip phase:"<<endl;
    int card;
    do
    {
        cout << "Available money: " << this->money << endl;
        this->printHand();
        this->printArmy();
        cout << "which card do you want to buy? (give 0 if you don't) " << endl; //choose card to purchase
        cin >> card;
        if (card != 0)
        {
            int i = 1;
            list <GreenCard*> :: iterator it1;
            for(it1 = this->hand.begin(); it1 != this->hand.end(); ++it1) 
            {
                if(i == card) //if the card exists in the list
                {
                    cout << (*it1)->getname() << endl;
                    if( (*it1)->getcost() <= this->money ) //and player's money are more than the cost
                    {
                        int give;
                        cout << "to which personality do you want to give it?" << endl;
                        cin >> give;
                        int j = 1;
                        list <Personality*> :: iterator it2;
                        for(it2 = this->army.begin(); it2 != this->army.end(); ++it2) //choose the personality to give the card to
                        {
                            if(j == give)
                            {
                                if ( (*it2)->totalCards() < 10 ) //10 are the maximum cards possible for a Personality to hold 
                                {
                                    if ( (*it2)->getHonour() >= (*it1)->getMINhon() ) //if the personality has enough honour to get the card
                                    {
                                        this->tappHoldings((*it1)->getcost());
                                        this->money = this->money - (*it1)->getcost(); //the card is purchased
                                        int bon;
                                        cout << "to you want to get the bonus effect? (1=yes,0=no)" << endl;
                                        cin >> bon;
                                        if (bon == 1)
                                        {
                                            if( (*it1)->getEFFcost() <= this->money ) //if the player wants and can buy the bonus effect
                                            {
                                                (*it1)->setATKbon( (*it1)->getEFFbon() + (*it1)->getATKbon() ); //the bonus effect gets added to the attack
                                                (*it1)->setDEFbon( (*it1)->getEFFbon() + (*it1)->getDEFbon() ); //and defense stats of the green card
                                                (*it1)->setEFFbon(0);                                           //and the bonus effect gets equal to 0
                                                this->money = this->money - (*it1)->getEFFcost();
                                                this->tappHoldings((*it1)->getEFFcost());
                                            }
                                            else
                                            {
                                                cout << "Not enough money to buy the bonus" << endl;
                                            }
                                        }
                                        (*it2)->getFolItem().push_front(*it1);
                                        hand.erase(it1);
                                        break;
                                    }
                                    else
                                    {
                                        cout << "Not enough honour to buy the card" << endl;
                                    } 
                                }
                                else
                                {
                                    cout << "This Personality holds the maximum number of cards" << endl;
                                }
                            }
                            j++;
                        }
                        break;
                    }
                    else
                    {
                        cout << "Not enough money to buy the card" << endl;
                    }
                }
                i++;
            }
        }
    } while (card != 0);
};

void Player::economyPhase()
{
    cout<<"In economy phase:"<<endl;
    int card;
    do
    {
        this->printProvinces();
        cout << "Available money: " << money << endl;;
        cout << "which card do you want to buy? (give 0 if you don't) " << endl;
        /*if dynasty deck is empty*/
        if(this->dynastyDeck->size() == 0 && this->activeProvinces() == 1){
            cout << "You can't buy the last card because you're going to loose the game!" << endl;
            card = 0;
            getchar;
        }
        else if(this->dynastyDeck->size() == 0){
            cout << "Dynasty Deck is empty! Whenever you buy a card you loose a province." << endl;
            cin >> card;
        }
        else{
            cin >> card;
        }
        
        if (card != 0) //choose cart to purchase from a province
        {
            for (int i = 0; i < 4; i++)
            {
                if ( i == (card-1))
                {
                    if (this->provinces[i] != NULL) //if the province is not defeated 
                    {
                        if (this->provinces[i]->getisrev() == 1) //and is revealed
                        {
                            cout << this->provinces[i]->getname() << endl;
                            if( provinces[i]->getcost() <= this->money ) //and if the player has enough money
                            {
                                this->tappHoldings( this->provinces[i]->getcost() ); //the card form the province is purchased form the player
                                this->getBlackCard(this->provinces[i]); //and gets sent to either the army or the holdings
                                this->money = this->money - this->provinces[i]->getcost();

                                if(this->dynastyDeck->size() > 0){
                                    /*replace slot with new non-revealed card*/
                                    list <BlackCard*> :: iterator it1;
                                    it1 = this->dynastyDeck->begin();
                                    this->provinces[i]=*it1;
                                    this->dynastyDeck->pop_front();
                                    
                                }
                                else{
                                    cout << "Province " << i+1 << " lost because Dynasty Deck run out of cards!" << endl;
                                    this->provinces[i] = NULL;
                                }
                            }
                            else
                            {
                                cout << "Not enough money to buy the card" << endl;
                            }
                        }
                        else
                        {
                            cout << "Card not revealed yet" << endl;
                        }
                    }
                    else
                    {
                        cout << "Province " << i+1 << " defeated" << endl;
                    }
                }
            }
        }
    } while (card != 0);
 }

void Player::endPhase()
{
    cout << "In end phase:" << endl;
    this->printStrongHold();
    this->printHand();
    this->printArmy();
    this->printProvinces();
    this->printHoldings();
    
    this->money = 0;
    this->discardSurplusFateCards();
};

void Player::printStrongHold(){
    cout << "STRONGHOLD's Honour:" << this->fort->getHon()
        << " Harvest:" << this->fort->getMoney()
        << " Defence:" << this->fort->getInitialD()
        << " Tapped:" << (char*)(this->fort->getistap() == 1 ? "YES" : "NO")
        << endl;
};

void Player::chainMine(Holding* ph) //function for a mine to form a chain with a gold mine
{
    list <Holding *>  upper;
    list <Holding*> :: iterator it1;
    for(it1 = this->holdings.begin(); it1 != this->holdings.end(); ++it1) //a sublist of the holding list is created that holds the suitable gold mines 
    {
        if ( (*it1)->getvalue() == 5 )
        {
            if ( (*it1)->getSubHol() == NULL )
            {
                upper.push_back(*it1);
            }
        }
    }
    if (upper.size() != 0) //if one or more suitable gold mine(s) exist(s) it forms a chain with the mine
    { 
        int choose = rand() % upper.size();
        cout << choose << endl;
        int i=0;
        for(it1 = upper.begin(); it1 != upper.end(); ++it1) 
        {
            if(i == choose)
            {
                ph->getUpperHol() = (*it1);
                (*it1)->getSubHol() = ph;
            }
            i++;
        }
    }
};

void Player::chainCrystalMine(Holding* ph) //function for a crystal mine to form a chain with a gold mine
{
    list <Holding *>  sub;
    list <Holding*> :: iterator it1;
    for(it1 = this->holdings.begin(); it1 != this->holdings.end(); ++it1) //a sublist of the holding list is created that holds the suitable gold mines 
    {
        if ( (*it1)->getvalue() == 5 )
        {
            if ( (*it1)->getUpperHol() == NULL )
            {
                sub.push_back(*it1);
            }
        }
    }
    if (sub.size() != 0) //if one or more suitable gold mine(s) exist(s) it forms a chain with the crystal mine
    {
        int choose = rand() % sub.size();
        cout << choose << endl;
        int i=0;
        for(it1 = sub.begin(); it1 != sub.end(); ++it1) 
        {
            if(i == choose)
            {
                ph->getSubHol() = (*it1);
                (*it1)->getSubHol() = ph;
            }
            i++;
        }
    }
};

void Player::chainGoldMine(Holding* ph) //function for a gold mine to form a chain with a mine and/or a crystal mine
{
    list <Holding *>  lst;
    list <Holding*> :: iterator it1;
    for(it1 = this->holdings.begin(); it1 != this->holdings.end(); ++it1) //a sublist of the holding list is created that holds the suitable crystal mines 
    {
        if ( (*it1)->getvalue() == 6 )
        {
            if ( (*it1)->getSubHol() == NULL )
            {
                lst.push_back(*it1);
            }
        }
    }
    if (lst.size()!=0) //if one or more suitable crystal mine(s) exist(s) it forms a chain with the gold mine
    {
        int choose = rand() % lst.size();
        cout << choose << endl;
        int i = 0;
        for(it1 = lst.begin(); it1 != lst.end(); ++it1) 
        {
            if(i == choose)
            {
                ph->getUpperHol() = (*it1);
                (*it1)->getSubHol() = ph;
            }
            i++;
        }
    }
    lst.clear(); //the sublist empties
    for(it1 = this->holdings.begin(); it1 != this->holdings.end(); ++it1) //a sublist of the holding list is created that holds the suitable mines 
    {
        if ( (*it1)->getvalue() == 3 )
        {
            if ( (*it1)->getUpperHol() == NULL )
            {
                lst.push_back(*it1);
            }
        }
    }
    if (lst.size() != 0)  //if one or more suitable mine(s) exist(s) it forms a chain with the gold mine
    {
        int choose = rand() % lst.size();
        cout << choose << endl;
        int i=0;
        for(it1 = lst.begin(); it1 != lst.end(); ++it1) 
        {
            if(i == choose)
            {
                ph->getSubHol() = (*it1);
                (*it1)->getUpperHol() = ph;
            }
            i++;
        }
    }
};

void Player::tappHoldings(int amount) //tapps the right amount of holdings in orger to cover the value of a purchase
{
    if(fort->getistap()!=1) //first tapps the stronghold (if it isn't tapped)
    {
        if (amount>0)
        {
            fort->setistap(1);
            amount = amount-fort->getMoney();
        }
    }
    list <Holding*> :: iterator it1;
    for(it1 = this->holdings.begin(); it1 != this->holdings.end(); ++it1) //and then tapps the right amount of holdings untill the value of a purchase is covered completly
    {
        if (amount>0)
        {
            if ((*it1)->getistap()!=1)
            {
                (*it1)->setistap(1);
                amount = amount-(*it1)->gettotalvalue();
            }
        }
    }    
}

void Player::discardSurplusFateCards(){ 
    int rid;
    while ( hand.size() > 6 ) //if the player has more than 6 cards in th hand
    {
        cout<<"Must have at most 6 cards in the hand"<<endl;
        this->printHand();
        cout<<"Choose the card to discard: "<<endl;
        cin>>rid;
        int i = 1;
        list <GreenCard*> :: iterator it1;
        for(it1 = this->hand.begin(); it1 != this->hand.end(); ++it1) //chooses one cars to drop from it
        { 
            if(i == rid)
            {
                delete (*it1);
                hand.erase(it1);
                break;
            }
            i++;
        }
    }    
};

void Player::calcMoney(){ //calculates the amount of available money at the start of the round according to the player's strongold and holdings
    this->money = this->fort->getMoney();
    list <Holding*> :: iterator it1;
    for(it1 = this->holdings.begin(); it1 != this->holdings.end(); ++it1) 
    {
        this->money += (*it1)->gettotalvalue();
    }
};


list <GreenCard *> & Player::getHand(){
    return this->hand;
};

list <GreenCard *> *& Player::getFateDeck(){
    return this->fateDeck;
};

list <BlackCard *> *& Player::getDynastyDeck(){
    return this->dynastyDeck;
};

list <Holding *> & Player::getHoldings(){
    return this->holdings;
};

list <Personality *> & Player::getArmy(){
    return this->army;
};

BlackCard ** Player::getProvinces(){
    return this->provinces;
};

Stronghold *& Player::getFort(){
    return this->fort;
};


bool Player::canAttack(){

    if (this->army.size() == 0) return false;
    list <Personality*> :: iterator it2;
    for(it2 = this->army.begin(); it2 != this->army.end(); ++it2){

        if ( !(*it2)->getistap() ) return true;
    }
    return false;

};

int Player::prepareAttack(){
    
    int selection, totalATK = 0;
    list <Personality*> :: iterator it2;
    
    do{
        it2 = this->army.begin();
        this->printArmy();
        cout << "Select personality to add to attack troops.(0 to finish)" << endl;
        cin >> selection;

        while(selection != 0 && ( selection < 0 || selection > this->army.size() || !this->fightReadyPersonality(selection-1) )){
            cout << "Invalid choice." << endl;
            cout << "Select personality to add to attack troops.(0 to finish)" << endl;
            cin >> selection;
        }

        if (selection == 0) return totalATK;

        /*add personality to subarmy*/
        this->addtoSubArmy(selection-1, 'A');

        /*calculate atk and add it to total ATK */
        advance(it2, selection-1);
        totalATK += (*it2)->totalATK();
        
        this->printSubArmy();
        cout << "Total ATTACK: " << totalATK << endl;

    }while(selection != 0);

    return totalATK;
};

bool Player::fightReadyPersonality(int index){

    list <Personality*> :: iterator it2;
    it2 = this->army.begin();
    advance(it2,index);
    if ( (*it2)->getistap() ) {
        cout << "Personality is tapped" << endl;
        return false;
    }
    if ( this->subarmy.size() > 0 ){
        list <Personality*> :: iterator it;
        for(it = this->subarmy.begin(); it != this->subarmy.end(); ++it){
            if ( (*it) == (*it2) ) {
                cout << "Personality is already in troops." << endl;
                return false;
            }
        }
    }
    return true;

};

void Player::printSubArmy(){

    cout << "Selected troops:" << endl;
    list <Personality*> :: iterator it1;
    int i = 1;
    for(it1 = this->subarmy.begin(); it1 != this->subarmy.end(); ++it1){

        cout << "card_no: " << i << " ";
        (*it1)->printCard();
        i++;
    }
    fflush;
};

void Player::addtoSubArmy(int index, char atkORdef){
    /*find personality*/
    list <Personality*> :: iterator it2;
    it2 = this->army.begin();
    advance(it2,index);
    /*add to subarmy*/
    this->subarmy.push_back((*it2));
    /*make the attacker's card unable to be used to another fight*/
    if (atkORdef == 'A') (*it2)->setistap(true);

};


bool Player::validProvince(int index){
    if(this->provinces[index] != NULL) return true;
    return false;
};

int Player::activeProvinces(){
    int sum = 0;
    for (int i = 0; i < 4; i++){
        this->provinces[i] != NULL ? sum++ : 0;
    }
    return sum;
};

int Player::getProvinceDef(int index){

    /*province total def consists of stronghold initial defence*/
    int provDef = this->fort->getInitialD();


    return provDef;
};

int Player::prepareDefence(){

    int selection, totalDEF = 0;
    list <Personality*> :: iterator it2;
    
    do{
        it2 = this->army.begin();
        this->printArmy();
        cout << "Select personality to add to defence troops.(0 to finish)" << endl;
        cin >> selection;

        while(selection != 0 && ( selection < 0 || selection > this->army.size() || !this->fightReadyPersonality(selection-1) ) ){
            cout << "Invalid choice." << endl;
            cout << "Select personality to add to defence troops.(0 to finish)" << endl;
            cin >> selection;
        }

        if (selection == 0) return totalDEF;

        /*add personality to subarmy*/
        this->addtoSubArmy(selection-1, 'D');

        /*calculate atk and add it to total defence */
        advance(it2, selection-1);
        totalDEF += (*it2)->totalDEF();
        
        this->printSubArmy();
        cout << "Total DEFENCE: " << totalDEF << endl;

    }while(selection != 0);

    return totalDEF;
};
        
void Player::destroySubArmy(){

    /*if the whole army was used to fight*/
    if (this->subarmy.size() == this->army.size()){
        list <Personality*> :: iterator it2;
        for(it2 = this->army.begin(); it2 != this->army.end(); ++it2){
            delete *it2;
        }
        this->army.clear();
        this->subarmy.clear();
        return;
    }
    /*if part of the whole army was used*/
    list <Personality*> :: iterator it;
    list <Personality*> :: iterator it2;
    for(it = this->subarmy.begin(); it != this->subarmy.end(); ++it){
        /*search army for each personality in subarmy*/
        for(it2 = this->army.begin(); it2 != this->army.end(); ++it2){
            if ( (*it) == (*it2) ){
                delete *it2;
                this->army.remove(*it2);
                break;
            }
        }
    }
    this->subarmy.clear();
};

void Player::destroyProvince(int index){
    delete this->provinces[index];
    this->provinces[index] = NULL;
};

void Player::reduceArmy(int value){

    /*user input*/
    streamsize inputLength = 128;
    char * input = new char[128];
    int left = value, valuereduced;


    if(this->subarmy.size() > 0){
        do{
            this->printSubArmy();
            cout << "Attack value owed:     " << left << endl;
            cout << "Choose card to sacrifice (ie 1 2 or 1.2 for item/follower or 2 for personality)" << endl;
            do { cin.getline(input,inputLength); }while(strcmp(input,"\0") == 0);

            valuereduced = this->sacrificeCard(input);
            while( valuereduced == -1 ){
                
                cout << "Wrong input!!!" << endl;
                cout << "Choose card to sacrifice (ie 1 2 or 1.2 for item/follower or 2 for personality)" << endl;
                do { cin.getline(input,inputLength); }while(strcmp(input,"\0") == 0);
                valuereduced = this->sacrificeCard(input);
            }

            left -= valuereduced;

        }while( this->subarmy.size() > 0 && left > 0 );
    }

    cout << "Army Reduced" << endl;
    delete[] input;
};

int Player::sacrificeCard(char * input){

    int personality, greenCard, ATKval;
    char * pch;         /*used for strtok*/

    /*get personality*/
    pch = strtok(input," .,-|\t\0");
    // cout << "Personality(pch-1): " << pch << endl;
    personality = atoi(pch);
    personality--; /*index type*/
    /*check if personality card is valid*/
    if (personality < 0 || personality >= this->subarmy.size()) return -1;
    /*get Personality card*/
    list <Personality*> :: iterator it2;
    it2 = this->subarmy.begin();
    advance(it2,personality);

    /*check if a green card was selected*/
    pch = strtok(NULL," \0");
    if( pch != NULL ){
        // cout << "GREAN CARD(pch): " << pch << endl;
        greenCard = atoi(pch);
        greenCard--; /*index type*/

        /*check greencard validity and return greenCard's attack value*/
        ATKval = (*it2)->sacrificeGreenCard(greenCard);
        return ATKval;
    }

    ATKval = (*it2)->totalATK();
    delete *it2;
    this->army.remove(*it2);
    this->subarmy.remove(*it2);

    cout << "ATK to be reduced " << ATKval << endl;

    return ATKval;
};

void Player::regroupArmy(){

    if (this->subarmy.size() > 0) this->subarmy.clear();

};

void Player::attackerSurvived(){
    list <Personality*> :: iterator it2;
    for(it2 = this->subarmy.begin(); it2 != this->subarmy.end(); ++it2){
        if( (*it2)->performSeppuku() ){
            delete *it2;
            this->army.remove(*it2);
        }
    }
    this->subarmy.clear();
};