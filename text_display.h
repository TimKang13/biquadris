#ifndef TEXT_DISPLAY_H
#define TEXT_DISPLAY_H

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
    // Constants
    static const int WIDTH = 12;
    static const char SPACE = '\t';
    // Constructor
    explicit TextDisplay(Game& g);
    // Observer override
    void notify() override;

private:
    // Helper methods
    void render(const std::vector<std::unique_ptr<Player>>& players, const std::vector<int>& highScores);
    void displayScoreInfo(const std::vector<std::unique_ptr<Player>>& players,
                                 const std::vector<int>& highScores);
    void displayBoardRow(const Player* player, const std::vector<Coordinate>& blockCords, int row);

    void displayNextBlocks(const Block* nextBlock1, const Block* nextBlock2);
};

#endif
