#ifndef Follower_h
#define Follower_h

#include "Card.h"

class GreenCard;

class Follower : public GreenCard{
    private:
        
    public:
        Follower();
        ~Follower();

        void printCard() override;
        int getType() override;
};




#endif