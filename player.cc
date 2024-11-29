#include "player.h"
#include "levels.h"
#include <stdexcept>
#include <iostream>
#include <memory>
#include <fstream>
using namespace std;

// default constructor
Player::Player(std::string fileName): sequenceFile{fileName}, heavy{false}, blind{false}, bonusEnabled{false}{
    level = std::make_unique<LevelZero>(sequenceFile);
    currentBlock = nullptr;
    nextBlock = level->getBlock();
}

// constructor with cmd line args
Player::Player(std::string fileName, int levelNum, int seed): seed{seed}, sequenceFile{fileName}, heavy{false}, blind{false}, bonusEnabled{false}{
    switch(levelNum){
        case 0:
            level = std::make_unique<LevelZero>(sequenceFile);
            break;
        case 1:
            level = std::make_unique<LevelOne>(seed);
            break;
        case 2:
            level = std::make_unique<LevelTwo>(seed);
            break;
        case 3:
            level = std::make_unique<LevelThree>(seed);
            break;
        case 4:
            level = std::make_unique<LevelFour>(seed);
            break;
        default:
            throw std::invalid_argument("Invalid level");
    }
    currentBlock = nullptr;
    nextBlock = level->getBlock();
}


Player::~Player() {}

void Player::removeSpecialAction(){
    heavy = false;
    blind = false;
}

void Player::applySpecialAction(const std::string& action) {
    if(action == "blind"){
        applyBlind();
    } else if(action == "heavy"){
        applyHeavy();
    } else if (action.substr(0, 5) == "force"){
        char blockChar = action[6];
        applyForce(blockChar);
    } else {
        cout << "invalid special action string" << endl;
    }
}

//special actions
void Player::applyHeavy(){
    heavy = true;
}
void Player::applyBlind(){
    blind = true;
}
void Player::applyForce(char blockChar){
    //applied when the player's next block is not yet current block.
    int life = 0;
    bool invincible = true;
    if(dynamic_cast<LevelOne*>(level.get())){
        //generate block with life when level one
        life = 10;
        invincible = false;
    }
    nextBlock = createBlock(std::string(1, std::tolower(blockChar)) + "block", life, invincible);
}

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
    bool valid = newPos.row <= Board::HEIGHT - 1 && !board.checkCollision(*currentBlock);
    if (!valid) currentBlock->setPosition(oldPos);
}

void Player::rotateCW() {
    if (!currentBlock) return;
    currentBlock->rotateCW();
    bool valid = !board.checkCollision(*currentBlock, true);
    if (!valid) currentBlock->rotateCCW();
}

void Player::rotateCCW() {
    if (!currentBlock) return;
    currentBlock->rotateCCW();
    bool valid = !board.checkCollision(*currentBlock, true);
    if (!valid) currentBlock->rotateCW();
}


int Player::placeOneBlock(unique_ptr<Block> oneBlock) {
    Coordinate newPos = oneBlock->getPosition();
    while(!board.checkCollision(*oneBlock)) {
        newPos.row++;
        oneBlock->setPosition(newPos);
    }
    if(newPos.row == 0) return -1;
    newPos.row -= 1;
    oneBlock->setPosition(newPos);
    return board.placeBlock(*oneBlock, level->getLevelNumber());
 
}
bool Player::drop() {
    int currentCleared = board.getRowsCleared();
    if (!currentBlock) return false;
    Coordinate newPos = currentBlock->getPosition();
    while(!board.checkCollision(*currentBlock)) {
        newPos.row++;
        currentBlock->setPosition(newPos);
    }
    if(newPos.row == 0) return false;
    newPos.row -= 1;
    currentBlock->setPosition(newPos);  
    score += board.placeBlock(*currentBlock, level->getLevelNumber());

    if(getLevelNumber() == 4 && currentCleared == board.getRowsCleared()) {
            
        int temp = level->getBlocksWithoutClear();
        std::cout << temp;
        temp++;
                
        if(temp % 5 == 0) {
            int tempScore = placeOneBlock(make_unique<OneBlock>());
            if(tempScore == -1) return false;
            score += tempScore;
        }
        level->setBlocksWithoutClear(temp);
        std::cout << temp << std::endl;
                
    }
    cout << "dropped at" <<endl;
    return true;     
}

pair<bool,bool> Player::specialActionMoveDown(){
    bool dropped = false;
    bool canDrop = true; //only relevant when dropped
    //return (drop called) (can't drop when drop called)
    Coordinate oldPos = currentBlock->getPosition();
    Coordinate newPos = currentBlock->getPosition();
    newPos.row++; //check drop once
    currentBlock->setPosition(newPos);
    bool collide = board.checkCollision(*currentBlock);
    newPos.row++; //check drop twice
    currentBlock->setPosition(newPos);
    collide = collide || board.checkCollision(*currentBlock);
    
    if(collide){
        dropped = true;
        currentBlock->setPosition(oldPos);
        canDrop = drop();
    }
    return {dropped, canDrop};
}

bool Player::advanceBlock(){
    currentBlock = std::move(nextBlock);
    nextBlock = level->getBlock();
    if(board.checkCollision(*currentBlock)){
        return false; //can't place block
    } 
    return true; //can place block
}

void Player::flushCurrentBlock(){
    currentBlock.reset(); //leaves unique_ptr empty
}

void Player::levelUp() {
    int levelNumber = level->getLevelNumber();
    if(levelNumber == 4) return;
    if(levelNumber == 0) {
        level = std::make_unique<LevelOne>(seed);
    } else if(levelNumber == 1) {
        level = std::make_unique<LevelTwo>(seed);
    } else if(levelNumber == 2) {
        level = std::make_unique<LevelThree>(seed);
    } else {
        level = std::make_unique<LevelFour>(seed);
    }
}

void Player::levelDown(){
    int levelNumber = level->getLevelNumber();
    if(levelNumber == 0) return;
    if(levelNumber == 1) {
        level = std::make_unique<LevelZero>(sequenceFile);
    } else if(levelNumber == 2) {
        level = std::make_unique<LevelOne>(seed);
    } else if(levelNumber == 3) {
        level = std::make_unique<LevelTwo>(seed);
    } else {
        level = std::make_unique<LevelThree>(seed);
    }
}
void Player::noRandom(std::string file) {
    if(level->getLevelNumber() < 3) return;
    ifstream s{file};
    level->setRandom(false);
    if(!s.good()) {
        std::cerr << "File is does not exist. Set to norandom and using default file";
        level->addSequence(sequenceFile);
    } else level->addSequence(file);
    
}
void Player::makeLevelRandom(){
    if(level->getLevelNumber() < 3) return;
    level->setRandom(true);
}

// Getters
int Player::getScore() const { return score; }
int Player::getLevelNumber() const { return level->getLevelNumber(); }
const Board& Player::getBoard() const { return board; }
const Block* Player::getCurrentBlock() const { return currentBlock.get(); }
const Block* Player::getNextBlock() const { return nextBlock.get(); }
const std::string Player::getSequenceFile() const {return sequenceFile;}
const int Player::getSeed() const {return seed;}
const bool Player::isHeavy() const {return heavy;}
const bool Player::isBlind() const {return blind;}
// Setters
void Player::setScore(int newScore) { score = newScore; }
void Player::setBoardRowsCleared(int num) {board.setRowsCleared(num);}
void Player::setLevel(int newLevel) { 
    switch (newLevel) {
        case 0:
            level = std::make_unique<LevelZero>(sequenceFile);
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
    if(level->getLevelNumber() == 3 || level->getLevelNumber() == 4) {
        currentBlock->setHeavy(true);
    }
}
void Player::enableBonus(){
    bonusEnabled = true;
    board.enableBonus();
}
