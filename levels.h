#ifndef LEVEL_H
#define LEVEL_H
#include "block.h"
#include <map>
#include <memory>
#include <string>  

class Level {

    public: 
        virtual int getLevelNumber() const = 0;
        virtual std::shared_ptr<Block> getBlock(int playerNum) = 0;
        virtual ~Level() {};

};

class LevelZero: public Level {
    std::vector<std::string> sequenceOne;
    std::vector<std::string> sequenceTwo;
    // variables for tracking which block each sequence is currently on
    int count1;
    int count2;
    public:
        LevelZero(std::string file1 = "sequence1.txt", std::string file2 = "sequence2.txt");
        std::shared_ptr<Block> getBlock(int playerNum) override;
        std::vector<std::string>getSequenceOne();
        std::vector<std::string>getSequenceTwo();
        int getLevelNumber() const override;
};

class LevelOne: public Level {
    int seed;
    public:
        LevelOne(int seed = 0);
        std::shared_ptr<Block> getBlock(int playerNum) override;
        int getLevelNumber() const override;
};

class LevelTwo: public Level {
    int seed;
    public:
        LevelTwo(int seed = 0);
        std::shared_ptr<Block> getBlock(int playerNum) override;
        int getLevelNumber() const override;
};
class LevelThree: public Level {
    int seed;
    bool isRandom;
    public:
        LevelThree(int seed = 0);
        std::shared_ptr<Block> getBlock(int playerNum) override;
        int getLevelNumber() const override;
        void setRandom(bool input);
};

class LevelFour: public Level {
    int seed;
    int blocksWithoutClear;
    bool isRandom;
    public:
        void setRandom(bool input);
        LevelFour(int seed = 0);
        std::shared_ptr<Block> getBlock(int playerNum) override;
        int getLevelNumber() const override;
};

std::shared_ptr<Block> createBlock(const std::map<int, std::string> &probabilities, int randNum);
#endif
