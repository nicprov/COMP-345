#pragma once

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
    ~Subject(); //default destructor for destructor
    Subject(); //default constructor for subject
    Subject(const Subject&); // subject copy constructor
    Subject& operator= (const Subject&); // assignment operator
    friend std::ostream& operator<< (std::ostream&, const Subject&); // stream operator
    void attach(Observer* o); //attach method to attach observer to subject
    void detach(Observer* o); //detach method to detach observer from subject
    void notify(ILoggable* I); //notify method to notify of logging event
    std::vector<Observer*> getObservers(); //return list of observers
private:
    std::vector<Observer*> observers; //vector of observer pointer objects
};

class LogObserver : public Observer{
public:
    LogObserver(const std::string&); //log observer parameterized constructor
    LogObserver(const LogObserver&); // log observer copy constructor
    LogObserver& operator= (const LogObserver&); // log observer assignment operator
    friend std::ostream& operator<< (std::ostream&, const LogObserver&); // log observer stream operator
    void update(ILoggable*); //overriden update method
private:
    std::string filename; //name of file to log to
};


