#include "graphical_display.h"
#include <string>

const int GraphicalDisplay::CELL_SIZE = 20;
const int GraphicalDisplay::PADDING = 20;
const int GraphicalDisplay::SCORE_HEIGHT = 60;
const int GraphicalDisplay::NEXT_BLOCK_SIZE = 40;
const int GraphicalDisplay::WINDOW_WIDTH = 
    (Board::WIDTH * GraphicalDisplay::CELL_SIZE * 2) + // Two boards
    (GraphicalDisplay::PADDING * 3);                   // Padding between and around boards
const int GraphicalDisplay::WINDOW_HEIGHT = 
    GraphicalDisplay::SCORE_HEIGHT +                   // Score display area
    (Board::HEIGHT * GraphicalDisplay::CELL_SIZE) +    // Board height
    GraphicalDisplay::NEXT_BLOCK_SIZE +                // Next block preview
    (GraphicalDisplay::PADDING * 3);                   // Padding top, middle, and bottom
    
GraphicalDisplay::GraphicalDisplay(Game& g) 
    : game(g), 
      window{std::make_unique<Xwindow>(WINDOW_WIDTH, WINDOW_HEIGHT)} {}


void GraphicalDisplay::notify() {
    render(game.getGameState().players, game.getGameState().highScores);
}

void GraphicalDisplay::render(const std::vector<std::unique_ptr<Player>>& players,
                            const std::vector<int>& highScores) {
    // Clear window
    window->fillRectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, Xwindow::White);
    
    // Display scores and level info
    displayScoreInfo(players, highScores);
    
    // Display boards
    int leftBoardX = PADDING;
    int rightBoardX = PADDING * 2 + Board::WIDTH * CELL_SIZE;
    displayBoard(players[0].get(), leftBoardX);
    displayBoard(players[1].get(), rightBoardX);
    
    // Display next blocks
    int nextBlockY = SCORE_HEIGHT + (Board::HEIGHT * CELL_SIZE) + PADDING;
    displayNextBlock(players[0]->getNextBlock(), leftBoardX);
    displayNextBlock(players[1]->getNextBlock(), rightBoardX);
}

void GraphicalDisplay::displayScoreInfo(const std::vector<std::unique_ptr<Player>>& players,
                                      const std::vector<int>& highScores) {
    // Display info for both players
    for (int i = 0; i < 2; ++i) {
        int offsetX = i * (WINDOW_WIDTH / 2);
        int textY = 20;
        
        // Level
        window->drawString(PADDING + offsetX, textY, 
            "Level: " + std::to_string(players[i]->getLevelNumber()));
        
        // High Score
        window->drawString(PADDING + offsetX, textY + 20, 
            "High Score: " + std::to_string(highScores[i]));
        
        // Current Score
        window->drawString(PADDING + offsetX, textY + 40, 
            "Score: " + std::to_string(players[i]->getScore()));
    }
}

void GraphicalDisplay::displayBoard(const Player* player, int offsetX) {
    const auto& board = player->getBoard();
    const Block* currentBlock = player->getCurrentBlock();
    std::vector<Coordinate> blockPositions;
    
    // Get current block positions if there is one
    if (currentBlock) {
        blockPositions = currentBlock->getAbsolutePositions();
    }
    
    // Draw board cells
    for (int row = 0; row < Board::HEIGHT; ++row) {
        for (int col = 0; col < Board::WIDTH; ++col) {
            int x = offsetX + (col * CELL_SIZE);
            int y = SCORE_HEIGHT + (row * CELL_SIZE);
            
            // Check if current position contains block
            bool isBlock = std::any_of(blockPositions.begin(), blockPositions.end(),
                [row, col](const Coordinate& pos) { 
                    return pos.row == row && pos.col == col; 
                });
            
            // Determine cell color
            int color;
            if (isBlock) {
                color = getColorFromChar(currentBlock->getFill());
            } else {
                color = getColorFromChar(board.getCellChar(row, col));
            }
            
            // Draw cell
            window->fillRectangle(x, y, CELL_SIZE, CELL_SIZE, color);
        }
    }
}

void GraphicalDisplay::displayNextBlock(const Block* nextBlock, int offsetX) {
    if (!nextBlock) return;
    
    const auto& shape = nextBlock->getShape();
    int color = getColorFromChar(nextBlock->getFill());
    int baseY = SCORE_HEIGHT + (Board::HEIGHT * CELL_SIZE) + PADDING;
    
    // Draw preview
    for (size_t row = 0; row < shape.size(); ++row) {
        for (size_t col = 0; col < shape[row].size(); ++col) {
            if (shape[row][col]) {
                int x = offsetX + (col * CELL_SIZE);
                int y = baseY + (row * CELL_SIZE);
                window->fillRectangle(x, y, CELL_SIZE, CELL_SIZE, color);
            }
        }
    }
}

int GraphicalDisplay::getColorFromChar(char c) const {
    switch (c) {
        case 'I': return Xwindow::Red;
        case 'J': return Xwindow::Blue;
        case 'L': return Xwindow::Green;
        case 'O': return Xwindow::Red;
        case 'S': return Xwindow::Blue;
        case 'Z': return Xwindow::Green;
        case 'T': return Xwindow::Blue;
        case '*': return Xwindow::Black;
        default: return Xwindow::White;
    }
}