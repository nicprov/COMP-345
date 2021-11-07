#include <boost/algorithm/string.hpp>
#include "CommandProcessing.h"

// FileLineReader class
FileLineReader::~FileLineReader()
{
    this->stream->close();
}

FileLineReader::FileLineReader(const std::string &filename)
{
    this->filename = filename;
    this->stream = new std::ifstream;
    this->stream->open(this->filename);
}

FileLineReader::FileLineReader(const FileLineReader &fileLineReader)
{
    this->filename = fileLineReader.filename;
}

FileLineReader &FileLineReader::operator=(const FileLineReader &fileLineReader)
{
    this->filename = fileLineReader.filename;
    return *this;
}

std::ostream &operator<<(std::ostream &stream, const FileLineReader &fileLineReader)
{
    return stream << "Filename (" << fileLineReader.filename << ")";
}

std::string FileLineReader::readLineFromFile()
{
    std::string command;
    if (this->stream->eof())
        throw std::runtime_error("Reached end of file, no new lines to read");

    if (this->stream->is_open()){
        getline(*this->stream, command);
        return command;
    }
    throw std::runtime_error("Error reading from file: " + this->filename);
}

// Command class
Command::Command(GameEngine::GameCommand &gameCommand, const std::string& effect)
{
    this->command = new GameEngine::GameCommand(gameCommand);
    this->effect = effect;
}


Command::Command(const Command &_command)
{
    this->command = _command.command;
    this->effect = _command.effect;
}

Command &Command::operator= (const Command &_command)
{
    this->command = _command.command;
    this->effect = _command.effect;
    return *this;
}

std::ostream &operator<<(std::ostream &stream, const Command &_command)
{
    return stream << "Command (" << _command.command << "), Effect (" << _command.effect << " )";
}

void Command::safeEffect()
{

}

GameEngine::GameCommand* Command::getCommand()
{
    return this->command;
}

// CommandProcessor class
CommandProcessor::CommandProcessor(const GameEngine &gameEngine): gameEngine(const_cast<GameEngine &>(gameEngine))
{
    this->commands = new std::vector<Command*>();
}

CommandProcessor::CommandProcessor(const CommandProcessor &commandProcessor): gameEngine(commandProcessor.gameEngine)
{
    this->commands = new std::vector<Command*>(*commandProcessor.commands);
}

CommandProcessor &CommandProcessor::operator= (const CommandProcessor &commandProcessor)
{
    this->commands = new std::vector<Command*>(*commandProcessor.commands);
    return *this;
}

void CommandProcessor::getCommand()
{
    Command* command = this->readCommand();
    this->saveCommand(command);
}

Command* CommandProcessor::validate(const std::string& command, const std::string& effect)
{
    try {
        std::vector<GameEngine::GameCommand> validCommands;
        auto* gameCommand = new GameEngine::GameCommand(GameEngine::gameCommandMapping.at(command));
        this->gameEngine.getAvailableCommands(validCommands);
        bool isValid = false;
        if ((command == "loadmap" || command == "addplayer") && effect.empty())
            return nullptr;
        for (GameEngine::GameCommand validCommand: validCommands) {
            if (*gameCommand == validCommand)
                isValid = true;
        }
        if (isValid)
            return new Command(*gameCommand, effect);
    } catch (boost::wrapexcept<std::out_of_range>&) {}
    return nullptr;
}

void CommandProcessor::saveCommand(Command* command)
{
    if (command != nullptr)
        this->commands->push_back(command);
}

Command* CommandProcessor::readCommand()
{
    std::string inputCommand;
    std::string _command;
    std::string _effect;
    bool isValid = false;
    while (!isValid) {
        std::cout << "Enter command: ";
        getline(std::cin, inputCommand);
        std::vector<std::string> inputSplit;
        boost::split(inputSplit, inputCommand, boost::is_any_of("\t "));
        _command = boost::algorithm::to_lower_copy(inputSplit.at(0));
        if ((_command == "loadmap" || _command == "addplayer") && inputSplit.size() == 2) // Get effect only if command is loadmap or addplayer
            _effect = boost::algorithm::to_lower_copy(inputSplit.at(1));
        else
            _effect = "";
        Command* command = this->validate(_command, _effect);
        if (command == nullptr){
            std::cout << "\x1B[31m" << "Invalid command, try again... " << "\033[0m" << std::endl;
        } else {
            return command;
        }
    }
    return nullptr;
}

std::ostream &operator<<(std::ostream &stream, const CommandProcessor &commandProcessor)
{
    stream << "Commands[";
    int counter = 1;
    for (Command* command: *commandProcessor.commands){
        if (counter++ < commandProcessor.commands->size())
            stream << command->getCommand() << ",";
        else
            stream << command->getCommand();
    }
    stream << "]";
    return stream;
}

// FileCommandProcessorAdapter class
FileCommandProcessorAdapter::FileCommandProcessorAdapter(const GameEngine &gameEngine, const std::string &filename): CommandProcessor(gameEngine)
{
    this->fileLineReader = new FileLineReader(filename);
}

FileCommandProcessorAdapter::FileCommandProcessorAdapter(const FileCommandProcessorAdapter &fileCommandProcessorAdapter): CommandProcessor(fileCommandProcessorAdapter)
{
    this->fileLineReader = fileCommandProcessorAdapter.fileLineReader;
}

FileCommandProcessorAdapter &FileCommandProcessorAdapter::operator= (const FileCommandProcessorAdapter &fileCommandProcessorAdapter)
{
    this->commands = new std::vector<Command*>(*fileCommandProcessorAdapter.commands);
    return *this;
}

std::ostream &operator<<(std::ostream &stream, const FileCommandProcessorAdapter &fileCommandProcessorAdapter)
{
    return stream << "FileCommandProcessorAdaptor (" << fileCommandProcessorAdapter.fileLineReader->filename;
}

Command* FileCommandProcessorAdapter::readCommand()
{
    std::string _command;
    std::string _effect;
    std::string inputCommand = this->fileLineReader->readLineFromFile();
    std::vector<std::string> inputSplit;
    boost::split(inputSplit, inputCommand, boost::is_any_of("\t "));
    _command = boost::algorithm::to_lower_copy(inputSplit.at(0));
    if (_command == "loadmap" || _command == "addplayer") // Get effect only if command is loadmap or addplayer
        _effect = boost::algorithm::to_lower_copy(inputSplit.at(1));
    else
        _effect = "";
    auto* command = this->validate(_command, _effect);
    if (command == nullptr)
        std::cout << "Invalid command entered: " + _command;
    return command;
}