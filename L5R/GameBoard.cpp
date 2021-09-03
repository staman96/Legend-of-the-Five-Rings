#include <bits/stdc++.h>
#include <cstring>
#include <stdlib.h>
#include <iostream>
#include <string>

#include "GameBoard.h"
#include "Player.h"

using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::fflush;

GameBoard::GameBoard(int numofpl)
:roundsPlayed(0){
    this->annihilation = new int[numofpl];
    this->survived = new int[numofpl];
    this->attacked = new int[numofpl];
    this->defended = new int[numofpl];
    
    for (int i = 0; i < numofpl; i++){

        Player* ppl = new Player();
        this->players.push_back(ppl);
        this->annihilation[i] = 0;
        this->survived[i] = 0;
        this->attacked[i] = 0;
        this->defended[i] = 0;
    }
}

GameBoard::~GameBoard(){
    for(int i = 0; i < this->players.size(); i++) 
        delete this->players[i];
    delete[] this->annihilation;
    delete[] this->survived;
    delete[] this->attacked;
    delete[] this->defended;
}

vector <Player *> & GameBoard::getPlayers(){
    return this->players;
};

void GameBoard::GamePlay(){

    int winner = -1;

    cout << "Starting Game with " << this->players.size() << " players." << endl;

    int i = 1;
    while (i != 100)
    {
        this->roundsPlayed++;
        for(int p = 0; p < this->players.size(); p++) this->survived[p]++;
        this->startingPhase();
        this->equipPhase();
        winner = this->battlePhase();
        if (winner != -1) { winner++; break;}
        this->economyPhase();
        this->endPhase();
        cout << "Hit 100 to terminate the game violently" << endl;
        cin >> i;
    }
    
    this->printGameStatistics();
    cout << "****************************************************" << endl;
    cout << "-------->  !!! PLAYER " << winner << " WON !!!    <--------" << endl;
    cout << "****************************************************" << endl;

};

void GameBoard::startingPhase(){

    cout << "----------------------------  STARTING PHASE  -----------------------------" << endl;
    for (int i = 0; i < this->players.size(); i++)
    {
        if (this->players[i] != NULL) {
            cout << "---> PLAYER's " << i+1 << " STATE" << endl;
            this->players[i]->startingPhase();
        }
    }
};

void GameBoard::equipPhase(){

    cout << "----------------------------  EQUIP PHASE  -----------------------------" << endl;
    for (int i = 0; i < this->players.size(); i++)
    {
        if (this->players[i] != NULL && this->players[i]->getArmy().size() > 0)
        {
            cout << "---> PLAYER's " << i+1 << " MOVE" << endl;
            this->players[i]->equipPhase();
        }
    }
};

int GameBoard::battlePhase(){

    cout << "----------------------------  BATTLE PHASE  -----------------------------" << endl;
    for (int i = 0; i < this->players.size(); i++){

        int defender, ATKval, DEFval, provID, provDEF;

        if( this->players[i] == NULL ) continue;

        if (this->players[i]->canAttack()){

            this->printArena();

            cout << "---> PLAYER's " << i+1 << " MOVE" << endl;

            cout << "Choose player to attack to(choose 0 for no attack)" << endl;
            cin >> defender;
            
            while (defender != 0 && !this->validDefender(defender, i+1) ){
                cout << "Invalid player!!!" << endl;
                cout << "Choose player to attack to(choose 0 for no attack)" << endl;
                cin >> defender;
            }

            if (defender == 0) continue;

            /*attacker prepares army to attack*/
            ATKval = this->players[i]->prepareAttack();

            if(ATKval == 0) continue;

            /*get statistics*/
            this->attacked[i]++;
            this->defended[defender-1]++;
            
            this->players[defender-1]->printProvinces();
            cout << "Choose province to attack to" << endl;
            cin >> provID;

            while(provID > 4 || provID < 1 || !this->players[defender-1]->validProvince(provID-1)){
                cout << "Invalid Province!!!" << endl;
                cout << "Choose province to attack to" << endl;
                cin >> provID;
            }

            
            /*defender prepares army to defend province*/
            provDEF = this->players[defender-1]->getProvinceDef(provID-1);
            cout << "Total attack is " << ATKval << " and province's defence is " << provDEF << endl;
            cout << "---> PLAYER's " << defender << " MOVE" << endl;
            DEFval = this->players[defender-1]->prepareDefence();
            cout << "Total troops defence is " << DEFval << " and Province Defence is " << provDEF << endl;

            /***  confict resolution  ***/

            /*case where attacker prevails*/
            if(ATKval >= DEFval + 2*provDEF){
                /*destroy defenders subarmy and province*/
                this->players[defender-1]->destroySubArmy();
                this->players[defender-1]->destroyProvince(provID-1);
                /*get statistics*/
                this->annihilation[defender-1]++;
                cout << endl << "Player's " << i+1 << " attack(" << ATKval << ") overpowered player's " 
                    << defender << " total army defence(" << DEFval << ") and twice the province's defence(" 
                    << provDEF << "x2) and destroyed both." << endl << endl;
            }
            /*case where just attack stat is more that defence stat*/
            else if(ATKval > DEFval + provDEF){
                /*destroy defender's subarmy*/
                this->players[defender-1]->destroySubArmy();                
                /*reduce attcker's army*/
                cout << "---> PLAYER's " << i+1 << " MOVE" << endl;
                this->players[i]->reduceArmy(ATKval - DEFval - provDEF);
                this->players[i]->attackerSurvived();
                /*get statistics*/
                this->annihilation[defender-1]++;
                cout << endl << "Player's " << i+1 << " attack(" << ATKval << ") overpowered player's " 
                    << defender << " total army defence(" << DEFval << ") and once the province's defence(" 
                    << provDEF << "x1); and while defender's army got destroyed, the province didn't." << endl << endl;
            }
            /*case where attack stat equals defence*/
            else if(ATKval == DEFval + provDEF){
                /*destroy both's subarmies*/
                this->players[defender-1]->destroySubArmy();
                this->players[i]->destroySubArmy();
                /*get statistics*/
                this->annihilation[i]++;
                this->annihilation[defender-1]++;
                cout << endl << "Player's " << i+1 << " attack(" << ATKval << ") was equal with player's " 
                    << defender << " total army defence(" << DEFval << ") and once the province's defence(" 
                    << provDEF << "x1); so both's armies got destroyed." << endl << endl;
            }
            /*case where attacker lose*/
            else if(ATKval < DEFval + provDEF){
                /*destroy attackers subarmy*/
                this->players[i]->destroySubArmy();
                /*reduce defenders army*/
                cout << "---> PLAYER's " << defender << " MOVE" << endl;
                this->players[defender-1]->reduceArmy((DEFval+provDEF) - ATKval);
                /*get statistics*/
                this->annihilation[i]++;
                cout << endl << "Player's " << i+1 << " attack(" << ATKval << ") was lower than player's " 
                    << defender << " total army defence(" << DEFval << ") and once the province's defence(" 
                    << provDEF << "x1); so attacker's army got destroyed." << endl << endl;
            }
            else{
                cout << "CONFLICT ERROR" << endl;
            }
            
            /*clear subarmies that engaged in battle*/
            this->players[i]->regroupArmy();
            this->players[defender-1]->regroupArmy();

            /*check if defender lost game*/
            if (this->players[defender-1]->activeProvinces() == 0){
                delete this->players[defender-1];
                this->players[defender-1] = NULL;
                cout << "!!!        Player " << defender << " lost      !!!" << endl;
            }

            /*check if attacker is last player alive*/
            if( this->checkWinningCondition() ){
                return i;
            }

        }
        else{
            cout << "Player " << i+1 << " can't attack this turn!" << endl;
        }
    }

    return -1;
};

void GameBoard::economyPhase(){
    //for players
        //buy if enough money
    cout << "----------------------------  ECONOMY PHASE  -----------------------------" << endl;
    for (int i = 0; i < this->players.size(); i++)
    {
       if (this->players[i] != NULL){
           cout << "---> PLAYER's " << i+1 << " MOVE" << endl;
           this->players[i]->economyPhase();
       }
    }
};

void GameBoard::endPhase(){
    //for kai print ta panta, money = 0, discard extra cards
    cout << "----------------------------  END PHASE  -----------------------------" << endl;
    this->printGameStatistics();
    for (int i = 0; i < this->players.size(); i++)
    {
       if (this->players[i] != NULL){
           cout << "---> PLAYER's " << i+1 << " STATE:" << endl;
           this->players[i]->endPhase();
           cout << endl;
       }
    }
};

bool GameBoard::validDefender(int defender, int attacker){
    if (defender < 0) return false;
    if (defender > this->players.size()) return false;
    if (defender == attacker) return false;
    if (this->players[defender-1] == NULL) return false;
    return true;
};

bool GameBoard::checkWinningCondition(){
    int activeplayers = 0;
    for(int i = 0; i < this->players.size(); i++){
        if (this->players[i] != NULL) activeplayers++;
        if (activeplayers > 1) return false;
    }
    return true;
};

void GameBoard::printArena(){
    for (int i = 0; i < this->players.size(); i++){
         
        if(this->players[i] != NULL){
            if ( this->players[i]->activeProvinces() > 0 ){

                cout << "Player " << i+1 << " board status." << endl;
                this->players[i]->printStrongHold();
                this->players[i]->printArmy();
                this->players[i]->printProvinces();
                
            }
            cout << endl;
        }
        else{
            cout << "Player " << i+1 << " defeated!" << endl;
        }
    }
    fflush;
};

void GameBoard::printGameStatistics(){
    cout << endl << "   ************ Game Statistics ************" << endl << endl;
    cout << "Number of rounds played: " << this->roundsPlayed << endl;
    for (int i = 0; i < this->players.size(); i++){
        cout << "PLAYER " << i+1;
        if(this->players[i] == NULL){
            cout << " was defeated at round " << this->survived[i] 
                << ", attacked " << this->attacked[i]
                << " times, had to defend his provinces " << this->defended[i]
                << " times and lost all his troops " << this->annihilation[i]
                << " times." << endl;
        }
        else{
            cout << " is alive after " << this->survived[i] 
                << " rounds, attacked " << this->attacked[i]
                << " times, had to defend his provinces " << this->defended[i]
                << " times, lost all his troops " << this->annihilation[i]
                << " times and has " << this->players[i]->activeProvinces()
                << " active provinces." << endl;
        }
        
    }
    cout << endl;
};
