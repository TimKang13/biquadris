#ifndef PLAYER_H
#define PLAYER_H
#include "levels.h"
#include "block.h"
#include "board.h"

class Player {
    private:
        int seed;
        std::string sequenceFile;
        int score;
        std::unique_ptr<Level> level;
        Board board;
        std::unique_ptr<Block> currentBlock;
        std::unique_ptr<Block> nextBlock;
        //special action
        bool heavy;
        bool blind;
        bool bonusEnabled;

    public:
        // Constructor and destructor
        Player(std::string fileName);
        Player(std::string sequenceFile, int level, int seed);
        ~Player();
        // Game actions
        void removeSpecialAction();
        void applySpecialAction(const std::string &action);
        void applyBlind();
        void applyForce(char blockChar);
        void applyHeavy();
        void moveLeft();
        void moveRight();
        void moveDown();
        void rotateCW();
        void rotateCCW();
        bool drop();
        pair<bool,bool> specialActionMoveDown();
        int placeOneBlock(unique_ptr<Block> oneBlock); 
        //Block actions
        bool advanceBlock();
        void flushCurrentBlock();

        //Level actions
        void levelUp();
        void levelDown();
        void noRandom(std::string file);
        void makeLevelRandom();

        // Getters
        int getScore() const;
        int getLevelNumber() const;
        const Board& getBoard() const;
        const Block* getCurrentBlock() const;
        const Block* getNextBlock() const;
        const std::string getSequenceFile() const;
        const int getSeed() const;
        const bool isHeavy() const;
        const bool isBlind() const;

        // Setters
        void setScore(int newScore);
        void setLevel(int newLevel);
        void setCurrentBlock(char blockChar);
        void setBoardRowsCleared(int num);
        void enableBonus();
};

#endif
