#include "game.h"
#include "command_interpreter.h"
#include "player.h"
#include <vector>
#include <string>
#include <utility>
#include <iostream>
#include <fstream>
#include "block.h"
#include "displays.h"
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
    players[turn]->flushCurrentBlock();
    turn = !turn;
    ++numTotalMoves;
}

pair<int, string> Game::getUserCmd(){
    return CI.getUserCmd(cin);
}
void Game::executeCmd(string cmd){
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
    } else if (cmd == "levelup") {
        players[turn]->levelUp();
    } else if (cmd == "leveldown") {
        players[turn]->levelDown();
    } else if (cmd == "norandom") {
        // players[turn]->noRandom();
    } else if (cmd == "random") {
        // players[turn]->makeLevelRandom();
    } else if (cmd.substr(0, 8) == "sequence") {
        string s;
        ifstream f{cmd.substr(9)};
        while(f >> s){
            executeCmd(s);
        }
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
            pair<int, string> cmdPair = getUserCmd();
            for(int i = 0; i < cmdPair.first; ++i){
                executeCmd(cmdPair.second);
            }
            isTurnOver = "drop" == cmdPair.second || "" == cmdPair.second;
            if(cmdPair.second == "drop" && players[turn]->getBoard().getRowsCleared() > 1){
                cout << "special action activated" << endl;
                string specialAction = CI.getSpecialAction(cin);
                //player[!turn]->applySpecialAction();
                players[turn]->setBoardRowsCleared(0); 
            }
            if(players[turn]->getScore() > highScores[turn]){
                highScores[turn] = players[turn]->getScore();
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

