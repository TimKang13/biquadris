#ifndef GAME_H
#define GAME_H
#include "player.h"
#include "command_interpreter.h"
#include <vector>
#include <utility>
#include <string>
#include "subject.h"
#include <memory>
using namespace std;

struct GameState {
    std::vector<std::unique_ptr<Player>> players;
};

class Game: public Subject {
    std::vector<std::unique_ptr<Player>> players;
    std::vector<int> highScores;

    bool turn;
    bool isGameOver;
    CommandInterpreter CI;
    int numTotalMoves;

    public:
        //ctor and dtor
        Game(std::vector<std::unique_ptr<Player>>& playerList, CommandInterpreter& CI);
        ~Game();
        void startGame();
        void endGame();
        void restartGame();
        void endProgram();
        void switchPlayer();
        pair<int,string> getUserCmd();
        void executeCmd(string cmd);
        void updateDisplay();
        GameState getGameState() {return {.players = players};}

        //getters
        Player getPlayer1() const;
        Player getPlayer2() const;
        //CommandInterpreter getCI() const;

        //setters
        void setPlayer1(Player& p);
        void setPlayer2(Player& p);
};

#endif