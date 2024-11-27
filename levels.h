#ifndef LEVEL_H
#define LEVEL_H
#include "block.h"
#include <map>
#include <memory>
#include <string>  

class Level {

    public: 
        virtual int getLevelNumber() const = 0;
        virtual std::unique_ptr<Block> getBlock() = 0;
        virtual ~Level() {};
        virtual void setRandom(bool random) {};
};

class LevelZero: public Level {
    std::vector<std::string> sequenceText;
    // variables for tracking which block each sequence is currently on
    int count;
    public:
        LevelZero(std::string file);
        std::unique_ptr<Block> getBlock() override;
        std::vector<std::string>getSequence();
        int getLevelNumber() const override;
};

class LevelOne: public Level {
    int seed;
    public:
        LevelOne(int seed = 0);
        std::unique_ptr<Block> getBlock() override;
        int getLevelNumber() const override;
};

class LevelTwo: public Level {
    int seed;
    public:
        LevelTwo(int seed = 0);
        std::unique_ptr<Block> getBlock() override;
        int getLevelNumber() const override;
};
class LevelThree: public Level {
    int seed;
    bool isRandom;
    public:
        LevelThree(int seed = 0);
        std::unique_ptr<Block> getBlock() override;
        int getLevelNumber() const override;
        void setRandom(bool input) override;
};

class LevelFour: public Level {
    int seed;
    int blocksWithoutClear;
    bool isRandom;
    public:
        void setRandom(bool input) override;
        LevelFour(int seed = 0);
        std::unique_ptr<Block> getBlock() override;
        int getLevelNumber() const override;
};

std::unique_ptr<Block> createBlock(const std::map<int, std::string> &probabilities, int randNum);
#endif
