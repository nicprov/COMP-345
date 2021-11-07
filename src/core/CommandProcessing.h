#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include "GameEngine.h"

class FileLineReader {
public:
    ~FileLineReader();
    FileLineReader(const std::string&);
    FileLineReader(const FileLineReader&);
    FileLineReader& operator= (const FileLineReader&);
    friend std::ostream& operator<< (std::ostream&, const FileLineReader&);
    std::string filename;
    std::string readLineFromFile();
private:
    std::ifstream* stream;
    int lineCount;
};

class Command{
public:
    Command(GameEngine::GameCommand&);
    Command(GameEngine::GameCommand&, const std::string&);
    Command(GameEngine::GameCommand&, const std::string&, const std::string&);
    Command(const Command&);
    Command& operator= (const Command&);
    friend std::ostream& operator<< (std::ostream&, const Command&);
    void saveEffect(const std::string&);
    GameEngine::GameCommand* getCommand();
    std::string getParam();
    std::string getEffect();
private:
    GameEngine::GameCommand* command;
    std::string param;
    std::string effect;
};

class CommandProcessor {
public:
    CommandProcessor(const GameEngine &gameEngine);
    CommandProcessor(const CommandProcessor&);
    CommandProcessor& operator= (const CommandProcessor&);
    friend std::ostream& operator<< (std::ostream&, const CommandProcessor&);
    void getCommand();
    Command* validate(const std::string&, const std::string&);
protected:
    void saveCommand(Command*);
    virtual Command* readCommand();
    std::vector<Command*>* commands;
    GameEngine& gameEngine;
};

class FileCommandProcessorAdapter: public CommandProcessor {
public:
    FileCommandProcessorAdapter(const GameEngine&, const std::string&);
    FileCommandProcessorAdapter(const FileCommandProcessorAdapter&);
    FileCommandProcessorAdapter& operator= (const FileCommandProcessorAdapter&);
    friend std::ostream& operator<< (std::ostream&, const FileCommandProcessorAdapter&);
private:
    Command* readCommand();
    FileLineReader* fileLineReader;
};
