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
        virtual void addSequence(std::string file) {}
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

    public:
        LevelOne(int seed = 0);
        std::unique_ptr<Block> getBlock() override;
        int getLevelNumber() const override;
};

class LevelTwo: public Level {

    public:
        LevelTwo(int seed = 0);
        std::unique_ptr<Block> getBlock() override;
        int getLevelNumber() const override;
};
class LevelThree: public Level {
    std::vector<std::string> sequenceText;
    int count;
    bool isRandom;
    public:
        LevelThree(int seed = 0);
        std::unique_ptr<Block> getBlock() override;
        int getLevelNumber() const override;
        void setRandom(bool input) override;
        void addSequence(std::string file) override;
};

class LevelFour : public LevelThree {
public:
    LevelFour(int seed = 0);
   // std::unique_ptr<Block> getBlock() override;
    int getLevelNumber() const override;
    int blocksWithoutClear; // Tracks blocks placed without clearing rows
};

std::unique_ptr<Block> createBlock(std::string blockType);
std::vector<std::string> parseBlockSequence(const std::string& file);
std::string getBlockType(const std::map<int, std::string> &probabilities, int randNum);
#endif
