#include <fstream>
#include <iostream>
#include <memory>
#include <map>
#include <stdexcept>
#include "levels.h"

// sets list of blocks in sequence one and sequence two based on the given input files
LevelZero::LevelZero(std::string fileOne, std::string fileTwo) : count1(0), count2(0) {
    // Load sequence1.txt into sequenceOne
    std::ifstream streamOne{fileOne};
    if (!streamOne) {
        throw std::runtime_error("Error: Could not open sequence1.txt");
    }
    std::string line;
    while (std::getline(streamOne, line)) {
        sequenceOne.push_back(line);
    }
    if (sequenceOne.empty()) {
        throw std::runtime_error("Error: sequence1.txt is empty");
    }
    
    // load sequence2.txt into sequenceTwo
    line = "";
    std::ifstream streamTwo{fileTwo};
    if (!streamTwo) {
        throw std::runtime_error("Error: Could not open sequence2.txt");
    }
    while (std::getline(streamTwo, line)) {
        sequenceTwo.push_back(line);
    }
    if (sequenceTwo.empty()) {
        throw std::runtime_error("Error: sequence2.txt is empty");
    }
}

// given the player number (either 1 or 2),returns the next block for that player, update the count
std::shared_ptr<Block> LevelZero::getBlock(int playerNum) {
    // Get the next block type for Player 1
    std::string blockType;
    if(playerNum == 1) {
        blockType = sequenceOne[count1];
        count1 = (count1 + 1) % sequenceOne.size(); // Loop back to the start
    } else {
        blockType = sequenceOne[count2];
        count2 = (count2 + 1) % sequenceTwo.size(); // Loop back to the start
    }
    std::cout<< blockType << "\n";
    if(blockType == "iblock") { //
        return std::make_shared<IBlock>();
    } else if (blockType == "jblock") {
        std::cout<< "is running" << "\n";
        return std::make_shared<JBlock>();
    } else if(blockType == "sblock") {
        return std::make_shared<SBlock>();
    }
    return nullptr;
}

// for testing purposes
std::vector<std::string> LevelZero::getSequenceOne() {return sequenceOne;} 
std::vector<std::string> LevelZero::getSequenceTwo() {return sequenceTwo;}

// sets seed for randomizer to be parameter, default is 0
LevelOne::LevelOne(int seed): seed{seed} {}

// gets next block for level one
std::shared_ptr<Block> LevelOne::getBlock(int playerNum) {
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
std::shared_ptr<Block> LevelTwo::getBlock(int playerNum) {
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
std::shared_ptr<Block> LevelThree::getBlock(int playerNum) {
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
    std::shared_ptr<Block> temp = createBlock(blockProbabilities,randNum);
    // set block to be heavy
    //temp.setHeavy(true);
    return temp;
}


// will finish integrating one by one block after 
LevelFour::LevelFour(int seed): seed{seed}, blocksWithoutClear{0} {}
std::shared_ptr<Block> LevelFour::getBlock(int playerNum) {
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
    std::shared_ptr<Block> temp = createBlock(blockProbabilities,randNum);
    //temp.setHeavy(true);
    blocksWithoutClear++;
    if (blocksWithoutClear % 5 == 0) {
        //dropOneByOneBlock(gameBoard);
    }
    return temp;
}
std::shared_ptr<Block> createBlock(const std::map<int, std::string> &probabilities, int randNum) {
    std::string blockType;
    for (auto& p : probabilities) {
        if(randNum <= p.first) blockType = p.second;
    }
    if(blockType == "iblock") {
        return std::make_shared<IBlock>();
    } else if (blockType == "jblock") {
        return std::make_shared<JBlock>();
    } else if(blockType == "sblock") {
        return std::make_shared<SBlock>();
    }

    return nullptr;
}