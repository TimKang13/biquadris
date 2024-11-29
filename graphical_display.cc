#include "graphical_display.h"
#include <string>
#include "window.h"

const int GraphicalDisplay::CELL_SIZE = 20;
const int GraphicalDisplay::BORDER_WIDTH = 2;
const int GraphicalDisplay::PADDING = 20;
const int GraphicalDisplay::SCORE_HEIGHT = 55;
const int GraphicalDisplay::NEXT_BLOCK_SIZE = CELL_SIZE * 2;
const int GraphicalDisplay::WINDOW_WIDTH = 
    (Board::WIDTH * CELL_SIZE * 2) + // Two boards
    (PADDING * 3);                   // Padding between and around boards
const int GraphicalDisplay::WINDOW_HEIGHT = 
    SCORE_HEIGHT +                   // Score display area
    (Board::HEIGHT * CELL_SIZE) +    // Board height
    NEXT_BLOCK_SIZE +                // Next block preview
    (PADDING * 4);                   // Padding top, middle, and bottom

const int GraphicalDisplay::BOARD_COLOUR = Xwindow::Black;
const int GraphicalDisplay::TEXT_COLOUR = Xwindow::White;
    
GraphicalDisplay::GraphicalDisplay(Game& g) 
    : game(g), 
      window{std::make_unique<Xwindow>(WINDOW_WIDTH, WINDOW_HEIGHT, Xwindow::Black)} {}


void GraphicalDisplay::notify() {
    render(game.getGameState().players, game.getGameState().highScores);
}

void GraphicalDisplay::render(const std::vector<std::unique_ptr<Player>>& players,
                            const std::vector<int>& highScores) {
    int leftBoardX = PADDING;
    int rightBoardX = PADDING * 2 + Board::WIDTH * CELL_SIZE;

    // Display scores and level info
    displayScoreInfo(players[0].get(), highScores[0], leftBoardX, PADDING);
    displayScoreInfo(players[1].get(), highScores[1], rightBoardX, PADDING);
    
    // Display boards
    int boardY = PADDING + SCORE_HEIGHT + PADDING;
    displayBoard(players[0].get(), leftBoardX, boardY);
    displayBoard(players[1].get(), rightBoardX, boardY);
    
    // Display next blocks
    int nextBlockY = boardY + (Board::HEIGHT * CELL_SIZE) + PADDING;
    displayNextBlock(players[0]->getNextBlock(), leftBoardX, nextBlockY);
    displayNextBlock(players[1]->getNextBlock(), rightBoardX, nextBlockY);
}

void GraphicalDisplay::displayScoreInfo(const Player* player, int highScore, int offsetX, int offsetY) {
    window->fillRectangle(offsetX, offsetY, Board::WIDTH * CELL_SIZE, SCORE_HEIGHT, BOARD_COLOUR);
    
    int textY = offsetY;
    // Level
    window->drawString(offsetX, textY, 
        "Level: " + std::to_string(player->getLevelNumber()),
        TEXT_COLOUR);
    textY += 20;
    // High Score
    window->drawString(offsetX, textY, 
        "High Score: " + std::to_string(highScore),
        TEXT_COLOUR);
    textY += 20;
    // Current Score
    window->drawString(offsetX, textY, 
        "Score: " + std::to_string(player->getScore()),
        TEXT_COLOUR);
}


void GraphicalDisplay::displayBoard(const Player* player, int offsetX, int offsetY) {
    const auto& board = player->getBoard();
    const Block* currentBlock = player->getCurrentBlock();
    const int BLIND_COLOUR = Xwindow::Black;
    std::vector<Coordinate> blockPositions;
    
    // Board Background and outline
    window->drawRectangleWithStroke(
        offsetX,                           // x position
        offsetY,                           // y position
        Board::WIDTH * CELL_SIZE,         // width of the board
        Board::HEIGHT * CELL_SIZE,        // height of the board
        Xwindow::Black,                   // fill color (assuming you want white fill)
        Xwindow::White,                   // stroke color (black border as in original)
        BORDER_WIDTH                      // stroke width (using your existing BORDER_WIDTH)
    );

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

        // Draw grid lines
        // const int GRID_LINE_THICKNESS = 1;
        // for (int row = 0; row <= Board::HEIGHT; ++row) {
        //     int y = offsetY + (row * CELL_SIZE);
        //     window->fillRectangle(offsetX, y, Board::WIDTH * CELL_SIZE, GRID_LINE_THICKNESS, Xwindow::Black);
        // }

        // for (int col = 0; col <= Board::WIDTH; ++col) {
        //     int x = offsetX + (col * CELL_SIZE);
        //     window->fillRectangle(x, offsetY, GRID_LINE_THICKNESS, Board::HEIGHT * CELL_SIZE, Xwindow::Black);
        // }
    }
}

void GraphicalDisplay::displayNextBlock(const Block* nextBlock, int offsetX, int offsetY) {
    if (!nextBlock) return;
    
    window->drawString(offsetX, offsetY, "Next Block: ", TEXT_COLOUR);
    
    const auto& shape = nextBlock->getShape();
    const int colour = getColourFromFill(nextBlock->getFill());
    const int previewOffsetX = offsetX + 70;
    
    // Calculate which row to start based on preview height
    const int PREVIEW_HEIGHT = 2;
    size_t startRow = (shape.size() > PREVIEW_HEIGHT) ? 
                      (shape.size() - PREVIEW_HEIGHT) : 0;
    
    // Clear preview
    const int PREVIEW_WIDTH = 4;
    const int previewHeightPx = PREVIEW_HEIGHT * CELL_SIZE;
    const int previewWidthPx = PREVIEW_WIDTH * CELL_SIZE;
    window->fillRectangle(previewOffsetX, offsetY, previewWidthPx, previewHeightPx, BOARD_COLOUR);

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
        case 'I': return Xwindow::Teal;
        case 'J': return Xwindow::SkyBlue;
        case 'L': return Xwindow::Orange;
        case 'O': return Xwindow::Yellow;
        case 'S': return Xwindow::Lime;
        case 'Z': return Xwindow::Scarlet;
        case 'T': return Xwindow::Purple;
        case '*': return Xwindow::Brown;
        default: return BOARD_COLOUR;
    }
}
