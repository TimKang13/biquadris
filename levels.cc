#include <fstream>
#include <iostream>
#include <memory>
#include <map>
#include <string>
#include <stdexcept>
#include "levels.h"

// sets list of blocks in sequence one and sequence two based on the given input files
LevelZero::LevelZero(std::string file) : count{0} {
    // Load sequence1.txt into sequenceOne
    std::ifstream streamOne{file};
    if (!streamOne) {
        throw std::runtime_error("Error: Could not open sequence1.txt");
    }
    std::string line;
    while (std::getline(streamOne, line)) {
        sequenceText.push_back(line);
    }
    if (sequenceText.empty()) {
        std::string error = "Error: " + file + " is empty";
        throw std::runtime_error(error);
    }
}

// given the player number (either 0 or 1),returns the next block for that player, update the count
std::unique_ptr<Block> LevelZero::getBlock() {
    // Get the next block type for Player 1
    std::string blockType;
    blockType = sequenceText[count];
    count = (count + 1) % sequenceText.size(); // Loop back to the start
 //   std::cout<< blockType << "\n";
    if(blockType == "iblock") { //
        return std::make_unique<IBlock>();
    } else if (blockType == "jblock") {
        return std::make_unique<JBlock>();
    } else if(blockType == "lblock") {
        return std::make_unique<LBlock>();
    } else if(blockType == "tblock") {
        return std::make_unique<TBlock>();
    } else if(blockType == "sblock") {
        return std::make_unique<SBlock>();
    } else if(blockType == "oblock") {
        return std::make_unique<OBlock>();
    } else if(blockType == "zblock") {
        return std::make_unique<ZBlock>();
    }
    return nullptr;
}

// for testing purposes
std::vector<std::string> LevelZero::getSequence() {return sequenceText;} 

// sets seed for randomizer to be parameter, default is 0
LevelOne::LevelOne(int seed): seed{seed} {}

// gets next block for level one
std::unique_ptr<Block> LevelOne::getBlock() {
    srand(seed);
    //probability calcualted using culmulative distribution
   static const std::map<int, std::string> blockProbabilities = {
        {2, "iblock"},  // 1/6
        {4, "jblock"},  // 1/6
        {6, "lblock"},  // 1/6
        {8, "oblock"},  // 1/6
        {10, "tblock"}, // 1/6
        {11, "sblock"}, // 1/12
        {12, "zblock"}  // 1/12
    };

    // Generate a random number between 1 and 12
    int randNum = (rand() % 12) + 1;
    return createBlock(blockProbabilities, randNum);

    return nullptr;
}

LevelTwo::LevelTwo(int seed): seed{seed} {}

// gets next block for level 2
std::unique_ptr<Block> LevelTwo::getBlock() {
    srand(seed);
    static const std::map<int, std::string> blockProbabilities = {
        {1, "iblock"},  // 1/7
        {2, "jblock"},  // 1/7
        {3, "lblock"},  // 1/7
        {4, "oblock"},  // 1/7
        {5, "tblock"}, // 1/7
        {6, "sblock"}, // 1/7
        {7, "zblock"}  // 1/7
    };

    // Generate a random number between 1 and 7
    int randNum = (rand() % 7) + 1;
    return createBlock(blockProbabilities, randNum);
}

// gets next block for level 3
// need to write logic for random and norandom
LevelThree::LevelThree(int seed): seed{seed} {}
std::unique_ptr<Block> LevelThree::getBlock() {
    srand(seed);
    static const std::map<int, std::string> blockProbabilities = {
        {1, "iblock"},  // 1/9
        {2, "jblock"},  // 1/9
        {3, "lblock"},  // 1/9
        {4, "oblock"},  // 1/9
        {5, "tblock"}, // 1/9
        {7, "sblock"}, // 2/9
        {9, "zblock"}  // 2/9
    };
    int randNum = (rand() % 9) + 1;
    std::unique_ptr<Block> temp = createBlock(blockProbabilities,randNum);
    // set block to be heavy
    //temp.setHeavy(true);
    return temp;
}

void LevelThree::setRandom(bool input) {isRandom = input;}
void LevelFour::setRandom(bool input) {isRandom = input;}

// will finish integrating one by one block after 
LevelFour::LevelFour(int seed): seed{seed}, blocksWithoutClear{0} {}
std::unique_ptr<Block> LevelFour::getBlock() {
    srand(seed);
    static const std::map<int, std::string> blockProbabilities = {
        {1, "iblock"},  // 1/9
        {2, "jblock"},  // 1/9
        {3, "lblock"},  // 1/9
        {4, "oblock"},  // 1/9
        {5, "tblock"}, // 1/9
        {7, "sblock"}, // 2/9
        {9, "zblock"}  // 2/9
    };
    int randNum = (rand() % 9) + 1;
    std::unique_ptr<Block> temp = createBlock(blockProbabilities,randNum);
    //temp.setHeavy(true);
    blocksWithoutClear++;
    if (blocksWithoutClear % 5 == 0) {
        //dropOneByOneBlock(gameBoard);
    }
    return temp;
}
std::unique_ptr<Block> createBlock(const std::map<int, std::string> &probabilities, int randNum) {
    std::string blockType;
    for (auto& p : probabilities) {
        if(randNum <= p.first) blockType = p.second;
    }
    if(blockType == "iblock") {
        return std::unique_ptr<IBlock>();
    } else if (blockType == "jblock") {
        return std::unique_ptr<JBlock>();
    } else if(blockType == "sblock") {
        return std::unique_ptr<SBlock>();
    } else if(blockType == "zblock") {
        return std::unique_ptr<ZBlock>();
    } else if(blockType == "oblock") {
        return std::unique_ptr<OBlock>();
    } else if(blockType == "tblock") {
        return std::unique_ptr<TBlock>();
    } else {
        return std::unique_ptr<LBlock>();
    }

    return nullptr;
}

int LevelZero::getLevelNumber() const{return 0;}
int LevelOne::getLevelNumber() const{return 1;}
int LevelTwo::getLevelNumber() const{return 2;}
int LevelThree::getLevelNumber() const{return 3;}
int LevelFour::getLevelNumber() const{return 4;}