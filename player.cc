#include "player.h"
#include "levels.h"
#include <stdexcept>
#include <memory>

Player::Player(): score{0}, level{std::make_unique<LevelZero>()}, currentBlock{nullptr}, nextBlock{nullptr} {}

Player::Player(int levelNum): score{0}, currentBlock{nullptr}, nextBlock{nullptr} {
    switch(levelNum){
        case 0:
            level = std::make_unique<LevelZero>();
            break;
        case 1:
            level = std::make_unique<LevelOne>();
            break;
        case 2:
            level = std::make_unique<LevelTwo>();
            break;
        case 3:
            level = std::make_unique<LevelThree>();
            break;
        case 4:
            level = std::make_unique<LevelFour>();
            break;
        default:
            throw std::invalid_argument("Invalid level");
    }
}


Player::~Player() {}

void Player::applySpecialAction(const std::string& action) {}

void Player::moveLeft() {
    if (!currentBlock) return;
    Coordinate oldPos = currentBlock->getPosition();
    Coordinate newPos = currentBlock->getPosition();
    newPos.col--;
    currentBlock->setPosition(newPos);
    bool valid = newPos.col >= 0 && !board.checkCollision(*currentBlock);
    if (!valid) currentBlock->setPosition(oldPos);
}

void Player::moveRight() {
    if (!currentBlock) return;
    Coordinate oldPos = currentBlock->getPosition();
    Coordinate newPos = currentBlock->getPosition();
    newPos.col++;
    currentBlock->setPosition(newPos);
    bool valid = newPos.col <= Board::WIDTH - 1 && !board.checkCollision(*currentBlock);
    if (!valid) currentBlock->setPosition(oldPos);
}

void Player::moveDown() {
    if (!currentBlock) return;
    Coordinate oldPos = currentBlock->getPosition();
    Coordinate newPos = currentBlock->getPosition();
    newPos.row++;
    currentBlock->setPosition(newPos);
    bool valid = newPos.row <= Board::HEIGHT - 1 && !board.checkCollision(*currentBlock);
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

bool Player::drop() {
    if (!currentBlock) return false;
    Coordinate oldPos = currentBlock->getPosition();
    Coordinate newPos = currentBlock->getPosition();
    for(int row = Board::HEIGHT - 1; row >= 0; --row){
        newPos.row = row;
        currentBlock->setPosition(newPos);
        if(!board.checkCollision(*currentBlock)){
            //can place!!
            int points = board.placeBlock(*currentBlock, level->getLevelNumber());
            score += points;
            return true;
        }
    }
    currentBlock->setPosition(oldPos);
    return false;
}

void Player::advanceBlock(){

}

// Getters
int Player::getScore() const { return score; }
int Player::getLevelNumber() const { return level->getLevelNumber(); }
const Board& Player::getBoard() const { return board; }
const Block* Player::getCurrentBlock() const { return currentBlock.get(); }
const Block* Player::getNextBlock() const { return nextBlock.get(); }

// Setters
void Player::setScore(int newScore) { score = newScore; }
void Player::setLevel(int newLevel) { 
    switch (newLevel) {
        case 0:
            level = std::make_unique<LevelZero>();
            break;
        case 1:
            level = std::make_unique<LevelOne>();
            break;
        case 2:
            level = std::make_unique<LevelTwo>();
            break;
        case 3:
            level = std::make_unique<LevelThree>();
            break;
        case 4:
            level = std::make_unique<LevelFour>();
            break;
        default:
            throw std::invalid_argument("Invalid level");
    }
}

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
