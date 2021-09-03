#ifndef Personality_h
#define Personality_h

#include <iterator> 
#include <list>
#include <stdlib.h>
#include "Card.h"

using std::list;

class GreenCard;
class BlackCard;

class Personality: public BlackCard{
    protected:
        int attack, defense, honour;
        bool isDead;
        list <GreenCard *> gc;

    public:
        Personality();
        ~Personality();

        /*SETTERS*/
        void setAttack(int);
        void setDefense(int);
        void setHonour(int);
        void setIsdead(bool);

        /*GETTERS*/
        int getAttack();
        int getDefense();
        int getHonour();
        bool getIsdead();
        list <GreenCard *> & getFolItem();
 
        void addcard(GreenCard*);
        int totalATK();
        int totalDEF();
        int totalCards();
        void printGreenCards();
        int sacrificeGreenCard(int index);/*return attack value on success, -1 on error*/
        void printCard() override;
        bool performSeppuku(); /*decreases personality honour, if reaches 0 return true(else false)*/
        void updateItems(); /*find items and decrease durability(destroy them if its 0)*/

        int getType() override;
};


#endif