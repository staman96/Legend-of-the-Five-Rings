# Legend-of-the-Five-Rings
It's simplified version of the card game Legend of the Five Rings. A big project for 2 students in Object Oriented Programming course to use all basic data structures and more(enum, type conversion etc).  

Manolas Stamatios and Skordoulis Dimitrios, OOP Project 2019/2020


## Simplified Game Rule changes and additions:

  The game is played with at least 2 players. Every player starts with 4 cards and 4 Provinces (Holdings/Personalities). Each Personality can have 10 green cards (followers/items) maximum. At the beggining of each round, every player must harvest the money from its Stronghold and Holdings. These money are tapped after a winning bid. During the battle Phase each player can attack only once. In a battle, the attacker wins if his total attack stats are equal or better than the defender's defence stats. Also, at end of the battle phase it is checked if a player won. After, the End Phase, there is a choice to end the game. Lastly, when the Fate Deck runs out of cards, the player gets a message about it; but if the Dynasty Deck runs out of cards, then the player looses the province that used to buy the card. If a player is left with only 1 province, then he can't buy the last card because he would loose the game.
  
### General:

* Compilation is done with make, and make clean is used to remove to .o (object files).
* The command to run the game is:

      ./L5R
* We used Valgind and we have no erros:

      make clean && make && valgrind -v --leak-check=yes --show-leak-kinds=all --track-origins=yes ./L5R




