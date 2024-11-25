#ifndef COMMANDINTERPRETER_H
#define COMMANDINTERPRETER_H
#include <string>
#include <vector>
#include <map>

class CommandInterpreter {
    std::map<std::string, std::string> commands;
    std::vector<std::string> macros; // to be implemented later, not sure how macro works yet
    std::pair<int, std::string> commandToReturn;
    std::string fileName;
    std::pair<int, std::string> parseCommand(const std::string &input);
    std::pair<int, std::string> CommandInterpreter::separateNumber(std::string word);
    bool isValid(std::string word);
    void updateNum();
    std::vector<int> getCommandValue(std::string temp);
    void rename(std::string oldName, std::string newName);
    public:
        CommandInterpreter();
        std::pair<int, std::string> getUserMove(std::istream& input);
};

#endif
