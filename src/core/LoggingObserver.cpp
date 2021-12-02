#include <iostream>
#include <fstream>
#include "LoggingObserver.h"

/**
 * parameterized constructor
 * @param filename where to write the file
 */
LogObserver::LogObserver(const std::string& filename)
{
    this->filename = filename;
}

/**
 * Update method to write log to file
 * @param loggable
 */
void LogObserver::update(ILoggable* loggable)
{
    std::ofstream file(this->filename, std::ofstream::out | std::ofstream::app);
    if(file.is_open())
        file << loggable->stringToLog() << std::endl;
    else
        throw std::runtime_error("Unable to write to log file");
}

/**
 * LogObserver copy constructor
 * @param logObserver
 */
LogObserver::LogObserver(const LogObserver &logObserver)
{
    this->filename = logObserver.filename;
}

/**
 * LogObserver assignment operator
 * @param observer
 * @return  log observer
 */
LogObserver &LogObserver::operator=(const LogObserver &observer)
{
    if (this != &observer){
        this->filename = observer.filename;
    }
    return *this;
}

/**
 * LogObserver stream operator
 * @param stream
 * @param logObserver
 * @return stream
 */
std::ostream &operator<<(std::ostream &stream, const LogObserver &logObserver)
{
    return stream << "LogObserver (" << logObserver.filename << ")";
}

/**
 * Destructor for subject
 */
Subject::~Subject()
{
    for (Observer* observer: this->observers)
        this->detach(observer);
}

/**
 * Constructor for subject
 */
Subject::Subject()
{
    observers = std::vector<Observer*>();
}

/**
 * Subject copy constructor
 * @param subject
 */
Subject::Subject(const Subject &subject)
{
    auto tempObservers = std::vector<Observer*>();
    for (Observer* observer: subject.observers)
        tempObservers.push_back(observer);
    this->observers = tempObservers;
}

/**
 * Subject assignment operator
 * @param subject
 * @return current object
 */
Subject &Subject::operator=(const Subject& subject) {
    if (this != &subject){
        this->observers = subject.observers;
    }
    return *this;
}

/**
 * Subject stream operator
 * @param stream
 * @param subject
 * @return stream
 */
std::ostream &operator<<(std::ostream &stream, const Subject &subject) {
    stream << "Subject [";
    int counter = 1;
    for (Observer* observer: subject.observers) {
        if (counter++ == subject.observers.size())
            stream << observer;
        else
            stream << observer << ",";
    }
    stream << "]";
    return stream;
}

/**
 * Attach observer to to a subject
 * @param o observer to attach
 */
void Subject::attach(Observer* o)
{
    observers.push_back(o);
}

/**
 * Detach the observer from the subject
 * @param o observer pointer
 */
void Subject::detach(Observer* o)
{
    int count = 0;
    for(Observer* observer : observers){
        if(observer == o){
            observers.erase(observers.begin() + count);
            break;
        }
        count++;
    }
}
/**
 * Notification which calls update method
 * @param i Iloggable instance
 */
void Subject::notify(ILoggable* i)
{
    auto iterator = observers.begin();
    for (; iterator != observers.end(); ++iterator)
        (*iterator)->update(i);
}
/**
 * gets observers vector
 * @return vector of observers
 */
std::vector<Observer*> Subject::getObservers() {
    return this->observers;
}