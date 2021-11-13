#include <iostream>
#include <fstream>
#include "LoggingObserver.h"

ILoggable::~ILoggable() {}

ILoggable::ILoggable() {}

Observer::Observer() {}

Observer::~Observer() {}

LogObserver::LogObserver(const std::string& filename)
{
    this->filename = filename;
}

LogObserver::~LogObserver() {}

void LogObserver::update(ILoggable* loggable)
{
    std::ofstream file(this->filename, std::ofstream::out | std::ofstream::app);
    if(file.is_open())
        file << loggable->stringToLog() << std::endl;
    else
        throw std::runtime_error("Unable to write to log file");
}

Subject::Subject()
{
    observers = std::vector<Observer*>();
}

Subject::~Subject()
{
    for (Observer* observer: this->observers)
        this->detach(observer);
}

void Subject::attach(Observer* o)
{
    observers.push_back(o);
}

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

void Subject::notify(ILoggable* i)
{
   auto iterator = observers.begin();
   for (; iterator != observers.end(); ++iterator)
      (*iterator)->update(i);
}

std::vector<Observer*> Subject::getObservers() {
    return this->observers;
}
