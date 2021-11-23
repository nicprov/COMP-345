#pragma once

#include <string>
#include <vector>

class ILoggable{
public:
    virtual std::string stringToLog() = 0; //pure virtual method for string to log
};

class Observer {
public:
    virtual void update(ILoggable*) = 0; //pure virtual update method
};

class Subject : public ILoggable {
public:
    void attach(Observer* o); //attach method to attach observer to subject
    void detach(Observer* o); //detach method to detach observer from subject
    void notify(ILoggable* I); //notify method to notify of logging event
    std::vector<Observer*> getObservers(); //return list of observers
    Subject(); //default constructor for subject
    ~Subject(); //default destructor for destructor
private:
    std::vector<Observer*> observers; //vector of observer pointer objects
};

class LogObserver : public Observer{
public:
    LogObserver(const std::string&); //log observer parameterized constructor
    void update(ILoggable*); //overriden update method
private:
    std::string filename; //name of file to log to
};


