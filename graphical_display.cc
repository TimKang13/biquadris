#include "graphical_display.h"
#include <string>

const int GraphicalDisplay::CELL_SIZE = 20;
const int GraphicalDisplay::BORDER_WIDTH = 3;
const int GraphicalDisplay::PADDING = 20;
const int GraphicalDisplay::SCORE_HEIGHT = 60;
const int GraphicalDisplay::NEXT_BLOCK_SIZE = CELL_SIZE * 2;
const int GraphicalDisplay::WINDOW_WIDTH = 
    (Board::WIDTH * CELL_SIZE * 2) + // Two boards
    (PADDING * 3);                   // Padding between and around boards
const int GraphicalDisplay::WINDOW_HEIGHT = 
    SCORE_HEIGHT +                   // Score display area
    (Board::HEIGHT * CELL_SIZE) +    // Board height
    NEXT_BLOCK_SIZE +                // Next block preview
    (PADDING * 3);                   // Padding top, middle, and bottom
    
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
    
    int leftBoardX = PADDING;
    int rightBoardX = PADDING * 2 + Board::WIDTH * CELL_SIZE;

    // Display scores and level info
    displayScoreInfo(players[0].get(), highScores[0], leftBoardX, PADDING);
    displayScoreInfo(players[1].get(), highScores[0], rightBoardX, PADDING);
    
    // Display boards
    int boardY = SCORE_HEIGHT + PADDING;
    displayBoard(players[0].get(), leftBoardX, boardY);
    displayBoard(players[1].get(), rightBoardX, boardY);
    
    // Display next blocks
    int nextBlockY = SCORE_HEIGHT + PADDING + (Board::HEIGHT * CELL_SIZE) + PADDING;
    displayNextBlock(players[0]->getNextBlock(), leftBoardX, nextBlockY);
    displayNextBlock(players[1]->getNextBlock(), rightBoardX, nextBlockY);
}

void GraphicalDisplay::displayScoreInfo(const Player* player, int highScore, int offsetX, int offsetY) {
    int textY = offsetY;
    // Level
    window->drawString(offsetX, textY, 
        "Level: " + std::to_string(player->getLevelNumber()));
    textY += 20;
    // High Score
    window->drawString(offsetX, textY, 
        "High Score: " + std::to_string(highScore));
    textY += 20;
    // Current Score
    window->drawString(offsetX, textY, 
        "Score: " + std::to_string(player->getScore()));
}


void GraphicalDisplay::displayBoard(const Player* player, int offsetX, int offsetY) {
    const auto& board = player->getBoard();
    const Block* currentBlock = player->getCurrentBlock();
    const int BLIND_COLOUR = Xwindow::Black;
    std::vector<Coordinate> blockPositions;
    
    // Left border
    window->fillRectangle(offsetX - BORDER_WIDTH,
                          offsetY - BORDER_WIDTH, 
                          BORDER_WIDTH, 
                          Board::HEIGHT * CELL_SIZE + (BORDER_WIDTH * 2), 
                          Xwindow::Black);
    // Right border
    window->fillRectangle(Board::WIDTH * CELL_SIZE + offsetX,
                          offsetY - BORDER_WIDTH, 
                          BORDER_WIDTH, 
                          Board::HEIGHT * CELL_SIZE + (BORDER_WIDTH * 2), 
                          Xwindow::Black);
    // Top border
    window->fillRectangle(offsetX - BORDER_WIDTH,
                          offsetY - BORDER_WIDTH, 
                          Board::WIDTH * CELL_SIZE + (BORDER_WIDTH * 2),
                          BORDER_WIDTH,
                          Xwindow::Black);
    // Bottom border
    window->fillRectangle(offsetX - BORDER_WIDTH,
                          offsetY + (Board::HEIGHT * CELL_SIZE),
                          Board::WIDTH * CELL_SIZE + (BORDER_WIDTH * 2),
                          BORDER_WIDTH,
                          Xwindow::Black);

    // Get current block positions if there is one
    if (currentBlock) blockPositions = currentBlock->getAbsolutePositions();
    
    // Draw board cells
    for (int row = 0; row < Board::HEIGHT; ++row) {
        int currentWidth = 1;
        int startCol = 0;
        const int INVALID_COLOUR = -1;
        int prevColour = INVALID_COLOUR;
        
        for (int col = 0; col <= Board::WIDTH; ++col) {
            // Check if current position contains block
            bool isBlock = std::any_of(blockPositions.begin(), blockPositions.end(),
                [row, col](const Coordinate& pos) {
                    return pos.row == row && pos.col == col;
                });
            // Determine cell colour
            int currentColour;
            if (player->isBlind() && 2 <= row && row <= 11 && 2 <= col && col <= 8) {
                currentColour = BLIND_COLOUR;
            } else {
                if (isBlock) {
                    currentColour = getColourFromFill(currentBlock->getFill());
                } else {
                    currentColour = getColourFromFill(board.getCellChar(row, col));
                }
            }
            // If colour changes or we're at the end of the row, draw the accumulated rectangle
            if (currentColour != prevColour || col == Board::WIDTH - 1) {
                if (prevColour != INVALID_COLOUR) {
                    int x = offsetX + (startCol * CELL_SIZE);
                    int y = offsetY + (row * CELL_SIZE);
                    window->fillRectangle(x, y, currentWidth * CELL_SIZE, CELL_SIZE, prevColour);
                }
                // Reset for new colour
                startCol = col;
                currentWidth = 1;
            } else {
                currentWidth++;
            }
            prevColour = currentColour;
        }
    }
}

void GraphicalDisplay::displayNextBlock(const Block* nextBlock, int offsetX, int offsetY) {
    if (!nextBlock) return;
    
    window->drawString(offsetX, offsetY, "Next Block: ");
    
    const auto& shape = nextBlock->getShape();
    const int colour = getColourFromFill(nextBlock->getFill());
    const int previewOffsetX = offsetX + 70;
    
    // Calculate which row to start based on preview height
    const int PREVIEW_HEIGHT = 2;
    size_t startRow = (shape.size() > PREVIEW_HEIGHT) ? 
                      (shape.size() - PREVIEW_HEIGHT) : 0;
    
    // Draw preview
    for (size_t row = startRow; row < shape.size(); ++row) {
        for (size_t col = 0; col < shape[row].size(); ++col) {
            if (shape[row][col]) {
                int x = previewOffsetX + (col * CELL_SIZE);
                int y = offsetY + ((row - startRow) * CELL_SIZE);
                window->fillRectangle(x, y, CELL_SIZE, CELL_SIZE, colour);
            }
        }
    }
}

int GraphicalDisplay::getColourFromFill(char c) const {
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
