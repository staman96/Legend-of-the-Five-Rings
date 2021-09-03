#ifndef Holding_h
#define Holding_h

#include "Card.h"
using std::string;

class BlackCard;

class Holding : public BlackCard{
    protected:
        int harvestValue;
        Holding * upperHolding, * subHolding;

    public:
        Holding();
        ~Holding();

        /*getters*/
        int getvalue();
        int gettotalvalue();
        Holding *& getUpperHol();
        Holding *& getSubHol();
        void printCard() override;
   
        int getType() override;

        void setvalue(int);
};

class Stronghold : public Holding{ //a stronghold is a holding
    private:
        int honour, money, initialDefense;
    public:
        Stronghold();
        ~Stronghold();

        /*setters*/
        void setHon(int);
        void setMoney(int);
        void setInitialD(int);

        /*getters*/
        int getHon();
        int getMoney();
        int getInitialD();
       
        int getType() override;
};


#endif