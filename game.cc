#include "game.h"
#include "command_interpreter.h"
#include "player.h"
#include <vector>
#include <string>
#include <utility>
#include <iostream>
#include <fstream>
#include "block.h"
#include "text_display.h"
using namespace std;


Game::Game(std::vector<std::unique_ptr<Player>>&& playerList, CommandInterpreter& CI):
    players{std::move(playerList)},
    highScores{{0, 0}},
    turn{0},
    isGameOver{false},
    CI{CI},
    numTotalMoves{0} {}

GameState Game::getGameState() const{
    return GameState{players, highScores};
}

void Game::startTurn(){
    bool canPlaceNextBlock = players[turn]->advanceBlock();
    if(!canPlaceNextBlock){
        endGame();
    }
}

void Game::endTurn(){
    if(players[turn]->getBoard().getRowsCleared() > 1){
        cout << "special action activated" << endl;
        string specialAction = CI.getSpecialAction(cin);
        players[!turn]->applySpecialAction(specialAction);
        players[turn]->setBoardRowsCleared(0); 
    }
    players[turn]->removeSpecialAction();
    turn = !turn; //switch turn
}

pair<int, string> Game::getUserCmd(){
    return CI.getUserCmd(cin);
}
void Game::executeCmd(string cmd, int moveRemaining){
    if (cmd == "left") {
        players[turn]->moveLeft();
    } else if (cmd == "right") {
        players[turn]->moveRight();
    } else if (cmd == "down") {
        players[turn]->moveDown();
    } else if (cmd == "clockwise") {
        players[turn]->rotateCW();
    } else if (cmd == "counterclockwise") {
        players[turn]->rotateCCW();
    } else if (cmd == "drop") {
        bool canDrop = players[turn]->drop();
        if(!canDrop){
            endGame();
        }
        if(players[turn]->getScore() > highScores[turn]){
            highScores[turn] = players[turn]->getScore();
        }
        //remove special action for current player
        players[turn]->flushCurrentBlock();
        if(moveRemaining > 0){
            players[turn]->advanceBlock();
        }
    } else if (cmd == "levelup") {
        players[turn]->levelUp();
    } else if (cmd == "leveldown") {
        players[turn]->levelDown();
    } else if (cmd.substr(0,8) == "norandom") {
        players[turn]->noRandom(cmd.substr(9));
    } else if (cmd == "random") {
        players[turn]->makeLevelRandom();
    } else if (cmd.substr(0, 8) == "sequence") {
        CI.setSequence(cmd.substr(9));
    } else if (cmd == "restart") {
        restartGame();
    } else if (cmd == "I" || cmd == "J" || cmd == "L" || 
               cmd == "O" || cmd == "S" || cmd == "T" || cmd == "Z") {
        players[turn]->setCurrentBlock(cmd[0]);
    } else if(cmd ==""){
        isGameOver = true;
    } else {
        std::cout << "Invalid command" << "\n";
    }
}

void Game::updateDisplay(){
    notifyObservers();
}

//start game   //note: prefix for non prefix commands need to be filtered out in CI
void Game::startGame(){
    while(!isGameOver){ //while game continues
        startTurn(); //will end game if currentBlock cannot be placed
        bool isTurnOver = false;
        while(!isTurnOver){ //next player's turn if drop
            updateDisplay();
            Coordinate oldPosition = players[turn]->getCurrentBlock()->getPosition();

            pair<int, string> cmdPair = getUserCmd();
            for(int i = cmdPair.first-1; i >= 0; --i){
                executeCmd(cmdPair.second, i);
            }

            isTurnOver = "drop" == cmdPair.second || "" == cmdPair.second;
                // check for level three and four block which is heavy

            //block heavy case
            if((cmdPair.second == "right" || cmdPair.second == "left" || cmdPair.second == "down" || cmdPair.second == "counterclockwise" || cmdPair.second == "clockwise") 
                && players[turn]->getCurrentBlock()->isHeavy()) {
                players[turn]->moveDown();
            }
            // special action heavy case
            if((cmdPair.second == "right" || cmdPair.second == "left") && players[turn]->isHeavy() && players[turn]->getCurrentBlock()->getPosition().col != oldPosition.col) {
                pair<bool,bool> calledDropPair = players[turn]->specialActionMoveDown();
                isTurnOver = calledDropPair.first;
                if(!calledDropPair.second){
                    endGame(); //drop called, but can't drop
                }
            }
        }
        endTurn();
    } 
    endProgram();
}

void Game::restartGame() {
    std::string sequenceOne = players[0]->getSequenceFile();
    std::string sequenceTwo = players[1]->getSequenceFile();
    int seed = players[0]->getSeed();
    players.clear(); //hope this frees the previous pts...
    players.push_back(std::make_unique<Player>(sequenceOne, 0, seed)); // temporary solution
    players.push_back(std::make_unique<Player>(sequenceTwo, 0, seed));
    turn = 0;
    isGameOver = false;
    numTotalMoves = 0;
    startGame();
}

void Game::endGame(){
    string winner = turn ? "player1" : "player2";
    cout << "winner: " << winner << endl;
    cout << "restart game?" << endl;
    while(1){
        pair<int, string> cmdPair = getUserCmd();
        string cmd = cmdPair.second;
        if(cmd == "restart") restartGame();
        else if(cmd == "") endProgram();
    }
}

void Game::endProgram(){
    // anything that needs to be run when game is over
    exit(0);
}

