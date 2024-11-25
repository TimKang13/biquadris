#ifndef GAME_H
#define GAME_H
#include <player.h>
#include <vector>
#include <utility>
#include <string>
using namespace std;

struct GameState {

};

class Game {
    std::vector<Player> players;
    bool turn;
    CommandInterpreter CI;
    int numTotalMoves;

    public:
        //ctor and dtor
        Game(std::vector<Player>& playerList, CommandLineInterpreter& CI);
        ~Game();
        void startGame();
        void switchPlayer();
        pair<int,string> getUserCmd();
        void executeCmd(string cmd);
        void updateDisplay();
        GameState getGameState();

        //getters
        Player getPlayer1() const;
        Player getPlayer2() const;
        //CommandInterpreter getCI() const;

        //setters
        void setPlayer1(Player& p);
        void setPlayer2(Player& p);
};

#endif