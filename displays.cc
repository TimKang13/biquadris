#include "displays.h"
#include <iomanip>

// Constructor
TextDisplay::TextDisplay(Game& g) : game(g) {}

// Notification handler
void TextDisplay::notify() {
    displayBoards(game.getGameState().players, game.getGameState().highScores);
}

// Displays the boards of both players
void TextDisplay::displayBoards(const std::vector<std::unique_ptr<Player>>& players, const std::vector<int>& highScores) {
    const std::string border = std::string(Board::WIDTH, '-');
    const char SPACE = '\t';
    const int WIDTH = 12;

    // Display levels and scores
    std::cout << std::left << std::setw(WIDTH) << "Level:"
              << players[0]->getLevelNumber()
              << SPACE << std::setw(WIDTH) << "Level:"
              << players[1]->getLevelNumber() << "\n";

    std::cout << std::left << std::setw(WIDTH) << "High Score:"
              << highScores[0]
              << SPACE << std::setw(WIDTH) << "High Score:"
              << highScores[1] << "\n";

    std::cout << std::left << std::setw(WIDTH) << "Score:"
              << players[0]->getScore()
              << SPACE << std::setw(WIDTH) << "Score:"
              << players[1]->getScore() << "\n";

    // Display top border
    std::cout << border << SPACE << border << "\n";

    // Get block positions
    const auto positions0 = players[0]->getCurrentBlock() ? 
        players[0]->getCurrentBlock()->getAbsolutePositions() : std::vector<Coordinate>{};
    const auto positions1 = players[1]->getCurrentBlock() ? 
        players[1]->getCurrentBlock()->getAbsolutePositions() : std::vector<Coordinate>{};

    // Display game boards row by row
    for (int y = 0; y < Board::HEIGHT; ++y) {
        displayBoardRow(players[0].get(), positions0, y);
        std::cout << SPACE;
        displayBoardRow(players[1].get(), positions1, y);
        std::cout << "\n";
    }

    // Display bottom border
    std::cout << border << SPACE << border << "\n";
}

// Displays a single row of a player's board
void TextDisplay::displayBoardRow(const Player* player, const std::vector<Coordinate>& positions, int y) {
    const Block* block = player->getCurrentBlock();
    for (int x = 0; x < Board::WIDTH; ++x) {
        bool isBlock = std::any_of(positions.begin(), positions.end(),
            [y, x](const Coordinate& pos) { return pos.row == y && pos.col == x; });
        std::cout << (isBlock ? block->getFill() : player->getBoard().getCell(y, x));
    }
}
