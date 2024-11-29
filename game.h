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
    const std::vector<std::unique_ptr<Player>>& players;
    const std::vector<int>& highScores;
    int numTotalMoves;
};

class Game: public Subject {
    std::vector<std::unique_ptr<Player>> players;
    std::vector<int> highScores;
    bool turn;
    bool isGameOver;
    CommandInterpreter CI;
    int numTotalMoves;

    public:
        Game(std::vector<std::unique_ptr<Player>>&& playerList, CommandInterpreter& CI);
        ~Game() = default;
        void startGame();
        void endGame();
        void restartGame();
        void endProgram();
        void startTurn();
        void endTurn();
        pair<int,string> getUserCmd();
        void executeCmd(string cmd, int moveRemaining);
        void updateDisplay();
        GameState getGameState() const;

        //getters
        Player getPlayer1() const;
        Player getPlayer2() const;
        //CommandInterpreter getCI() const;

        //setters
        void setPlayer1(Player& p);
        void setPlayer2(Player& p);
};

#endif
