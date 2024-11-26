#ifndef OBSERVERS_H
#define OBSERVERS_H

#include "observer.h"
#include "subject.h"
#include "game.h"
#include <iostream>
#include <vector>
#include <memory>

// Displays the game state in text format
class TextDisplay : public Observer {
    Game& game;

public:
    // Constructor
    explicit TextDisplay(Game& g);
    // Observer override
    void notify() override;

private:
    // Helper methods
    void displayBoards(const std::vector<std::unique_ptr<Player>>& players);
    void displayBoardRow(const Player* player, const std::vector<Coordinate>& positions, int y);
};

#endif // OBSERVERS_H
