#include <bits/stdc++.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <cmath>
#include <cfloat>
#include <list> 
#include <iterator> 
#include <time.h>

#include "cards/BlackCards.h"
#include "cards/Card.h"
#include "cards/Follower.h"
#include "cards/GreenCards.h"
#include "cards/Holding.h"
#include "cards/Item.h"
#include "cards/Personality.h"
#include "GameBoard.h"
#include "Player.h"
#include "DeckBuilder.h"
#include "TypeConverter.h"

using namespace std;

int main() //main function of the program
{
    srand(unsigned(time(NULL)));
 
    int numofPlayers;
    cout << endl << "Welcome to Legend of the Five Rings(almost)" << endl << endl;
    cout << "Choose number of players( > 1, default 2)" << endl;
    cin >> numofPlayers;

    if (numofPlayers < 2) numofPlayers = 2;

    GameBoard * gameboard = new GameBoard(numofPlayers);
    gameboard->GamePlay();
  
    delete gameboard;
}