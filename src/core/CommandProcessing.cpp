#include <boost/algorithm/string.hpp>
#include "CommandProcessing.h"

// FileLineReader class
/**
* Destructor
* Closes the input stream.
*/
FileLineReader::~FileLineReader()
{
    this->stream->close();
}

/**
* Parameterized constructor
* @param filename name of the file
*/
FileLineReader::FileLineReader(const std::string &filename)
{
    this->filename = filename;
    this->stream = new std::ifstream;
    this->stream->open(this->filename);
    lineCount = 0;
}

/**
 * Copy Constructor makes a copy of FileLineReader
 * @param fileLineReader fileLineReader
 */
FileLineReader::FileLineReader(const FileLineReader &fileLineReader)
{
    this->filename = fileLineReader.filename;
    this->lineCount = fileLineReader.lineCount;
    this->stream = fileLineReader.stream;
}

/**
* Assignment operator
* @param fileRineReader fileLineReader
*/
FileLineReader &FileLineReader::operator=(const FileLineReader &fileLineReader)
{
    if (this != &fileLineReader) {
        this->filename = fileLineReader.filename;
        this->stream = fileLineReader.stream;
        this->lineCount = 0;
    }
    return *this;
}

/**
* Stream output operator
*/
std::ostream &operator<<(std::ostream &stream, const FileLineReader &fileLineReader)
{
    return stream << "Filename (" << fileLineReader.filename << ")";
}

/**
* Read lines from a file until the end of the file.
* @return command returns commands.
*/
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
/**
* Parameterized constructor
* @param gameCommand game command
*/
Command::Command(const GameEngine::GameCommand &gameCommand)
{
    this->command = new GameEngine::GameCommand(gameCommand);
    this->params = std::vector<std::string>();
    this->effect = "";
}

/**
 * Parameterized constructor
 * @param gameCommand game command
 * @param param parameter
 */
Command::Command(const GameEngine::GameCommand &gameCommand, const std::vector<std::string>& params)
{
    this->command = new GameEngine::GameCommand(gameCommand);
    this->params = params;
    this->effect = "";
}

/**
 * Parameterized constructor
 * @param gameCommand game command
 * @param param parameter
 * @param effect
*/
Command::Command(const GameEngine::GameCommand &gameCommand, const std::vector<std::string>& params, const std::string& effect)
{
    this->command = new GameEngine::GameCommand(gameCommand);
    this->params = params;
    this->effect = effect;
}

/**
 * Copy Constructor makes a copy of Command
 * @param command Command
 */
Command::Command(const Command &_command)
{
    this->command = new GameEngine::GameCommand(*_command.command);
    this->params = _command.params;
    this->effect = _command.effect;
}

/**
* Assignment operator
 * @param command Command
*/
Command &Command::operator= (const Command &_command)
{
    if (this != &_command){
        this->command = new GameEngine::GameCommand(*_command.command);
        this->params = _command.params;
        this->effect = _command.effect;
    }
    return *this;
}

/**
* Stream output operator
*/
std::ostream &operator<<(std::ostream &stream, const Command &_command)
{
    stream << "Command (" << *_command.command << "), Params [";
    int counter = 1;
    for (const std::string& _param: _command.params){
        if (counter++ < _command.params.size())
            stream << _param << ",";
        else
            stream << _param;
    }
    stream << "]";
    return stream;
}

/**
* @ returns a string with the command and param.
*/
std::string Command::toString(){
    std::string strCommand;
    for (auto& it: GameEngine::gameCommandMapping){
        if (it.second == *this->command)
            strCommand = it.first;
    }
    std::string listOfCommands;
    int counter = 1;
    for (const std::string& _param: this->params){
        if (counter++ < this->params.size())
            listOfCommands += _param + ",";
        else
            listOfCommands += _param;
    }
    listOfCommands += "]";
    return "Command (" + strCommand + "), Param (" + listOfCommands + ")";
}

/**
* Saves the effect and notifies.
* @param effect the effect
*/
void Command::saveEffect(const std::string& _effect)
{
    this->effect = _effect;
    notify(this);
}

/**
* Gets the command
*/
Command& Command::getCommand()
{
    return *this;
}

/**
* Gets the game command
*/
GameEngine::GameCommand* Command::getGameCommand()
{
    return this->command;
}

/**
* Gets the param
*/
std::vector<std::string> Command::getParams()
{
    return this->params;
}

/**
* Gets the effect
*/
std::string Command::getEffect()
{
    return this->effect;
}

/**
* Outputs to log
* @return string with the effect of the command.
*/
std::string Command::stringToLog()
{
    return "Command's Effect: " + this->getEffect();
}

// CommandProcessor class
/**
* Parameterized constructor
* @param gameEngine the game engine
*/
CommandProcessor::CommandProcessor(const GameEngine &gameEngine): gameEngine(const_cast<GameEngine &>(gameEngine))
{
    this->commands = std::vector<Command*>();
}

/**
* Copy constructor
* @param commandProcessor CommandProcessor
*/
CommandProcessor::CommandProcessor(const CommandProcessor &commandProcessor): gameEngine(commandProcessor.gameEngine)
{
    this->commands = std::vector<Command*>();
    for (Command* command: commandProcessor.commands)
        this->commands.push_back(new Command(*command));
    this->gameEngine = commandProcessor.gameEngine;
}

/**
* Assignment operator
* @param commandProcessor CommandProcessor
*/
CommandProcessor &CommandProcessor::operator= (const CommandProcessor &commandProcessor)
{
    if (this != &commandProcessor){
        for (Command* command: this->commands)
            delete command;
        this->commands = std::vector<Command*>();
        for (Command* command: commandProcessor.commands)
            this->commands.push_back(new Command(*command));
        this->gameEngine = commandProcessor.gameEngine;
    }
    return *this;
}

/**
* Gets the command
*/
Command* CommandProcessor::getCommand()
{
    Command* command = this->readCommand();
    this->saveCommand(command);
    return command;
}

/**
* Checks if the command is valid
* @param command the command
* @param param the parameter
*/
Command* CommandProcessor::validate(const std::string& command, const std::vector<std::string>& params)
{
    try {
        std::vector<GameEngine::GameCommand> validCommands;
        auto* gameCommand = new GameEngine::GameCommand(GameEngine::gameCommandMapping.at(command));
        this->gameEngine.getAvailableCommands(validCommands);
        bool isValid = false;
        if ((command == "loadmap" && params.size() != 1) or (command == "addplayer" && params.size() != 2) or (command == "tournament" && params.size() != 4))
            return nullptr;
        for (GameEngine::GameCommand validCommand: validCommands) {
            if (*gameCommand == validCommand)
                isValid = true;
        }
        if (isValid)
            return new Command(*gameCommand, params);
    } catch (boost::wrapexcept<std::out_of_range>&) {}
    return nullptr;
}

/**
* Saves the command and notifies
* @param command the command
*/
void CommandProcessor::saveCommand(Command* command)
{
    if (command != nullptr){
        this->commands.push_back(command);
        notify(this);
    }
}

/**
* Reads the command
* @return command returns the command that was read
*/
Command* CommandProcessor::readCommand()
{
    std::string inputCommand;
    std::string _command;
    std::vector<std::string> _params;
    bool isValid = false;
    while (!isValid) {
        std::cout << "Enter command: ";
        getline(std::cin, inputCommand);
        std::tuple<std::string, std::vector<std::string>> result = getCommandAndParamsFromString(inputCommand);
        _command = std::get<0>(result);
        _params = std::get<1>(result);
        Command* command = this->validate(_command, _params);
        if (command == nullptr){
            std::cout << std::endl << "\x1B[31m" << "Invalid command, try again... " << "\033[0m" << std::endl << std::endl;
        } else {
            return command;
        }
    }
    return nullptr;
}

/**
* Outputs to log
* @return string of the command.
*/
std::string CommandProcessor::stringToLog() {
    return "Command: " + this->commands.back()->toString();
}

/**
* Stream output operator
*/
std::ostream &operator<<(std::ostream &stream, const CommandProcessor &commandProcessor)
{
    stream << "Commands[";
    int counter = 1;
    for (Command* command: commandProcessor.commands){
        if (counter++ < commandProcessor.commands.size())
            stream << command->getCommand() << ",";
        else
            stream << command->getCommand();
    }
    stream << "]";
    return stream;
}

// FileCommandProcessorAdapter class
/**
* Parameterized constructor
* @param gameEngine the game engine
* @param fileName name of the file
*/
FileCommandProcessorAdapter::FileCommandProcessorAdapter(const GameEngine &gameEngine, const std::string &filename): CommandProcessor(gameEngine)
{
    this->fileLineReader = new FileLineReader(filename);
}

/**
* Copy constructor
* @param fileCommandProcessorAdaptor
*/
FileCommandProcessorAdapter::FileCommandProcessorAdapter(const FileCommandProcessorAdapter &fileCommandProcessorAdapter): CommandProcessor(fileCommandProcessorAdapter)
{
    this->fileLineReader = fileCommandProcessorAdapter.fileLineReader;
}

/**
* Assignment operator
* @param fileCommandProcessorAdaptor
*/
FileCommandProcessorAdapter &FileCommandProcessorAdapter::operator= (const FileCommandProcessorAdapter &fileCommandProcessorAdapter)
{
    if (this != &fileCommandProcessorAdapter){
        for (Command* command: this->commands){
            delete command;
        }
        this->commands = std::vector<Command*>();
        for (Command* command: fileCommandProcessorAdapter.commands)
            this->commands.push_back(new Command(*command));
        delete this->fileLineReader;
        this->fileLineReader = new FileLineReader(*fileCommandProcessorAdapter.fileLineReader);
    }
    return *this;
}

/**
* Stream output operator
*/
std::ostream &operator<<(std::ostream &stream, const FileCommandProcessorAdapter &fileCommandProcessorAdapter)
{
    return stream << "FileCommandProcessorAdaptor (" << fileCommandProcessorAdapter.fileLineReader->filename;
}

/**
* Reads the command
* @return command returns the command that was read
*/
Command* FileCommandProcessorAdapter::readCommand()
{
    std::string inputCommand = this->fileLineReader->readLineFromFile();
    std::tuple<std::string, std::vector<std::string>> result = getCommandAndParamsFromString(inputCommand);
    std::string _command = std::get<0>(result);
    std::vector<std::string> params = std::get<1>(result);
    auto* command = this->validate(_command, params);
    if (command == nullptr)
        std::cout << std::endl << "\x1B[31m" << "Invalid command entered: " << inputCommand <<  "\033[0m" << std::endl << std::endl;
    return command;
}

std::tuple<std::string, std::vector<std::string>> getCommandAndParamsFromString(std::string input){
    std::vector<std::string> inputSplit;
    std::string _command;
    boost::split(inputSplit, input, boost::is_any_of("\t "));
    _command = boost::algorithm::to_lower_copy(inputSplit.at(0));
    auto params = std::vector<std::string>();
    if (_command == "loadmap" && inputSplit.size() == 2) // Get param only if command is loadmap or addplayer
        params.push_back(boost::algorithm::to_lower_copy(inputSplit.at(1)));
    else if (_command == "addplayer" && inputSplit.size() == 3){
        params.push_back(boost::algorithm::to_lower_copy(inputSplit.at(1)));
        params.push_back(boost::algorithm::to_lower_copy(inputSplit.at(2)));
    } else if (_command == "tournament" && inputSplit.size() == 5){
        params.push_back(boost::algorithm::to_lower_copy(inputSplit.at(1)));
        params.push_back(boost::algorithm::to_lower_copy(inputSplit.at(2)));
        params.push_back(boost::algorithm::to_lower_copy(inputSplit.at(3)));
        params.push_back(boost::algorithm::to_lower_copy(inputSplit.at(4)));
    }
    return {_command, params};
}