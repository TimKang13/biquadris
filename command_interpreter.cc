#include "command_interpreter.h"
#include <vector>
#include <iostream>
#include <string>
#include <utility>
#include <sstream>
using namespace std;

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
    specialActions = {{"heavy", "heavy"}, {"blind", "blind"}, {"force", "force"}};
}

std::pair<int, std::string> CommandInterpreter::getUserCmd(std::istream& input) {
    std::string line;
    // get a valid command
    while(std::getline(input, line)) {
        if(line == "") return {0,""};
        std::istringstream iss{line};
        std::string word;
        iss >> word;
        commandToReturn = separateNumber(word);
        if(!isValid()) {
            std::cerr << "Please enter a valid command: ";
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

std::string CommandInterpreter::getSpecialAction(std::istream& in) {
    std::string action; 
    std::cout << "Please enter a special action (force/heavy/blind): ";
    while(true) {
        if (!(in >> action)) {
            return "";
        }
        for (auto& p : specialActions) {
            if(action == p.first) return p.second;
        }
        
        std::cout << "Invalid action. Please try again.\n";
    }
    
}
// changes any numbers greater than one to one for commands that shouldn't be run more than once
void CommandInterpreter::updateNum() {
    if(commandToReturn.first == 0) return;
    if(commandToReturn.second != "left" && commandToReturn.second != "right" && commandToReturn.second != "down" && commandToReturn.second != "drop" 
    && commandToReturn.second != "levelup" && commandToReturn.second != "leveldown" && commandToReturn.second != "clockwise" && commandToReturn.second != "right") {
        commandToReturn.first = 1;
    }
}
// checks if the command is valid, changes the command in std::pair commandToReturn to the actual command
bool CommandInterpreter::isValid() {
    if(commandToReturn.first < 0) {return false;}
    string temp = commandToReturn.second;
    if(temp == "I" || temp == "J" || temp == "S" || temp == "L" || temp == "O" || temp == "Z" || temp == "T") return true;
    std::vector<std::string> commandValues = getCommandValue(temp); // all command values that match the substring
    if(commandValues.size() == 1) {
        commandToReturn.second = commandValues[0];
        return true;
    }

    return false;
}

// get all commands values in the commands map that match the substring
std::vector<std::string> CommandInterpreter::getCommandValue(std::string substring) {
    std::vector<std::string> temp;
    // go through the entire map
    for (auto& p : commands) {
        if(p.first.length() >= substring.length() && substring == p.first.substr(0,substring.length())) {
            temp.emplace_back(p.second);
        }
    }
    return temp;
}

// separtes numbers and letters from a string
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
    return {number, letters};
}

// rename a certain command or special action, if that name doesn't exist, do nothing
void CommandInterpreter::rename(std::string oldName, std::string newName) {
    // rename a command
    auto it = commands.find(oldName);
    if (it != commands.end()) {
        std::string value = it->second;
        commands.erase(it);
        commands.insert({newName, value});
        return;
    }
    //rename special action 
    it = specialActions.find(oldName);
    if (it != specialActions.end()) {
        std::string value = it->second;
        specialActions.erase(it);
        specialActions.insert({newName, value});
    }
}
