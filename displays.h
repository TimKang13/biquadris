#ifndef OBSERVERS_H
#define OBSERVERS_H
#include "observer.h"
#include "subject.h"
#include "game.h"
#include <iostream>

class TextDisplay : public Observer {
    private:
        Game& game;

    public:
        TextDisplay(Game& g) : game(g) {}

        void notify() override {
            displayBoards(game.getGameState().players);
            displayScores(game.getGameState());
        }

        void displayBoards(const std::vector<Player>& players) {
            for (int y = 15 - 1; y >= 0; y--) {
                for (int x = 0; x < 11; x++)
                    std::cout << players[0].getBoard().getCell(y, x) << " ";
                std::cout << "  ";
                for (int x = 0; x < 11; x++)
                    std::cout << players[1].getBoard().getCell(y, x) << " ";
                std::cout << "\n";
            }
        }

        void displayScores(const GameState& state) {
            std::cout << "P1: " << state.players[0].getScore() << ", P2: " << state.players[1].getScore() << "\n";
        }
};

#endif
