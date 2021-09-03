#ifndef Card_h
#define Card_h

using std::string;

class Card{
    protected:
        string name;
        int cost;
        bool isTapped;

    public:
        Card();
        ~Card();
        
        /*getters*/
        string getname();
        int getcost();
        bool getistap();
        /*setters*/
        void setname(string);
        void setcost(int);
        void setistap(bool);

        virtual void printCard() = 0;

};

class GreenCard : public Card{
    protected:
        int attackBonus, defenceBonus, minimumHonour;
        string cardText; //empty data member as no value was given
        int effectBonus, effectCost;

    public:
        GreenCard();
        ~GreenCard();

        /*getters*/
        int getATKbon();
        int getDEFbon();
        int getMINhon();
        int getEFFbon();
        int getEFFcost();
        string getTXT();

        /*setters*/
        void setATKbon(int);
        void setDEFbon(int);
        void setMINhon(int);
        void setEFFbon(int);
        void setEFFcost(int);
        void setTXT(string);
        
        virtual int getType() = 0; //pure virtual, only the derived class' function used
        
};

class BlackCard : public Card{
    protected:
        bool isRevealed;
    public:
        BlackCard();
        ~BlackCard();

        bool getisrev();
        void setisrev(bool);

        virtual int getType() = 0; //pure virtual, only the derived class' function used
};

#endif