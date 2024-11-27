#include "displays.h"
#include <iomanip>

// CONSTRUCTOR
TextDisplay::TextDisplay(Game& g) : game(g) {}

// NOTIFY
void TextDisplay::notify() {
    render(game.getGameState().players, game.getGameState().highScores);
}

// RENDER GAME
void TextDisplay::render(const std::vector<std::unique_ptr<Player>>& players, const std::vector<int>& highScores) {
    const std::string border = std::string(Board::WIDTH, '-');
    // Score and level info
    displayScoreInfo(players, highScores);
    // Top border
    std::cout << border << SPACE << border << "\n";
    // Game boards row by row
    const auto blockCords0 = players[0]->getCurrentBlock() ? 
        players[0]->getCurrentBlock()->getAbsolutePositions() : std::vector<Coordinate>{};
    const auto blockCords1 = players[1]->getCurrentBlock() ? 
        players[1]->getCurrentBlock()->getAbsolutePositions() : std::vector<Coordinate>{};
    for (int row = 0; row < Board::HEIGHT; ++row) {
        displayBoardRow(players[0].get(), blockCords0, row);
        std::cout << SPACE;
        displayBoardRow(players[1].get(), blockCords1, row);
        std::cout << "\n";
    }
    // Bottom border
    std::cout << border << SPACE << border << "\n";
    // Next blocks
    displayNextBlocks(players[0]->getNextBlock(), players[1]->getNextBlock());
}

// DISPLAY SCORE AND LEVEL INFO
void TextDisplay::displayScoreInfo(const std::vector<std::unique_ptr<Player>>& players,
                                 const std::vector<int>& highScores) {
    // Levels
    std::cout << std::left 
              << std::setw(WIDTH) << "Level:" << players[0]->getLevelNumber()
              << SPACE 
              << std::setw(WIDTH) << "Level:" << players[1]->getLevelNumber() 
              << "\n";
    // High scores
    std::cout << std::left 
              << std::setw(WIDTH) << "High Score:" << highScores[0]
              << SPACE 
              << std::setw(WIDTH) << "High Score:" << highScores[1] 
              << "\n";
    // Current scores
    std::cout << std::left 
              << std::setw(WIDTH) << "Score:" << players[0]->getScore()
              << SPACE 
              << std::setw(WIDTH) << "Score:" << players[1]->getScore() 
              << "\n";
}

// DISPLAY A SINGLE ROW OF A PLAYER'S BOARD
void TextDisplay::displayBoardRow(const Player* player, const std::vector<Coordinate>& blockCords, int row) {
    const Block* block = player->getCurrentBlock();
    for (int col = 0; col < Board::WIDTH; ++col) {
        bool isBlock = std::any_of(blockCords.begin(), blockCords.end(),
            [row, col](const Coordinate& pos) { return pos.row == row && pos.col == col; });
        std::cout << (isBlock ? block->getFill() : player->getBoard().getCell(row, col));
    }
}

// DISPLAY NEXT BLOCKS
void TextDisplay::displayNextBlocks(const Block* nextBlock1, const Block* nextBlock2) {
    const auto shape1 = nextBlock1->getShape();
    const char fill1 = nextBlock1->getFill();
    const auto shape2 = nextBlock2->getShape();
    const char fill2 = nextBlock1->getFill();
    
    // Display next blocks header
    std::cout << std::left 
              << std::setw(Board::WIDTH) << "Next:" 
              << SPACE
              << std::left 
              << std::setw(Board::WIDTH) << "Next:"
              << "\n";

    // Display preview rows
    const int PREVIEW_HEIGHT = 2;
    for (int i = 0; i < PREVIEW_HEIGHT; ++i) {
        // Calculate which row of the shape to show
        size_t shapeRow1 = nextBlock1 ? 
            (shape1.size() - PREVIEW_HEIGHT + i) : 0;
        size_t shapeRow2 = nextBlock2 ? 
            (shape1.size() - PREVIEW_HEIGHT + i) : 0;
        // Get shape row strings
        std::string leftPreview = "";
        std::string rightPreview = "";
        for (size_t col = 0; col < shape1[shapeRow1].size(); ++col) {
            leftPreview += (shape1[shapeRow1][col] ? fill1 : ' ');
        }
        for (size_t col = 0; col < shape2[shapeRow2].size(); ++col) {
            rightPreview += (shape2[shapeRow2][col] ? fill2 : ' ');
        }
        // print shape rows
        std::cout << std::left << std::setw(Board::WIDTH) << leftPreview
                  << SPACE << std::left << std::setw(Board::WIDTH) << rightPreview
                  << "\n";
    }
}
