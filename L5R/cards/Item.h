#ifndef Item_h
#define Item_h

#include "Card.h"
class GreenCard;

class Item : public GreenCard{
    protected:
        int durability;
    public:
        Item();
        ~Item();

        void setdur(int);
        int getdur();

        void printCard() override;
        int getType() override;
};



#endif