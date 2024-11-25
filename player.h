#ifndef PLAYER_H
#define PLAYER_H
#include "levels.h"
#include "block.h"
#include "board.h"

class Player {
    private:
        int player_num;
        int score;
        std::unique_ptr<Level> level;
        Board board;
        std::unique_ptr<Block> currentBlock;
        std::unique_ptr<Block> nextBlock;

    public:
        // Constructor and destructor
        Player();
        Player(int level);
        ~Player();
        // Game actions
        void applySpecialAction(const std::string &action);
        void moveLeft();
        void moveRight();
        void moveDown();
        void rotateCW();
        void rotateCCW();
        bool drop();

        //Block actions
        void advanceBlock();

        // Level actions
        // void levelUp();
        // void levelDown();
        // void noRandom();
        // void makeLevelRandom();

        // Getters
        int getScore() const;
        int getLevelNumber() const;
        const Board& getBoard() const;
        const Block* getCurrentBlock() const;
        const Block* getNextBlock() const;

        // Setters
        void setScore(int newScore);
        void setLevel(int newLevel);
        void setCurrentBlock(char blockChar);
};

#endif