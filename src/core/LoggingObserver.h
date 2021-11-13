#pragma once

#include <string>
#include <vector>

class ILoggable{
public:
    virtual std::string stringToLog() = 0;
    ILoggable();
    ~ILoggable();
};

class Observer {
public:
    Observer();
    ~Observer();
    virtual void update(ILoggable*) = 0;
};

class Subject : public ILoggable {
public:
    void attach(Observer* o);
    void detach(Observer* o);
    void notify(ILoggable* I);
    std::vector<Observer*> getObservers();
    Subject();
    ~Subject();
private:
    std::vector<Observer*> observers;
};

class LogObserver : public Observer{
public:
    LogObserver(const std::string&);
    ~LogObserver();
    void update(ILoggable*);
private:
    std::string filename;
};


