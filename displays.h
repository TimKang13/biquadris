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
        }

        void displayBoards(const std::vector<std::unique_ptr<Player>>& players) {
            std::cout << std::string(Board::WIDTH, '-') << "\t" << std::string(Board::WIDTH, '-') << "\n";
            // Print board contents
            for (int y = 0; y < Board::HEIGHT; y++) {
                for (int x = 0; x < Board::WIDTH; x++) std::cout << players[0]->getBoard().getCell(y, x);
                std::cout << "\t";
                for (int x = 0; x < Board::WIDTH; x++) std::cout << players[1]->getBoard().getCell(y, x);
                std::cout << "\n";
            }
            std::cout << std::string(Board::WIDTH, '-') << "\t" << std::string(Board::WIDTH, '-') << "\n";
        }
};

#endif
