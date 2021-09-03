#ifndef GreenCards_h
#define GreenCards_h

#include "Follower.h"
#include "Item.h"

using std::string;

class Item;
class Follwer;

class Katana: public Item{
    public:
        Katana(string);
};

class Spear: public Item{
    public:
        Spear(string);  
};

class Bow: public Item{
    public:
        Bow(string);
};

class Ninjato: public Item{
    public:
        Ninjato(string);
};

class Wakizashi: public Item{
    public:
        Wakizashi(string);
};

////////////////////////////////////////////////////////////////////////////////////////////->

class Footsoldier: public Follower{
    public:
        Footsoldier(string);
};

class Archer: public Follower{
    public:
        Archer(string);
};

class Cavalry: public Follower{
    public:
        Cavalry(string);
};

class Bushido: public Follower{
    public:
        Bushido(string);
};

class Sieger: public Follower{
    public:
        Sieger(string);
};

class Atakebune: public Follower{
    public:
        Atakebune(string);
};

#endif