#ifndef GameBoard_h
#define GameBoard_h

#include "Player.h"
#include "cards/BlackCards.h"
#include <vector>

using std::vector;

class Player;

class GameBoard{
    private:
        vector <Player *> players;
        int roundsPlayed, 
            *annihilation,  /*number of times each player lost its troops*/
            *survived,  /*number of rounds player still alive*/
            *attacked,  /*number of attacks made by player*/
            *defended;  /*number of times player had to defend*/

    public:

        GameBoard(int numOfPlayers);
        ~GameBoard();

        vector <Player *> & getPlayers();

        void GamePlay();

        /*phases*/
        void startingPhase();
        void equipPhase();
        int battlePhase();
        void economyPhase();
        void endPhase();

        bool validDefender(int defender, int attacker);

        bool checkWinningCondition(); /*returns true if only one player is still active*/
        void printArena();
        void printGameStatistics();
        
};



#endif