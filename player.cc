#include "player.h"
#include <stdexcept>

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
const Block* Player::getCurrentBlock() const { return curBlock; }
const Block* Player::getNextBlock() const { return nextBlock; }

// Setters
void Player::setScore(int newScore) { score = newScore; }
void Player::setLevel(int newLevel) { level = newLevel; }
