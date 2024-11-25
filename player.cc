#include "player.h"
#include <stdexcept>
#include <memory>

Player::Player(): score{0}, level{0}, currentBlock{nullptr}, nextBlock{nullptr} {}

Player::~Player() {}

void Player::applySpecialAction(const std::string& action) {}

void Player::moveLeft() {
    if (!currentBlock) return;
    Coordinate oldPos = currentBlock->getPosition();
    Coordinate newPos = currentBlock->getPosition();
    newPos.col--;
    currentBlock->setPosition(newPos);
    bool valid = !board.checkCollision(*currentBlock);
    if (!valid) currentBlock->setPosition(oldPos);
}

void Player::moveRight() {
    if (!currentBlock) return;
    Coordinate oldPos = currentBlock->getPosition();
    Coordinate newPos = currentBlock->getPosition();
    newPos.col++;
    currentBlock->setPosition(newPos);
    bool valid = !board.checkCollision(*currentBlock);
    if (!valid) currentBlock->setPosition(oldPos);
}

void Player::moveDown() {
    if (!currentBlock) return;
    Coordinate oldPos = currentBlock->getPosition();
    Coordinate newPos = currentBlock->getPosition();
    newPos.row++;
    currentBlock->setPosition(newPos);
    bool valid = !board.checkCollision(*currentBlock);
    if (!valid) currentBlock->setPosition(oldPos);
}

void Player::rotateCW() {
    if (!currentBlock) return;
    currentBlock->rotateCW();
    bool valid = !board.checkCollision(*currentBlock);
    if (!valid) currentBlock->rotateCCW();
}

void Player::rotateCCW() {
    if (!currentBlock) return;
    currentBlock->rotateCW();
    bool valid = !board.checkCollision(*currentBlock);
    if (!valid) currentBlock->rotateCCW();
}

void Player::drop() {
    if (currentBlock) {
        
    }
}

// Getters
int Player::getScore() const { return score; }
int Player::getLevel() const { return level; }
const Board& Player::getBoard() const { return board; }
const Block* Player::getCurrentBlock() const { return currentBlock.get(); }
const Block* Player::getNextBlock() const { return nextBlock.get(); }

// Setters
void Player::setScore(int newScore) { score = newScore; }
void Player::setLevel(int newLevel) { level = newLevel; }
void Player::setCurrentBlock(char blockChar) {
    // Reset the current block
    currentBlock.reset();
    // Create a new block based on the blockChar
    switch (blockChar) {
        case 'I':
            currentBlock = std::make_unique<IBlock>();
            break;
        case 'J':
            currentBlock = std::make_unique<JBlock>();
            break;
        case 'L':
            currentBlock = std::make_unique<LBlock>();
            break;
        case 'O':
            currentBlock = std::make_unique<OBlock>();
            break;
        case 'S':
            currentBlock = std::make_unique<SBlock>();
            break;
        case 'Z':
            currentBlock = std::make_unique<ZBlock>();
            break;
        case 'T':
            currentBlock = std::make_unique<TBlock>();
            break;
        default:
            throw std::invalid_argument("Invalid block type");
    }
}
