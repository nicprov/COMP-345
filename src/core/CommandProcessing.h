#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include "GameEngine.h"

class FileLineReader {
public:
    ~FileLineReader(); //Destructor
    FileLineReader(const std::string&); //Parameterized constructor
    FileLineReader(const FileLineReader&); //Copy constructor
    FileLineReader& operator= (const FileLineReader&); //Assignment operator
    friend std::ostream& operator<< (std::ostream&, const FileLineReader&); //Stream output operator
    std::string filename; //Name of a file
    std::string readLineFromFile(); //Method reads lines from a file until the end of the file
private:
    std::ifstream* stream; //Input file stream
    int lineCount; //Number of lines in a file
};

class Command : public Subject{
public:
    Command(const GameEngine::GameCommand&); //Parameterized constructor
    Command(const GameEngine::GameCommand&, const std::vector<std::string>&); //Parameterized constructor
    Command(const GameEngine::GameCommand&, const std::vector<std::string>&, const std::string&); //Parameterized constructor
    Command(const Command&); //Copy constructor
    Command& operator= (const Command&); //Assignment operator
    friend std::ostream& operator<< (std::ostream&, const Command&); //Stream output operator
    void saveEffect(const std::string&); //Saves the effect
    Command& getCommand(); //Get the command
    GameEngine::GameCommand* getGameCommand(); //Get the game command
    std::vector<std::string> getParams(); //Get the param
    std::string getEffect(); //Get the effect
    std::string stringToLog(); //Output to log
    std::string toString(); // Output string with the command and param
private:
    GameEngine::GameCommand* command; //Pointer of type gameCommand to the command
    std::vector<std::string> params; //Parameter
    std::string effect; //Effect
};

class CommandProcessor : public Subject{
public:
    CommandProcessor(const GameEngine &gameEngine); //Parameterized constructor
    CommandProcessor(const CommandProcessor&); //Copy constructor
    CommandProcessor& operator= (const CommandProcessor&); //Assignment operator
    friend std::ostream& operator<< (std::ostream&, const CommandProcessor&); //Stream output operator
    Command* getCommand(); //Get the command
    Command* validate(const std::string&, const std::vector<std::string>&); //Checks if the command is valid
    std::string stringToLog(); //Output to log
protected:
    void saveCommand(Command*); //Saves the command
    virtual Command* readCommand(); //Virtual method to read the command
    std::vector<Command*> commands; //Vector of commands
    GameEngine& gameEngine; //Reference to the gameEngine
};

class FileCommandProcessorAdapter: public CommandProcessor {
public:
    FileCommandProcessorAdapter(const GameEngine&, const std::string&); //Parameterized constructor
    FileCommandProcessorAdapter(const FileCommandProcessorAdapter&); //Copy constructor
    FileCommandProcessorAdapter& operator= (const FileCommandProcessorAdapter&); //Assignment operator
    friend std::ostream& operator<< (std::ostream&, const FileCommandProcessorAdapter&); //Stream output operator
private:
    Command* readCommand(); //Reads the commands
    FileLineReader* fileLineReader; // Pointer to lines from a file.
};

std::tuple<std::string, std::vector<std::string>> getCommandAndParamsFromString(std::string);
