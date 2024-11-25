#include "command_interpreter.h"
#include <vector>
#include <iostream>
#include <string>
#include <utility>
#include <sstream>

CommandInterpreter::CommandInterpreter(){
    // using a map format to accomodate for renaming commands
    commands = {{"left", "left"},
            {"right", "right"},
            {"down", "down"},
            {"drop", "drop"},
            {"clockwise", "clockwise"},
            {"counterclockwise", "counterclockwise"},
            {"levelup", "levelup"},
            {"leveldown", "leveldown"},
            {"norandom", "norandom"},
            {"random", "random"},
            {"restart", "restart"},
            {"sequence", "sequence"},
            {"rename", "rename"}
    };
}

std::pair<int, std::string> CommandInterpreter::getUserMove(std::istream& input) {
    std::string line;

    
    // get a valid command
    while(std::getline(input, line)) {
        std::istringstream iss{line};
        std::string word;
        iss >> word;
        commandToReturn = separateNumber(word);
        if(!isValid(commandToReturn.second)) {
            commandToReturn.first = 0;
            commandToReturn.second = "";
            continue;
        } 
        if(commandToReturn.second == "sequence" || commandToReturn.second == "norandom") {
            std::string file;
            iss >> file;
            commandToReturn.second = commandToReturn.second +  " " + file;
        }
        if(commandToReturn.second == "rename") {
            std::string oldName;
            std::string newName;
            iss >> oldName >> newName;
            rename(oldName, newName);
            continue;
        }

        break;
    } 
    updateNum();
    return commandToReturn;
    
}

void CommandInterpreter::updateNum() {
    if(commandToReturn.first < 0) {
        std::cerr << "Please enter a valid number" << "\n";
        return;
    }
    if(commandToReturn.first == 0) return;
    if(commandToReturn.second != "left" && commandToReturn.second != "right" && commandToReturn.second != "down" && commandToReturn.second != "drop" 
    && commandToReturn.second != "levelup" && commandToReturn.second != "leveldown" && commandToReturn.second != "clockwise" && commandToReturn.second != "right") {
        commandToReturn.first = 1;
    }
}
// checks if the command is valid, changes the command in std::pair commandToReturn to the actual command
bool CommandInterpreter::isValid(std::string temp) {
    if(temp == "I" || temp == "J" || temp == "S" || temp == "L" || temp == "O" || temp == "Z" || temp == "T") return true;
    for(int i = 0; i <= temp.length(); i++) {
        std::vector<int> commandValues = getCommandValue(temp.substr(0,i)); // all command values that match the substring
        if(commandValues.size() == 1) {
            commandToReturn.second = commandValues[0];
            return true;
        }
    }

    return false;
}

// get all commands values in the commands map that match the substring
std::vector<int> CommandInterpreter::getCommandValue(std::string substring) {
    std::vector<int> temp;
    // go through the entire map
    for (auto& p : commands) {
        if(p.first.find(substring) != std::string::npos) temp.emplace_back(p.second);
    }
    return temp;
}

std::pair<int, std::string> CommandInterpreter::separateNumber(std::string word) {
    size_t pos = 0; // To track where the numeric part ends
    int number = 0;

    try {
        // Attempt to convert the leading numeric part to an integer
        number = std::stoi(word, &pos);
    } catch (const std::invalid_argument&) {
        // If no numeric part exists, std::stoi will throw
        number = 1;
    }

    // Extract the remaining string starting from pos
    std::string letters = word.substr(pos);
    commandToReturn.first = number;
    commandToReturn.second = letters;
}