#include "player.h"
#include <stdexcept>
#include <memory>

Player::Player(): score{0}, level{0}, curBlock{nullptr}, nextBlock{nullptr} {}

Player::~Player() {
    delete curBlock;
    delete nextBlock;
}

void Player::applySpecialAction(const std::string& action) {}

void Player::moveLeft() {

}

void Player::moveRight() {

}

void Player::moveDown() {

}

void Player::rotateCW() {
    if (curBlock) {
        // TODO: NEEDS TO CHECK IF ROTATING IS VALID
        curBlock->rotateCW();
    }
}

void Player::rotateCCW() {
    if (curBlock) {
        // TODO: NEEDS TO CHECK IF ROTATING IS VALID
        curBlock->rotateCCW();
    }
}

void Player::drop() {
    if (curBlock) {
        
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
