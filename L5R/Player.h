#ifndef Player_h
#define Player_h

#include <list>

class GreenCard;
class BlackCard;
class Holding;
class Personality;
class Stronghold;
class DeckBuilder;

using std::list;

class Player{
    private:
        list <GreenCard *> hand, * fateDeck;
        list <BlackCard *> * dynastyDeck;
        list <Holding *> holdings;
        list <Personality *> army;
        BlackCard ** provinces;//4 sthn arxh 
        Stronghold * fort;
        DeckBuilder * DB;
        int money;
        /*confict materials*/
        list <Personality *> subarmy;

        void untapEverything();
        void drawFateCard();
        void revealProvinces();


        
    public:
        Player();
        ~Player();

        /*chains*/
        void chainMine(Holding*);
        void chainGoldMine(Holding*);
        void chainCrystalMine(Holding*);

        /*phases*/
        void startingPhase();
        void equipPhase();
        void economyPhase();
        void endPhase();
        void printStrongHold();
        void printArmy();
        void printHand();
        void printProvinces();
        void printHoldings();
        void placeinArmy(Personality*);
        void placeinHoldings(Holding*);
        void getBlackCard(BlackCard*);
        void discardSurplusFateCards();
        void calcMoney();
        void tappHoldings(int);
        

        /*setters*/
        void setmoney(int);
        

        /*getters*/
        int getmoney();
        list <GreenCard *> & getHand();
        list <GreenCard *> *& getFateDeck();
        list <BlackCard *> *& getDynastyDeck();
        list <Holding *> & getHoldings();
        list <Personality *> & getArmy();
        BlackCard ** getProvinces();
        Stronghold *& getFort();

        /*attack functionality*/
        bool canAttack();/*returns true if the can the player can attack this turn*/
        int prepareAttack();/*prepares subarmy for attack and returns total attack value*/
        bool fightReadyPersonality(int index);/*checks if personality is tapped and if it already chosen to fight*/
        void printSubArmy();
        void addtoSubArmy(int index, char atkORdef);/*add personality to subarmy*/

        /*defend functionality*/
        bool validProvince(int index);/*returns true if province with provID is a valid target*/
        int activeProvinces();/*returns number of active provinces*/
        int getProvinceDef(int index);/*returns province defence*/
        int prepareDefence();/*returns total def stats*/

        /*conflict functionality*/
        void destroySubArmy();
        void destroyProvince(int index);
        void reduceArmy(int value);/*player that lost part of subarmy chooses which cards to sacrifice*/
        int sacrificeCard(char * input);/*tries to sacrifice card to reduce army(-1 on error, attack value on success)*/
        void regroupArmy();/*clears subarmy after battle*/
        void attackerSurvived();/*does stuff that need to happen when attacker survives but not win*/


};



#endif