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
    virtual void Update(ILoggable*) =0;
};

class Subject : public ILoggable {
public:
    virtual void Attach(Observer* o);
    virtual void Detach(Observer* o);
    virtual void Notify(ILoggable* I);
    Subject();
    ~Subject();
private:
    std::vector<Observer*>* _observers;
};

class LogObserver : public Observer{
public:
    LogObserver();
    LogObserver(Subject*);
    ~LogObserver();
    void Update(ILoggable*);
private:
    Subject* _subject;


};


