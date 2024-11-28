#include <fstream>
#include <iostream>
#include <memory>
#include <map>
#include <string>
#include <cctype>
#include <stdexcept>
#include "levels.h"

// sets list of blocks in sequence one and sequence two based on the given input files
LevelZero::LevelZero(std::string file) : count{0} {
    // Load sequence1.txt into sequenceOne
    sequenceText = parseBlockSequence(file);
}

// gets the block for player in level zero
std::unique_ptr<Block> LevelZero::getBlock() {

    std::string blockType = sequenceText[count];
    count = (count + 1) % sequenceText.size(); // Loop back to the start
 //   std::cout<< blockType << "\n";
    return createBlock(blockType);
}

// for testing purposes
std::vector<std::string> LevelZero::getSequence() {return sequenceText;} 

// sets seed for randomizer to be parameter, default is 0
LevelOne::LevelOne(int seed) {
    srand(seed);  
}

// gets next block for level one
std::unique_ptr<Block> LevelOne::getBlock() {

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
    string blockType = getBlockType(blockProbabilities,randNum);
    std::unique_ptr<Block> temp = createBlock(blockType);
    return temp;
}

LevelTwo::LevelTwo(int seed) {
    srand(seed);  
}

// gets next block for level 2
std::unique_ptr<Block> LevelTwo::getBlock() {

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
    string blockType = getBlockType(blockProbabilities,randNum);
    std::unique_ptr<Block> temp = createBlock(blockType);
    return temp;
}

// gets next block for level 3
// need to write logic for random and norandom
LevelThree::LevelThree(int seed) {
    srand(seed);  
    isRandom = true;
}
std::unique_ptr<Block> LevelThree::getBlock() {
    std::unique_ptr<Block> temp;
    if(isRandom) {
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
        string blockType = getBlockType(blockProbabilities,randNum);
        temp = createBlock(blockType);
    } else {
        string blockType = sequenceText[count];
        count = (count + 1) % sequenceText.size(); // Loop back to the start
        temp =  createBlock(blockType);
    }
    
    // set block to be heavy
    temp->setHeavy(true);
    return temp;
}

void LevelThree::addSequence(std::string file) {
    sequenceText = parseBlockSequence(file);
    count = 0;
}
void LevelThree::setRandom(bool input) {isRandom = input;}

// will finish integrating one by one block after 
LevelFour::LevelFour(int seed): LevelThree(seed), blocksWithoutClear{0} {
    srand(seed);
}
// std::unique_ptr<Block> LevelFour::getBlock() {}

std::string getBlockType(const std::map<int, std::string> &probabilities, int randNum) {
    std::string blockType;
    for (auto& p : probabilities) {
        if(randNum <= p.first) {
            blockType = p.second;
            break;
        } 
    }
    return blockType;
}
std::unique_ptr<Block> createBlock(std::string blockType) {
    if(blockType == "iblock" || blockType == "iblock\r") {
        return std::make_unique<IBlock>();
    } else if (blockType == "jblock" || blockType == "jblock\r") {
        return std::make_unique<JBlock>();
    } else if(blockType == "sblock" || blockType == "sblock\r") {
        return std::make_unique<SBlock>();
    } else if(blockType == "zblock" || blockType == "zblock\r") {
        return std::make_unique<ZBlock>();
    } else if(blockType == "oblock" || blockType == "oblock\r") {
        return std::make_unique<OBlock>();
    } else if(blockType == "tblock" || blockType == "tblock\r") {
        return std::make_unique<TBlock>();
    } else {
        return std::make_unique<LBlock>();
    }

    return nullptr;
}

std::vector<std::string> parseBlockSequence(const std::string& file) {
    std::ifstream stream{file};

    std::vector<std::string> sequence;
    std::string line;
    while (std::getline(stream, line)) {
        cout << line << endl;
        cout << (line == "iblock\r") << endl;
        if (line == "iblock" || line == "jblock" || line == "sblock" || 
            line == "zblock" || line == "tblock" || line == "lblock" || 
            line == "oblock" || line == "iblock\r" || line == "jblock\r" || line == "sblock\r" || 
            line == "zblock\r" || line == "tblock\r" || line == "lblock\r" || 
            line == "oblock\r") {
            sequence.emplace_back(line);
        }
    }

    if (sequence.empty()) {
        throw std::runtime_error("Error: " + file + " is empty or contains no valid blocks");
    }

    return sequence;
}
int LevelZero::getLevelNumber() const{return 0;}
int LevelOne::getLevelNumber() const{return 1;}
int LevelTwo::getLevelNumber() const{return 2;}
int LevelThree::getLevelNumber() const{return 3;}
int LevelFour::getLevelNumber() const{return 4;}

int LevelFour::getBlocksWithoutClear() const {return blocksWithoutClear;}
void LevelFour::setBlocksWithoutClear(int num) {blocksWithoutClear = num;}
