#ifndef LEVEL_H
#define LEVEL_H
#include "block.h"
#include <map>
class Level {
    public: 
        virtual std::shared_ptr<Block> getBlock(int playerNum) = 0;
        virtual ~Level() {};
};

class LevelZero: public Level {
    std::vector<std::string> sequenceOne;
    std::vector<std::string> sequenceTwo;
    int count1;
    int count2;
    public:
        LevelZero();
        std::shared_ptr<Block> getBlock(int playerNum) override;
        std::vector<std::string>getSequenceOne();
        std::vector<std::string>getSequenceTwo();
};

class LevelOne: public Level {
    int seed;
    public:
        LevelOne(int seed = 0);
        std::shared_ptr<Block> getBlock(int playerNum) override;
};

class LevelTwo: public Level {
    int seed;
    public:
        LevelTwo(int seed = 0);
        std::shared_ptr<Block> getBlock(int playerNum) override;
};
class LevelThree: public Level {
    int seed;
    public:
        LevelThree(int seed = 0);
        std::shared_ptr<Block> getBlock(int playerNum) override;
};

class LevelFour: public Level {
    int seed;
    int blocksWithoutClear;
    public:
        LevelFour(int seed = 0);
        std::shared_ptr<Block> getBlock(int playerNum) override;
};

std::shared_ptr<Block> createBlock(const std::map<int, std::string> &probabilities, int randNum);
#endif
