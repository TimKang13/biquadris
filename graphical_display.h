#ifndef GRAPHICAL_DISPLAY_H
#define GRAPHICAL_DISPLAY_H

#include "observer.h"
#include "game.h"
#include "window.h"
#include <memory>

class GraphicalDisplay : public Observer {
    Game& game;
    std::unique_ptr<Xwindow> window;
    
    // Constants for display
    static const int CELL_SIZE;
    static const int BORDER_WIDTH;
    static const int PADDING;
    static const int SCORE_HEIGHT;
    static const int NEXT_BLOCK_SIZE;
    static const int WINDOW_WIDTH;
    static const int WINDOW_HEIGHT;

    static const int BOARD_COLOUR;
    static const int TEXT_COLOUR;

public:
    explicit GraphicalDisplay(Game& g);
    void notify() override;

private:
    void render(const GameState& gameState);
    void displayScoreInfo(const Player* player, int highScore, int offsetX, int offsetY);
    void displayBoard(const Player* player, int offsetX, int offsetY);
    void displayNextBlock(const Block* nextBlock, int offsetX, int offsetY);
    
    // Helper to convert char to colour
    int getColourFromFill(char c) const;
};

#endif