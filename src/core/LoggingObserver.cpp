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
 * Constructor for subject
 */
Subject::Subject()
{
    observers = std::vector<Observer*>();
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