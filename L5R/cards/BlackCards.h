#ifndef BlackCards_h
#define BlackCards_h

#include "Holding.h"
#include "Personality.h"

using std::string;

class Personality;
class Holding;
class GoldMine;
class CrystalMine;

class Attacker: public Personality{
    public:
        Attacker(string);
};

class Defender: public Personality{
    public:
        Defender(string);  
};

class Shogun: public Personality{
    public:
        Shogun(string);
};

class Chancellor: public Personality{
    public:
        Chancellor(string);
};

class Champion: public Personality{
    public:
        Champion(string);
};

//////////////////////////////////////////////////////////////////

class GiftsandFavour: public Holding{
    public:
        GiftsandFavour(string);
};

class Plain: public Holding{
    public:
        Plain(string);
};

class Farms: public Holding{
    public:
        Farms(string);
};

class Mine: public Holding{
    public:
        Mine(string);
        //void connect(GoldMine);
};

class GoldMine: public Holding{
    public:
        GoldMine(string);
        //void connect(Mine);
        //void connect(CrystalMine);
};

class CrystalMine: public Holding{
    public:
        CrystalMine(string);
        //void connect(GoldMine);
};


#endif